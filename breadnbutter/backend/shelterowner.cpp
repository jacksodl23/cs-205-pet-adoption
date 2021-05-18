#include "shelterowner.h"

ShelterOwner::~ShelterOwner()
{

}

ShelterOwner::ShelterOwner(QString email, QString password)
{
    this->email = email;
    this->password = password;
}

ShelterOwner::ShelterOwner(int id)
{
    this->id = id;

    QSqlQuery query;
    query.prepare("select * from User where user_id = ?");
    query.addBindValue(id);

    if (query.exec()) {
        if (query.next()) {
            int nameIndex = query.record().indexOf("name");
            int emailIndex = query.record().indexOf("email");
            int passwordIndex = query.record().indexOf("password");
            int phoneIndex = query.record().indexOf("phone");

            QString aName = query.value(nameIndex).toString();
            QString aEmail = query.value(emailIndex).toString();
            QString aPassword = query.value(passwordIndex).toString();
            QString aPhoneNum = query.value(phoneIndex).toString();

            QStringList pieces = aName.split(" ");
            for (int i = 0; i < pieces.size(); i++) {
                if (i == 0)
                    this->firstName = pieces.at(i);
                else if (i == 1)
                    this->lastName = pieces.at(i);
            }

            this->email = aEmail;
            this->password = aPassword;
            this->phoneNumber = aPhoneNum;
        }
    } else {
        qDebug() << "Error creating adopter:" << query.lastError().text();
    }
}

ShelterOwner::ShelterOwner(QString fn, QString ln, QString city, QString e, QString ph, QString p)
{
    this->firstName = fn;
    this->lastName = ln;

    QSqlQuery query;
    query.prepare("select location_id from location where city = ?");
    query.addBindValue(city);

    if (query.exec()) {
        if (query.next()) {
            this->location = new Location(query.value(0).toInt());
        } else {
            qDebug() << "No matching city could be found.";
        }
    } else {
        qDebug() << "Error fetching location:" << query.lastError().text();
    }

    this->email = e;
    this->phoneNumber = ph;
    this->password = p;
}

bool ShelterOwner::insertInDB()
{
    bool result;

    if (!existsInDB()) {
        QSqlQuery query;
        query.prepare("insert into User (name, location_id, email, phone, password, is_adopter)"
                      "values (?, ?, ?, ?, ?, ?)");
        query.addBindValue(firstName + " " + lastName);
        query.addBindValue(location->getLocID());
        query.addBindValue(email);
        query.addBindValue(phoneNumber);
        query.addBindValue(password);
        query.addBindValue(0);

        result = query.exec();

        if (!result)
            qDebug() << "Error inserting shelter owner:" << query.lastError().text();

        id = query.lastInsertId().toInt();
    }

    return result;
}

bool ShelterOwner::deleteFromDB()
{
    bool result;

    QSqlQuery query;
    query.prepare("delete from User where user_id = ?");
    query.addBindValue(id);

    result = query.exec();

    if (!result)
        qDebug() << "Error deleting shelter owner:" << query.lastError().text();

    return result;
}

bool ShelterOwner::existsInDB()
{
    QSqlQuery query;
    query.prepare("select email from User where email = ?");
    query.addBindValue(email);

    if (query.exec()) {
        while (query.next()) {
            int emailIndex = query.record().indexOf("email");
            QString dbEmail = query.value(emailIndex).toString();

            int compare = QString::compare(email, dbEmail, Qt::CaseInsensitive);
            if (compare == 0)
                return true;
        }
    } else {
        qDebug() << "Error searching for adopter in DB:" << query.lastError().text();
    }

    return false;
}
