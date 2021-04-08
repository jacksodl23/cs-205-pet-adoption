#include "petowner.h"

petOwner::petOwner()
{

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

int petOwner::getAge()
{
    return this->p_age;
}

QString petOwner::getBreed()
{
    return this->p_breed;
}

QString petOwner::getColor()
{
    return this->p_color;
}

QString petOwner::getHair()
{
    return this->p_hair_type;
}

int petOwner::getWeight()
{
    return this->p_weight;
}

QString petOwner::getOrigin()
{
    return this->p_origin;
}

bool petOwner::getAllergy()
{
    return this->p_allergy;
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

void petOwner::setAge(int age)
{
    this->p_age = age;
}

void petOwner::setBreed(QString breed)
{
    this->p_breed = breed;
}

void petOwner::setColor(QString color)
{
    this->p_color = color;
}

void petOwner::setHair(QString hair)
{
    this->p_hair_type = hair;
}

void petOwner::setWeight(int weight)
{
    this->p_weight = weight;
}

void petOwner::setOrigin(QString origin)
{
    this->p_origin = origin;
}

void petOwner::setAllergy(bool a)
{
    this->p_allergy = a;
}

bool petOwner::insertIntoDB()
{
    QSqlQuery query;
    query.prepare("insert into PetOwner (name)"
                  "values (?)");
    query.addBindValue(firstName + " " + lastName);

    return query.exec();
}

bool petOwner::deleteFromDB()
{
    QSqlQuery query;
    query.prepare("delete from PetOwner where pet_id = ?");
    query.addBindValue(petOwnerID);

    return query.exec();
}
