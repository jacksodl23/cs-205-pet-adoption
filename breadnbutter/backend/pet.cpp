#include "pet.h"

bool Pet::existsInDB()
{
    QSqlQuery query;
    query.prepare("select name from Pet where name = ?");
    query.addBindValue(name);

    if (query.exec()) {
        while (query.next()) {
            QString dbName = query.value(0).toString();

            int compare = QString::compare(name, dbName, Qt::CaseInsensitive);
            if (compare == 0)
                return true;
        }
    } else {
        std::cerr << "Error getting pets: " << query.lastError().text().toStdString() << std::endl;
    }

    return false;
}

int Pet::getAge() const
{
    return age;
}

QString Pet::getBreed() const
{
    return breed;
}

QString Pet::getColor() const
{
    return color;
}

bool Pet::getHypoallergenic() const
{
    return hypoallergenic;
}

int Pet::getPet_id() const
{
    return pet_id;
}

bool Pet::getIs_cat() const
{
    return is_cat;
}

QString Pet::getOrigin() const
{
    return origin;
}

QString Pet::getDescription() const
{
    return description;
}

Pet::Pet()
{
    
}

Pet::Pet(int id)
{
    this->pet_id = id;

    QSqlQuery query;
    query.prepare("select * from pet "
                  "inner join pet_attributes on pet_attributes.pet_att_id = pet.pet_attribute_id "
                  "where pet.pet_id = ?");
    query.addBindValue(id);

    if (query.exec()) {
        if (query.next()) {
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
    } else {
        qDebug() << "Error creating pet:" << query.lastError().text();
    }
}

Pet::Pet(bool is_cat, QString name, int age, QString breed, QString color, QString hairLength, float weight, QString origin, bool hypoallergenic, QString description)
{
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

bool Pet::insertIntoDB(int shelterID)
{
    bool result;

    if (!existsInDB()) {
        QSqlQuery query;
        query.prepare("insert into Pet (name, shelter_id, color, hair_length, description)"
                      "values (?, ?, ?, ?, ?)");
        query.addBindValue(name);
        query.addBindValue(shelterID);
        query.addBindValue(color);
        query.addBindValue(hairLength);
        query.addBindValue(description);

        if (query.exec()) {
            int pInsertID = query.lastInsertId().toInt();
            this->pet_id = pInsertID;

            QSqlQuery q2;
            q2.prepare("insert into Pet_Attributes (is_cat, age, breed, weight, origin, hypoallergenic) "
                       "values (?, ?, ?, ?, ?, ?)");
            q2.addBindValue(int(is_cat));
            q2.addBindValue(age);
            q2.addBindValue(breed);
            q2.addBindValue(weight);
            q2.addBindValue(origin);
            q2.addBindValue(int(hypoallergenic));

            if (q2.exec()) {
                QSqlQuery q3;
                q3.prepare("update pet set pet_attribute_id = ? where pet_id = ?");

                int insertID = q2.lastInsertId().toInt();
                q3.addBindValue(insertID);
                q3.addBindValue(pet_id);

                result = q3.exec();

                if (!result) {
                    qDebug() << "Error linking pet attribute to pet:" << q3.lastError().text();
                }
            } else {
                qDebug() << "Error inserting pet attributes:" << q2.lastError().text();
                result = false;
            }
        } else {
            qDebug() << "Error inserting pet:" << query.lastError().text();
            result = false;
        }
    } else {
        qDebug() << "Pet already exists in database.";
        result = false;
    }

    return result;
}

bool Pet::deleteFromDB()
{
    QSqlQuery query;
    query.prepare("delete from pet where pet_id = ?");
    query.addBindValue(pet_id);

    return query.exec();
}

QString Pet::getName()
{
    return name;
}
