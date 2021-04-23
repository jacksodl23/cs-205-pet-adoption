#include "petowner.h"

void PetOwner::chooseID()
{
    QSqlQuery query;

    if (query.exec("select max(adopter_id) from Adopter")) {
        if (query.next()) {
            int lastID = query.value(0).toInt();

            petOwnerID = lastID + 1;
        } else {
            petOwnerID = 1;
        }
    } else {
        std::cerr << "Error getting adopters: " << query.lastError().text().toStdString() << std::endl;
    }
}

bool PetOwner::existsInDB()
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

bool PetOwner::attemptLogin()
{
    QSqlQuery query;
    query.prepare("select * from Adopter where email = ? and password = ?");
    query.addBindValue(email);
    query.addBindValue(password);

    if (query.exec()) {
        while (query.next()) {
            QString dbName = query.value(2).toString();
            int dbID = query.value(0).toInt();

            this->petOwnerID = dbID;

            return true;
        }
    } else {
        std::cerr << "Error attempting login: " << query.lastError().text().toStdString() << std::endl;
    }

    return false;
}

PetOwner::PetOwner()
{

}

PetOwner::PetOwner(int id)
{
    this->petOwnerID = id;

    QSqlQuery query;
    query.prepare("select * from User where user_id = ?");
    query.addBindValue(id);

    if (query.exec()) {
        if (query.next()) {
            QString aName = query.value(0).toString();
            QString aEmail = query.value(3).toString();
            QString aPassword = query.value(4).toString();

            this->email = aEmail;
            this->password = aPassword;
        }
    } else {
        qDebug() << "Error creating adopter:" << query.lastError().text();
    }
}

PetOwner::PetOwner(QString email, QString password)
{
    this->email = email;
    this->password = password;
}

PetOwner::PetOwner(QString p, QString f, QString l, QString e)
{
    this->password = p;
    this->firstName = f;
    this->lastName = l;
    this->email = e;

    chooseID();
}

QString PetOwner::getPassword()
{
    return password;
}

QString PetOwner::getFirstName()
{
    return firstName;
}

QString PetOwner::getLastName()
{
    return lastName;
}

QString PetOwner::getEmail()
{
    return email;
}

int PetOwner::getID()
{
    return petOwnerID;
}

int PetOwner::getAge()
{
    return this->p_age;
}

QString PetOwner::getBreed()
{
    return this->p_breed;
}

QString PetOwner::getColor()
{
    return this->p_color;
}

QString PetOwner::getHair()
{
    return this->p_hair_type;
}

int PetOwner::getWeight()
{
    return this->p_weight;
}

QString PetOwner::getOrigin()
{
    return this->p_origin;
}

bool PetOwner::getAllergy()
{
    return this->p_allergy;
}

void PetOwner::setPassword(QString p)
{
    this->password = p;
}

void PetOwner::setFirstName(QString fn)
{
    this->firstName = fn;
}

void PetOwner::setLastName(QString ln)
{
    this->lastName = ln;
}

void PetOwner::setEmail(QString e)
{
    this->email = e;
}

void PetOwner::setAge(int age)
{
    this->p_age = age;
}

void PetOwner::setBreed(QString breed)
{
    this->p_breed = breed;
}

void PetOwner::setColor(QString color)
{
    this->p_color = color;
}

void PetOwner::setHair(QString hair)
{
    this->p_hair_type = hair;
}

void PetOwner::setWeight(int weight)
{
    this->p_weight = weight;
}

void PetOwner::setOrigin(QString origin)
{
    this->p_origin = origin;
}

void PetOwner::setAllergy(bool a)
{
    this->p_allergy = a;
}

bool PetOwner::insertIntoDB()
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

bool PetOwner::deleteFromDB()
{
    bool result;

    QSqlQuery query;
    query.prepare("delete from Adopter where adopter_id = ?");
    query.addBindValue(petOwnerID);

    result = query.exec();

    if (!result)
        std::cerr << query.lastError().text().toStdString() << std::endl;

    return result;
}
