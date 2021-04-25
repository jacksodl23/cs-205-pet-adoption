#ifndef PET_H
#define PET_H

#include <iostream>
#include <QString>
#include <QtSql>

class Pet
{
public:
    Pet();
    Pet(int id);
    Pet(QString name, int age, QString breed, QString color, QString hairType, float weight, QString origin, QString allergy,  QString description);

    bool insertIntoDB();
    bool deleteFromDB();
private:
    int pet_id;

    QString name;
    int age;
    QString breed;

    QString color;
    QString hairType;

    float weight;
    QString origin;
    QString allergy;
    QString description;

    void chooseID();
    bool existsInDB();
};

#endif // PET_H
