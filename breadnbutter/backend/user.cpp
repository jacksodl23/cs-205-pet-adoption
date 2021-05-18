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
    bool result;

    if (!existsInDB()) {
        QSqlQuery query;
        query.prepare("insert into User (name, location_id, email, password, is_adopter)"
                      "values (?, ?, ?, ?, ?)");
        query.addBindValue(firstName + " " + lastName);
        query.addBindValue(locID);
        query.addBindValue(email);
        query.addBindValue(password);
        query.addBindValue(1);

        result = query.exec();

        if (!result)
            qDebug() << "Error inserting user:" << query.lastError().text();
    }

    return result;
}

bool User::deleteFromDB()
{
    bool result;

    QSqlQuery query;
    query.prepare("delete from User where user_id = ?");
    query.addBindValue(id);

    result = query.exec();

    if (!result)
        qDebug() << "Error deleting user:" << query.lastError().text();

    return result;
}

bool User::existsInDB()
{
    QSqlQuery query;
    query.prepare("select email from User where email = ?");
    query.addBindValue(email);

    if (query.exec()) {
        while (query.next()) {
            QString dbEmail = query.value(0).toString();

            int compare = QString::compare(email, dbEmail, Qt::CaseInsensitive);
            if (compare == 0)
                return true;
        }
    } else {
        qDebug() << "Error searching for user in DB:" << query.lastError().text();
    }

    return false;
}

bool User::likePet(Pet p)
{
    QSqlQuery query;
    query.prepare("insert into Liked_By (adopter_id, pet_id)"
                  "values (?, ?)");
    query.addBindValue(id);
    query.addBindValue(p.getPet_id());

    bool ok = query.exec();

    if (!ok)
        qDebug() << "Error liking pet:" << query.lastError().text();

    return ok;
}

bool User::attemptLogin()
{
    QSqlQuery query;
    query.prepare("select * from User where email = ? and password = ?");
    query.addBindValue(email);
    query.addBindValue(password);

    if (query.exec()) {
        if (query.next()) {
            int dbID = query.value(0).toInt();

            this->id = dbID;
            qDebug() << "Found user with ID" << dbID;

            return true;
        } else {
            qDebug() << "No user with the given email and password could be found.";
        }
    } else {
        qDebug() << "Error logging in:" << query.lastError().text();
    }

    return false;
}

void User::logOut()
{
    std::ofstream config("currentuser.config");
    config.close();
}

int User::getID()
{
    return id;
}

QString User::getFirstName()
{
    return firstName;
}

bool User::getIs_adopter() const
{
    return is_adopter;
}

QString User::getLastName() const
{
    return lastName;
}

QString User::getEmail() const
{
    return email;
}

QString User::getPhoneNumber() const
{
    return phoneNumber;
}

int User::getLocID() const
{
    return locID;
}

void User::chooseID()
{
    QSqlQuery query;
    
    if (query.exec("select max(user_id) from User")) {
        if (query.next()) {
            int lastID = query.value(0).toInt();

            id = lastID + 1;
        } else {
            id = 1;
        }
    } else {
        qDebug() << "Error getting highest adopter ID:" << query.lastError().text();
    }
}
