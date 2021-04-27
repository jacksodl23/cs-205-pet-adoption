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

using namespace std;

class AdopterTest : public ::testing::Test {
protected:
    PetOwner *owner;

public:
    AdopterTest() {
        owner = new PetOwner("hello", "jonny", "appleseed", "themapples@gmail.com", "Seattle");
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

TEST_F(AdopterTest, TestLogin) {
    ASSERT_EQ(owner->attemptLogin(), true);
}

TEST_F(AdopterTest, TestDeleteAdopter) {
    ASSERT_EQ(owner->attemptLogin(), true);
}

TEST(TestRead, TestReadShelter) {
    QSqlQuery query("select max(shelter_id) from Shelter");

    if (query.next()) {
        int maxID = query.value(0).toInt();
        EXPECT_EQ(maxID, 100);

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
        EXPECT_EQ(maxID, 1000);

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

TEST(TestRead, GetPetsFromShelter) {
    QSqlQuery query("select max(shelter_id) from Shelter");
    std::vector<Pet> petsFromShelter;

    if (query.next()) {
        int maxID = query.value(0).toInt();
        EXPECT_EQ(maxID, 100);

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
