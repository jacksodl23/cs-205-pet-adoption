#ifndef SHELTER_H
#define SHELTER_H
#include <QString>
#include <QtSql>

class shelter
{
public:
    shelter();
    shelter(QString n, QString l, int p, QString e){
        this->name = n;
        this->location = l;
        this->phoneNumber = p;
        this->email = e;
    }

    // accessor methods
    int getPhoneNumber();
    QString getName();
    QString getLocation();
    QString getEmail();

    // mutator methods
    void setPhoneNumber(int p);
    void setName(QString n);
    void setLocation(QString l);
    void setEmail(QString e);

    // database methods
    bool insertIntoDB();
    bool deleteFromDB();

private:
    int shelterID;
    QString name;
    QString location;
    QString email;
    int phoneNumber;
};

#endif // SHELTER_H
