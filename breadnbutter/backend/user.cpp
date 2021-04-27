#include "user.h"

User::User()
{

}

User::User(QString email, QString password)
{
    this->email = email;
    this->password = password;
}

User::~User()
{

}

bool User::insertInDB()
{
    return false;
}

bool User::deleteFromDB()
{
    return false;
}

bool User::existsInDB()
{
    return false;
}

bool User::attemptLogin()
{
    QSqlQuery query;
    query.prepare("select * from User where email = ? and password = ?");
    query.addBindValue(email);
    query.addBindValue(password);

    if (query.exec()) {
        while (query.next()) {
            int dbID = query.value(0).toInt();

            this->id = dbID;
            qDebug() << "Found user with ID" << dbID;

            return true;
        }
    } else {
        qDebug() << "Error logging in:" << query.lastError().text();
    }

    return false;
}

int User::getID()
{
    return id;
}

QString User::getFirstName()
{
    return firstName;
}

void User::chooseID()
{
    std::cerr << "Choosing ID..." << std::endl;
}
