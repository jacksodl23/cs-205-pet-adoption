#include "pet.h"

void Pet::chooseID()
{
    QSqlQuery query;

    if (query.exec("select max(pet_id) from Pet")) {
        if (query.next()) {
            int lastID = query.value(0).toInt();
            pet_id = lastID + 1;
        } else {
            pet_id = 1;
        }
    } else {
        std::cerr << "Error getting pets: " << query.lastError().text().toStdString() << std::endl;
    }
}

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

    chooseID();
}

bool Pet::insertIntoDB()
{
    bool result;

    if (!existsInDB()) {
        QSqlQuery query;
        query.prepare("insert into Pet (pet_id, name)"
                      "values (?, ?)");
        query.addBindValue(pet_id);
        query.addBindValue(name);

        result = query.exec();

        if (!result){
            std::cerr << query.lastError().text().toStdString() << std::endl;
        }
    }
    else {
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
