#include "pet.h"

// Pet age getter method
int Pet::getAge() const
{
    return age;
}

// Pet breed getter method
QString Pet::getBreed() const
{
    return breed;
}

// Pet color getter method
QString Pet::getColor() const
{
    return color;
}

// Pet hypoallergenic status getter method
bool Pet::getHypoallergenic() const
{
    return hypoallergenic;
}

// Pet ID getter method
int Pet::getPet_id() const
{
    return pet_id;
}

// Pet cat status getter method
bool Pet::getIs_cat() const
{
    return is_cat;
}

// Pet origin getter method
// Breeder, shelter, or rescue
QString Pet::getOrigin() const
{
    return origin;
}

// Pet description getter method
QString Pet::getDescription() const
{
    return description;
}

// Pet weight getter method
float Pet::getWeight() const
{
    return weight;
}

// Pet hair length getter method
QString Pet::getHairLength() const
{
    return hairLength;
}

// Pet backup constructor
Pet::Pet()
{
    this->name = nullptr;
    this->breed = nullptr;
    this->color = nullptr;
    this->hairLength = nullptr;
    this->description = nullptr;
    this->is_cat = -1;
    this->age = -1;
    this->weight = -1;
    this->origin = nullptr;
    this->hypoallergenic = -1;
}

/*
 * Pet constructor using Pet ID arguement
 * this constructor allows for initializing and creating
 * a Pet object using a Pet ID from the database
 */
Pet::Pet(int id)
{
    // setting Pet object's ID
    this->pet_id = id;

    // select query to get Pet information from database
    QSqlQuery query;
    query.prepare("select * from pet where pet_id = ?");
    query.addBindValue(id);

    // attempting to execute select query
    if (query.exec()) {
        if (query.next()) {
            // getting the database table indicies of Pet attributes (columns)
            int nameIndex = query.record().indexOf("name");
            int breedIndex = query.record().indexOf("breed");
            int colorIndex = query.record().indexOf("color");
            int hairLenIndex = query.record().indexOf("hair_length");
            int descIndex = query.record().indexOf("description");
            int isCatIndex = query.record().indexOf("is_cat");
            int ageIndex = query.record().indexOf("age");
            int weightIndex = query.record().indexOf("weight");
            int origIndex = query.record().indexOf("origin");
            int allerIndex = query.record().indexOf("hypoallergenic");

            // getting all Pet info from database using indicies
            QString pName = query.value(nameIndex).toString();
            QString pBreed = query.value(breedIndex).toString();
            QString pColor = query.value(colorIndex).toString();
            QString pHairLength = query.value(hairLenIndex).toString();
            QString pDescription = query.value(descIndex).toString();
            int pIsCat = query.value(isCatIndex).toInt();
            int pAge = query.value(ageIndex).toInt();
            int pWeight = query.value(weightIndex).toFloat();
            QString pOrigin = query.value(origIndex).toString();
            int pAller = query.value(allerIndex).toInt();

            // initializing all Pet information
            this->name = pName;
            this->breed = pBreed;
            this->color = pColor;
            this->hairLength = pHairLength;
            this->description = pDescription;
            this->is_cat = pIsCat == 1;
            this->age = pAge;
            this->weight = pWeight;
            this->origin = pOrigin;
            this->hypoallergenic = pAller == 1;
        }
    } else { // unable to execute Pet select query
        qDebug() << "Error creating pet:" << query.lastError().text();
    }
}

/*
 * Pet default constructor with all Pet information
 * as arguments, used to initialize a Pet without pulling
 * from a database
 */
Pet::Pet(bool is_cat, QString name, int age, QString breed, QString color, QString hairLength, float weight, QString origin, bool hypoallergenic, QString description)
{
    // initializing all class members
    this->is_cat = is_cat;
    this->name = name;
    this->age = age;
    this->breed = breed;
    this->color = color;
    this->hairLength = hairLength;
    this->weight = weight;
    this->origin = origin;
    this->hypoallergenic = hypoallergenic;
    this->description = description;
}

/*
 * insertIntoDB() uses an insert SQL statement
 * to insert a Pet object's information/data members into the
 * application database
 */
bool Pet::insertIntoDB(int shelterID)
{
    // boolean for checking successful insertion
    bool ok;

    // insert query
    QSqlQuery query;
    query.prepare("insert into Pet (name, shelter_id, color, hair_length, description, is_cat, age, breed, weight, origin, hypoallergenic)"
                  "values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)");

    // adding all Pet data to the query
    query.addBindValue(name);
    query.addBindValue(shelterID);
    query.addBindValue(color);
    query.addBindValue(hairLength);
    query.addBindValue(description);
    query.addBindValue(int(is_cat));
    query.addBindValue(age);
    query.addBindValue(breed);
    query.addBindValue(weight);
    query.addBindValue(origin);
    query.addBindValue(int(hypoallergenic));

    // attempting to execute the insert query
    ok = query.exec();

    // checking for query success
    if (!ok)
        qDebug() << "Error inserting pet:" << query.lastError().text();

    // returning wheter or not the query was successful
    return ok;
}

/*
 * deleteFromDB() uses a delete query and the
 * Pet ID from this instance of a Pet to remove the
 * Pet information from the application database
 */
bool Pet::deleteFromDB()
{
    // delete query
    QSqlQuery query;
    query.prepare("delete from pet where pet_id = ?");
    query.addBindValue(pet_id);

    // return whether or not the deletion was successful
    return query.exec();
}

// simple getter method that returns this Pet's name
QString Pet::getName()
{
    return name;
}
