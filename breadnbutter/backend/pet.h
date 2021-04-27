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
    Pet(bool is_cat, QString name, int age, QString breed, QString color, QString hairLength, float weight, QString origin, bool hypoallergenic, QString description);

    bool insertIntoDB();
    bool deleteFromDB();
    QString getName();
    bool existsInDB();

private:
    int pet_id;
    bool is_cat;

    QString name;
    int age;
    QString breed;

    QString color;
    QString hairLength;

    float weight;
    QString origin;
    bool hypoallergenic;
    QString description;

    void chooseID();
};

#endif // PET_H
