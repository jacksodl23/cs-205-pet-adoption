#include <iostream>
#include <QtSql>

#include "gtest/gtest.h"
#include "../backend/petowner.h"

using namespace std;

class BackendTest : public ::testing::Test {
protected:
    PetOwner owner;
public:
    BackendTest() {
        owner = PetOwner("hello", "john", "smith", "johnsmith@gmail.com");
    }

    void SetUp() {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("test_db.sqlite");

        if (!db.open())
            qFatal("Error opening database.");
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

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
