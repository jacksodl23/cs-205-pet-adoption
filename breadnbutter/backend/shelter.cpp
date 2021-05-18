#include "shelter.h"

void Shelter::fetchInfoFromID(int id)
{
    QSqlQuery query;
    query.prepare("select * from shelter where shelter_id = ?");
    query.addBindValue(id);

    if (query.exec()) {
        if (query.next()) {
            int nameIndex = query.record().indexOf("name");
            int locIndex = query.record().indexOf("location_id");
            int emailIndex = query.record().indexOf("email");
            int ownerIndex = query.record().indexOf("owner_id");

            this->name = query.value(nameIndex).toString();
            this->location = new Location(query.value(locIndex).toInt());
            this->email = query.value(emailIndex).toString();
        }

        fetchPets();
    } else {
        qDebug() << "Error getting shelter info:" << query.lastError().text();
    }
}

Shelter::Shelter(int id)
{
    this->shelterID = id;

    fetchInfoFromID(id);
}

Shelter::Shelter(QString n, QString c, QString e) {
    this->name = n;

    QSqlQuery query;
    query.prepare("select location_id from location where city = ?");
    query.addBindValue(c);

    if (query.exec()) {
        if (query.next()) {
            this->location = new Location(query.value(0).toInt());
        } else {
            qDebug() << "No matching city could be found.";
        }
    } else {
        qDebug() << "Error fetching city:" << query.lastError().text();
    }

    this->email = e;
}

QString Shelter::getName()
{
    return name;
}

QString Shelter::getEmail()
{
    return email;
}

void Shelter::setName(QString n)
{
    this->name = n;
}

void Shelter::setEmail(QString e)
{
    this->email = e;
}

bool Shelter::insertIntoDB()
{
    bool ok;

    if (!existsInDB()) {
        QSqlQuery query;
        query.prepare("insert into Shelter (name, location_id, email)"
                      "values (?, ?, ?)");
        query.addBindValue(name);
        query.addBindValue(location->getLocID());
        query.addBindValue(email);

        ok = query.exec();

        if (!ok)
            std::cerr << query.lastError().text().toStdString() << std::endl;

        this->shelterID = query.lastInsertId().toInt();
    } else {
        ok = false;
    }

    return ok;
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
    query.prepare("select name from Shelter where name = ?");
    query.addBindValue(name);

    if (query.exec()) {
        while (query.next()) {
            QString dbLoc = query.value(0).toString();

            int compare = QString::compare(name, dbLoc, Qt::CaseInsensitive);
            if (compare == 0)
                return true;
        }
    } else {
        std::cerr << "Error getting shelters: " << query.lastError().text().toStdString() << std::endl;
    }

    return false;
}

std::vector<Pet> Shelter::getPets()
{
    return pets;
}

void Shelter::fetchPets()
{
    QSqlQuery query;
    query.prepare("select * from Pet "
                  "inner join Shelter on shelter.shelter_id = pet.shelter_id "
                  "where pet.shelter_id = ?");
    query.addBindValue(shelterID);

    if (query.exec()) {
        while (query.next()) {
            int pID = query.value(0).toInt();
            Pet p(pID);

            pets.push_back(p);
        }
    } else {
        qDebug() << "Error getting shelter's pets:" << query.lastError().text();
    }
}

Location *Shelter::getLocation() const
{
    return location;
}

ShelterOwner *Shelter::getOwner() const
{
    return owner;
}

void Shelter::setOwner(ShelterOwner *value)
{
    owner = value;
}

int Shelter::getShelterID() const
{
    return shelterID;
}

void Shelter::setShelterID(int value)
{
    shelterID = value;
}
