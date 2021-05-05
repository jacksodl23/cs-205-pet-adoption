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

    bool insertIntoDB(int shelterID);
    bool deleteFromDB();
    QString getName();
    bool existsInDB();

    int getAge() const;

    QString getBreed() const;

    QString getColor() const;

    bool getHypoallergenic() const;

    int getPet_id() const;

    bool getIs_cat() const;

    QString getOrigin() const;

    QString getDescription() const;

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
};

#endif // PET_H
