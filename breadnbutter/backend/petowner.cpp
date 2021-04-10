#include "petowner.h"

petOwner::petOwner()
{

}

void petOwner::chooseID()
{
    QSqlQuery query;
    int fieldNo = query.record().indexOf("adopter_id");

    if (query.exec("select max(adopter_id) from Adopter")) {
        if (query.next()) {
            int lastID = query.value(fieldNo).toInt();

            petOwnerID = lastID + 1;
        } else {
            petOwnerID = 1;
        }
    } else {
        std::cerr << "Error getting adopters: " << query.lastError().text().toStdString() << std::endl;
    }
}

bool petOwner::existsInDB()
{
    QSqlQuery query;
    query.prepare("select email from Adopter where email = ?");
    query.addBindValue(email);

    if (query.exec()) {
        while (query.next()) {
            QString dbEmail = query.value(0).toString();

            int compare = QString::compare(email, dbEmail, Qt::CaseInsensitive);
            if (compare == 0)
                return true;
        }
    } else {
        std::cerr << "Error getting adopters: " << query.lastError().text().toStdString() << std::endl;
    }

    return false;
}

petOwner::petOwner(QString p, QString f, QString l, QString e)
{
    this->password = p;
    this->firstName = f;
    this->lastName = l;
    this->email = e;

    chooseID();
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
    bool result;

    if (!existsInDB()) {
        QSqlQuery query;
        query.prepare("insert into Adopter (adopter_id, name, password, email)"
                      "values (?, ?, ?, ?)");
        query.addBindValue(petOwnerID);
        query.addBindValue(firstName + " " + lastName);
        query.addBindValue(password);
        query.addBindValue(email);

        result = query.exec();

        if (!result)
            std::cerr << query.lastError().text().toStdString() << std::endl;
    } else {
        result = false;
    }

    return result;
}

bool petOwner::deleteFromDB()
{
    QSqlQuery query;
    query.prepare("delete from PetOwner where pet_id = ?");
    query.addBindValue(petOwnerID);

    return query.exec();
}
