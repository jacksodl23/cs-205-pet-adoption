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
            QString pName = query.value(1).toString();
            QString pColor = query.value(4).toString();
            QString pHairLength = query.value(5).toString();
            QString pDescription = query.value(6).toString();
            int pIsCat = query.value(9).toInt();
            int pAge = query.value(10).toInt();
            int pWeight = query.value(12).toFloat();
            QString pOrigin = query.value(13).toString();
            int pAller = query.value(14).toInt();

            this->name = pName;
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
    QSqlQuery query;
    query.prepare("insert into pet (name) "
                  "values (?)");
    query.addBindValue(name);

    bool result = query.exec();

    if (!result)
        std::cerr << "Query error: " << query.lastError().text().toStdString() << std::endl;

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
