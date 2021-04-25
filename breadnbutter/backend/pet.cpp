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
}

Pet::Pet(QString name, int age, QString breed, QString color, QString hairType, float weight, QString origin, QString allergy, QString description)
{
    this->name = name;
    this->age = age;
    this->breed = breed;
    this->color = color;
    this->hairType = hairType;
    this->weight = weight;
    this->origin = origin;
    this->allergy = allergy;
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
