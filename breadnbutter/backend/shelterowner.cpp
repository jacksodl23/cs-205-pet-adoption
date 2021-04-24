#include "shelterowner.h"

ShelterOwner::ShelterOwner()
{

}

ShelterOwner::ShelterOwner(int id)
{

}

ShelterOwner::ShelterOwner(QString fn, QString ln, QString loc, QString e, QString p)
{
    this->firstName = fn;
    this->lastName = ln;
    this->location = loc;
    this->email = e;
    this->password = p;

    chooseID();
}

bool ShelterOwner::insertInDB()
{
    bool result;

    if (!existsInDB()) {
        QSqlQuery query;
        query.prepare("insert into User (name, location, email, password, is_adopter)"
                      "values (?, ?, ?, ?, ?)");
        query.addBindValue(firstName + " " + lastName);
        query.addBindValue(location);
        query.addBindValue(email);
        query.addBindValue(password);
        query.addBindValue(0);

        result = query.exec();

        if (!result)
            qDebug() << "Error inserting adopter:" << query.lastError().text();
    }

    return result;
}

bool ShelterOwner::deleteFromDB()
{
    bool result;

    QSqlQuery query;
    query.prepare("delete from User where user_id = ?");
    query.addBindValue(petOwnerID);

    result = query.exec();

    if (!result)
        std::cerr << query.lastError().text().toStdString() << std::endl;

    return result;
}

bool ShelterOwner::existsInDB()
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
        qDebug() << "Error searching for adopter in DB:" << query.lastError().text();
    }

    return false;
}

bool ShelterOwner::attemptLogin()
{
    QSqlQuery query;
    query.prepare("select * from User where email = ? and password = ?");
    query.addBindValue(email);
    query.addBindValue(password);

    if (query.exec()) {
        while (query.next()) {
            int dbID = query.value(0).toInt();

            this->ownerID = dbID;

            return true;
        }
    } else {
        qDebug() << "Error logging in:" << query.lastError().text();
    }

    return false;
}

void ShelterOwner::chooseID()
{
    QSqlQuery query;

    if (query.exec("select max(user_id) from User")) {
        if (query.next()) {
            int lastID = query.value(0).toInt();

            ownerID = lastID + 1;
        } else {
            ownerID = 1;
        }
    } else {
        qDebug() << "Error getting highest adopter ID:" << query.lastError().text();
    }
}
