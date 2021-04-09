#include <iostream>
#include <QtSql>

#include "gtest/gtest.h"
#include "../backend/petowner.h"

using namespace std;

class BackendTest : public ::testing::Test {
public:
    void SetUp() {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("test_db.sqlite");

        if (!db.open())
            qFatal("Error opening database.");
    }
};

TEST_F(BackendTest, TestNewAdopter) {
    petOwner owner("hello", "john", "smith", "johnsmith@gmail.com");

    ASSERT_EQ(owner.insertIntoDB(), true);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
