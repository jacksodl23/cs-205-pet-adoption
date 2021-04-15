#include "shelter.h"

Shelter::Shelter(int id)
{
    this->shelterID = id;
}

Shelter::Shelter(QString n, QString l, int p, QString e) {
    this->name = n;
    this->location = l;
    this->phoneNumber = p;
    this->email = e;
}

int Shelter::getPhoneNumber()
{
    return phoneNumber;
}

QString Shelter::getName()
{
    return name;
}

QString Shelter::getLocation()
{
    return location;
}

QString Shelter::getEmail()
{
    return email;
}

void Shelter::setPhoneNumber(int p)
{
    this->phoneNumber = p;
}

void Shelter::setName(QString n)
{
    this->name = n;
}

void Shelter::setLocation(QString l)
{
    this->location = l;
}

void Shelter::setEmail(QString e)
{
    this->email = e;
}

bool Shelter::insertIntoDB()
{
    bool result;

    if (!existsInDB()) {
        QSqlQuery query;
        query.prepare("insert into Shelter (shelterID, name, location, email, phoneNumber)"
                      "values (?, ?, ?, ?, ?)");
        query.addBindValue(shelterID);
        query.addBindValue(name);
        query.addBindValue(location);
        query.addBindValue(email);
        query.addBindValue(phoneNumber);

        result = query.exec();

        if (!result)
            std::cerr << query.lastError().text().toStdString() << std::endl;
    } else {
        result = false;
    }

    return result;
}

bool Shelter::deleteFromDB()
{
    QSqlQuery query;
    query.prepare("delete from Shelter where shelter_id = ?");
    query.addBindValue(shelterID);

    return query.exec();
}

bool Shelter::existsInDB()
{
    QSqlQuery query;
    query.prepare("select location from Shelter where location = ?");
    query.addBindValue(location);

    if (query.exec()) {
        while (query.next()) {
            QString dbLoc = query.value(0).toString();

            int compare = QString::compare(location, dbLoc, Qt::CaseInsensitive);
            if (compare == 0)
                return true;
        }
    } else {
        std::cerr << "Error getting shelters: " << query.lastError().text().toStdString() << std::endl;
    }

    return false;
}
