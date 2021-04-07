#include "petowner.h"

petOwner::petOwner()
{

}

QString petOwner::getUsername()
{
    return username;
}

QString petOwner::getPassword()
{
    return password;
}

QString petOwner::getFirstName()
{
    return firstName;
}

QString petOwner::getLastName()
{
    return lastName;
}

QString petOwner::getEmail()
{
    return email;
}

void petOwner::setUsername(QString u)
{
    this->username = u;
}

void petOwner::setPassword(QString p)
{
    this->password = p;
}

void petOwner::setFirstName(QString fn)
{
    this->firstName = fn;
}

void petOwner::setLastName(QString ln)
{
    this->lastName = ln;
}

void petOwner::setEmail(QString e)
{
    this->email = e;
}

bool petOwner::insertIntoDB()
{
    QSqlQuery query;
    query.prepare("insert into PetOwner (name)"
                  "values (?)");
    query.addBindValue(username);

    return query.exec();
}

bool petOwner::deleteFromDB()
{
    QSqlQuery query;
    query.prepare("delete from PetOwner where pet_id = ?");
    query.addBindValue(petOwnerID);

    return query.exec();
}
