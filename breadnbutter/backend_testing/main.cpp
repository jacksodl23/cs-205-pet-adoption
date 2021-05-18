#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <utility>
#include <QtSql>

#include "gtest/gtest.h"
#include "../backend/petowner.h"
#include "../backend/shelter.h"
#include "../backend/pet.h"
#include "../backend/user.h"
#include "../gui/shelterprofilesqlmodel.h"
#include "../backend/utils.h"
#include "../backend/location.h"

using namespace std;

class AdopterTest : public ::testing::Test {
protected:
    PetOwner *owner;

public:
    AdopterTest() {
        owner = new PetOwner("hello", "jonny", "appleseed", "themapples@gmail.com", "4845427676", "Seattle");
    }

    void TearDown() {
        owner->deleteFromDB();
    }
};

class PetTest : public ::testing::Test {
protected:
    Pet *pet;

public:
    PetTest() {
        pet = new Pet(true, "Fuzzy Wuzzy", 4, "Turkish Van", "brown", "medium", 8, "Shelter", true, "Lorem Ipsum");
    }

    void TearDown() {
        pet->deleteFromDB();
    }
};

class ShelterTest : public ::testing::Test {
protected:
    Shelter *shelter;

public:
    ShelterTest() {
        shelter = new Shelter("Who Let the Paws Out?", "Pittsburgh", "paws@paws.com");
    }

    void TearDown() {
        shelter->deleteFromDB();
    }
};

TEST_F(AdopterTest, TestNewAdopter) {
    ASSERT_EQ(owner->insertInDB(), true);
}

TEST_F(AdopterTest, TestDistanceToShelter) {
    srand(time(0));

    QSqlQuery query;
    query.prepare("select max(shelter_id) from shelter");
    if (query.exec()) {
        if (query.next()) {
            int maxID = query.value(0).toInt();

            int randID = rand() % maxID;
            query.prepare("select location_id from location where location_id = ?");
            query.addBindValue(randID);

            if (query.exec()) {
                if (query.next()) {
                    int locID = query.value(0).toInt();
                    Location loc(locID);
                    qDebug() << "Found shelter in" << loc.getCity();

                    double result = distanceToUser(loc, *owner);
                    qDebug() << "Distance is" << result << "miles.";
                    ASSERT_NE(result, 0);
                }
            } else {
                qDebug() << "Error getting random shelter:" << query.lastError().text();
            }
        }
    } else {
        qDebug() << "Error getting shelter IDs:" << query.lastError().text();
    }
}

TEST_F(AdopterTest, TestDeleteAdopter) {
    ASSERT_EQ(owner->deleteFromDB(), true);
}

TEST_F(PetTest, TestInsertPet) {
    ASSERT_EQ(pet->insertIntoDB(100), true);
}

TEST_F(PetTest, TestUpdatePet) {
    QSqlQuery query;
    query.prepare("update pet set age = ? where pet_id = ?");
    query.addBindValue(13);
    query.addBindValue(pet->getPet_id());

    ASSERT_EQ(query.exec(), true);
}

TEST_F(PetTest, TestLikePet) {
    PetOwner owner(201);
    ASSERT_EQ(owner.likePet(*pet), true);
}

TEST_F(ShelterTest, TestInsertShelter) {
    ASSERT_EQ(shelter->insertIntoDB(), true);
}

TEST(TestRead, TestReadShelter) {
    QSqlQuery query("select max(shelter_id) from Shelter");

    if (query.next()) {
        int maxID = query.value(0).toInt();

        srand(time(0));
        int id = rand() % maxID + 1;

        query.prepare("select * from Shelter where shelter_id = ?");
        query.addBindValue(id);

        if (query.exec()) {
            while (query.next()) {
                int nameIndex = query.record().indexOf("name");
                QString name = query.value(nameIndex).toString();
                ASSERT_EQ(name.isEmpty(), false);
            }
        }
    }
}

TEST(TestRead,TestReadPet) {
    QSqlQuery query("select max(pet_id) from Pet");

    if (query.next()) {
        int maxID = query.value(0).toInt();

        srand(time(0));
        int id = rand() % maxID + 1;

        query.prepare("select * from Pet where pet_id = ?");
        query.addBindValue(id);

        if (query.exec()) {
            while (query.next()) {
                int nameIndex = query.record().indexOf("name");
                QString name = query.value(nameIndex).toString();
                ASSERT_EQ(name.isEmpty(), false);
            }
        }
    }
}

TEST (TestRead, TestReadDogsOnly) {
    QSqlQuery query;
    if (query.exec("select * from Pet where is_cat = 0")) {
        ASSERT_EQ(query.next(), true);
    } else {
        qDebug() << "Error querying dogs:" << query.lastError().text();
    }
}

TEST(TestRead, GetPetsFromShelter) {
    QSqlQuery query("select max(shelter_id) from Shelter");

    if (query.next()) {
        int maxID = query.value(0).toInt();

        srand(time(0));
        int id = rand() % maxID + 1;

        Shelter s(id);

        ASSERT_EQ(s.getPets().size() > 0, true);
    }
}

TEST(TestUtil, TestGetScore) {

}

TEST(TestUtil, TestSortPets) {
    srand(time(0));

    QSqlQuery query;
    query.prepare("select max(shelter_id) from shelter");
    if (query.exec()) {
        if (query.next()) {
            int randID = rand() % query.value(0).toInt();

            query.prepare("select * from pet where shelter_id = ?");
            query.addBindValue(randID);

            if (query.exec()) {
                std::vector<Pet> pets;

                while (query.next()) {
                    int pID = query.value(0).toInt();
                    pets.push_back(Pet(pID));
                }

                std::vector<std::pair<Pet, float>> sorted = sortByMatch(pets);
                ASSERT_FALSE(sorted.empty());
            } else {
                qDebug() << "Error fetching shelter's pets:" << query.lastError().text();
            }
        }
    } else {
        qDebug() << "Error getting max shelter ID:" << query.lastError().text();
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test_db.sqlite");

    if (!db.open())
        qFatal("Error opening database.");

    return RUN_ALL_TESTS();
}
