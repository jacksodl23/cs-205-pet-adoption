#ifndef SHELTER_H
#define SHELTER_H
#include <QString>
#include <QSql>

class shelter
{
public:
    shelter();
    shelter(QString n, QString l, int p){
        this->name = n;
        this->location = l;
        this->phoneNumber = p;
    }

    // accessor methods
    int getPhoneNumber();
    QString getName();
    QString getLocation();

    // database methods
    bool insertIntoDB();
    bool deleteFromDB();

private:
    int shelterID;
    QString name;
    QString location;
    int phoneNumber;
};

#endif // SHELTER_H
