#include <iostream>
#include <cstdlib>
#include <ctime>
#include <QtSql>

#include "gtest/gtest.h"
#include "../backend/petowner.h"
#include "../backend/shelter.h"
#include "../backend/pet.h"

using namespace std;

class BackendTest : public ::testing::Test {
protected:
    PetOwner owner;

public:
    BackendTest() {
        owner = PetOwner("hello", "john", "smith", "johnsmith@gmail.com");
    }

    void SetUp() {

    }
};

TEST_F(BackendTest, TestNewAdopter) {
    if (!owner.existsInDB())
        EXPECT_EQ(owner.insertIntoDB(), true);
    else
        EXPECT_EQ(owner.insertIntoDB(), false);
}

TEST_F(BackendTest, TestAdopterExists) {
    ASSERT_EQ(owner.existsInDB(), true);
}

TEST_F(BackendTest, TestLogin) {
    ASSERT_EQ(owner.attemptLogin(), true);
}

TEST_F(BackendTest, TestDeleteAdopter) {
    ASSERT_EQ(owner.deleteFromDB(), true);
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
                QString name = q2.value(1).toString();
                std::cout << "Found shelter named " << name.toStdString() << std::endl;
                ASSERT_EQ(name.isEmpty(), false);
            }
        }
    }
}

TEST(TestRead,TestReadPet) {
    QSqlQuery query("select max(pet_id) from Pet");

    while (query.next()) {
        int maxID = query.value(0).toInt();
        EXPECT_EQ(maxID, 100);

        srand(time(0));
        int id = rand() % maxID + 1;

        QSqlQuery q2;
        q2.prepare("select * from Pet where pet_id = ?");
        q2.addBindValue(id);

        if (q2.exec()) {
            while (q2.next()) {
                QString name = q2.value(1).toString();
                std::cout << "Found pet named " << name.toStdString() << std::endl;
                ASSERT_EQ(name.isEmpty(), false);
            }
        }
    }
}

TEST(TestRead, GetPetsFromShelter) {
    QSqlQuery query("select max(shelter_id) from Shelter");

    if (query.next()) {
        int maxID = query.value(0).toInt();
        EXPECT_EQ(maxID, 100);

        srand(time(0));
        int id = rand() % maxID + 1;

        QSqlQuery q2;
        q2.prepare("select * from Pet "
                   "inner join Shelter on shelter.shelter_id = pet.shelter_id "
                   "where pet.shelter_id = ?");
        q2.addBindValue(id);

        bool result = q2.exec();

        if (result) {
            while (q2.next()) {
                QString pName = q2.value(1).toString();
                QString sName = q2.value(5).toString();

                qDebug() << "Found pet named" << pName << "in shelter named" << sName;
            }
        } else {
            qDebug() << "Error getting pets from shelter:" << q2.lastError().text();
        }

        ASSERT_EQ(result, true);
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
