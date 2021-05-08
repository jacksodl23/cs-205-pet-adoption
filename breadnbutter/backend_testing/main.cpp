#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <QtSql>

#include "gtest/gtest.h"
#include "../backend/petowner.h"
#include "../backend/shelter.h"
#include "../backend/pet.h"
#include "../backend/user.h"
#include "../gui/shelterprofilesqlmodel.h"

using namespace std;

class AdopterTest : public ::testing::Test {
protected:
    PetOwner *owner;

public:
    AdopterTest() {
        owner = new PetOwner("hello", "jonny", "appleseed", "themapples@gmail.com", "Seattle");
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
    if (!owner->existsInDB())
        EXPECT_EQ(owner->insertInDB(), true);
    else
        EXPECT_EQ(owner->insertInDB(), false);
}

TEST_F(AdopterTest, TestAdopterExists) {
    ASSERT_EQ(owner->existsInDB(), true);
}

/* TEST_F(AdopterTest, TestLogin) {
    ASSERT_EQ(owner->attemptLogin(), true);
}

TEST_F(AdopterTest, TestDeleteAdopter) {
    ASSERT_EQ(owner->attemptLogin(), true);
} */

TEST_F(PetTest, TestInsertPet) {
    if (pet->existsInDB())
        ASSERT_EQ(pet->insertIntoDB(100), false);
    else
        ASSERT_EQ(pet->insertIntoDB(100), true);
}

TEST_F(ShelterTest, TestInsertShelter) {
    if (shelter->existsInDB())
        ASSERT_EQ(shelter->insertIntoDB(), false);
    else
        ASSERT_EQ(shelter->insertIntoDB(), true);
}

TEST(TestRead, TestReadShelter) {
    QSqlQuery query("select max(shelter_id) from Shelter");

    if (query.next()) {
        int maxID = query.value(0).toInt();

        srand(time(0));
        int id = rand() % maxID + 1;

        QSqlQuery q2;
        q2.prepare("select * from Shelter where shelter_id = ?");
        q2.addBindValue(id);

        if (q2.exec()) {
            while (q2.next()) {
                QString name = q2.value(2).toString();
                qDebug() << "Found shelter named" << name;
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

        QSqlQuery q2;
        q2.prepare("select * from Pet where pet_id = ?");
        q2.addBindValue(id);

        if (q2.exec()) {
            while (q2.next()) {
                QString name = q2.value(1).toString();
                qDebug() << "Found pet named" << name;
                ASSERT_EQ(name.isEmpty(), false);
            }
        }
    }
}

TEST (TestRead, TestReadDogsOnly) {
    QSqlQuery query;
    if (query.exec("select * "
                   "from Pet "
                   "inner join Pet_Attributes on Pet_Attributes.pet_att_id = Pet.pet_attribute_id "
                   "where Pet_Attributes.is_cat = 0")) {
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

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("test_db.sqlite");

    if (!db.open())
        qFatal("Error opening database.");

    return RUN_ALL_TESTS();
}
