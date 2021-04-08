#include "shelter.h"

shelter::shelter()
{

}

bool shelter::insertIntoDB()
{
    QSqlQuery query;
    query.prepare("insert into Shelter (name)"
                  "values (?)");
    query.addBindValue(name);

    return query.exec();
}

bool shelter::deleteFromDB()
{
    QSqlQuery query;
    query.prepare("delete from Shelter where shelterID = ?");
    query.addBindValue(shelterID);

    return query.exec();
}
