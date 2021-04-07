#include "pet.h"

Pet::Pet()
{

}

bool Pet::insertIntoDB()
{
    QSqlQuery query;
    query.prepare("insert into Pet (name)"
                  "values (?)");
    query.addBindValue(name);

    return query.exec();
}

bool Pet::deleteFromDB()
{
    QSqlQuery query;
    query.prepare("delete from Pet where pet_id = ?");
    query.addBindValue(pet_id);

    return query.exec();
}
