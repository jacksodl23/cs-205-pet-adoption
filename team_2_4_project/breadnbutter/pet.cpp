#include "pet.h"

Pet::Pet(QString name)
{
    this->name = name;
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
