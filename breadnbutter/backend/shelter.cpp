#include "shelter.h"

/* Method that fetches information about the shelter based on its ID
 */
void Shelter::fetchInfoFromID(int id)
{
    // query statement that selects shelter from Shelter table based on its ID
    QSqlQuery query;
    query.prepare("select * from shelter where shelter_id = ?");
    query.addBindValue(id);

    // execute the query
    if (query.exec()) {
        if (query.next()) {
            int nameIndex = query.record().indexOf("name");
            int locIndex = query.record().indexOf("location_id");
            int emailIndex = query.record().indexOf("email");
            int ownerIndex = query.record().indexOf("owner_id");

            this->name = query.value(nameIndex).toString();
            this->locID = query.value(locIndex).toInt();
            this->email = query.value(emailIndex).toString();
        }

        fetchPets(); // fetch all pets
    } else {
        qDebug() << "Error getting shelter info:" << query.lastError().text();
    }
}

/* Constructor of the Shelter class that accepts ID
 */
Shelter::Shelter(int id)
{
    this->shelterID = id;

    fetchInfoFromID(id);
}

/* Constructor of the Shelter class that accepts name, city, and email
 */
Shelter::Shelter(QString n, QString c, QString e) {
    this->name = n;

    // query statement to select location_id from Location table based on city
    QSqlQuery query;
    query.prepare("select location_id from location where city = ?");
    query.addBindValue(c);

    // execute query
    if (query.exec()) {
        if (query.next()) {
            this->locID = query.value(0).toInt();
        } else {
            qDebug() << "No matching city could be found.";
        }
    } else {
        qDebug() << "Error fetching city:" << query.lastError().text();
    }

    this->email = e;
}

/* Accessor name to get name of the shelter
 */
QString Shelter::getName()
{
    return name;
}

/* Accessor name to get email of the shelter
 */
QString Shelter::getEmail()
{
    return email;
}

/* Mutator name to set name of the shelter
 */
void Shelter::setName(QString n)
{
    this->name = n;
}

/* Mutator method to set email of the shelter
 */
void Shelter::setEmail(QString e)
{
    this->email = e;
}

/* Database method to insert shelter to Shelter table
 */
bool Shelter::insertIntoDB()
{
    bool ok;

    if (!existsInDB()) {
        QSqlQuery query;
        query.prepare("insert into Shelter (name, location_id, email)"
                      "values (?, ?, ?)");
        query.addBindValue(name);
        query.addBindValue(locID);
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


/* Database method to delete shelter to Shelter table
 */
bool Shelter::deleteFromDB()
{
    QSqlQuery query;
    query.prepare("delete from Shelter where shelter_id = ?");
    query.addBindValue(shelterID);

    return query.exec();
}


/* Database method to check if shelter exists in the Shelter table
 */
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


/* Mutator method that gets shelter's pets vector
 */
std::vector<Pet> Shelter::getPets()
{
    return pets;
}

/* Method that fetches information about all pets of the shelter
 */
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

/* Accessor method that gets owner of the shelter
 */
ShelterOwner *Shelter::getOwner() const
{
    return owner;
}

/* Mutator method that sets shelter's owner
 */
void Shelter::setOwner(ShelterOwner *value)
{
    owner = value;
}

/* Accessor method that gets shelter's ID
 */
int Shelter::getShelterID() const
{
    return shelterID;
}

/* Mutator method that sets shelter's ID
 */
void Shelter::setShelterID(int value)
{
    shelterID = value;
}

/* Accessor method that gets location's ID
 */
int Shelter::getLocID() const
{
    return locID;
}
