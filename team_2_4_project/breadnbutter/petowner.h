#ifndef PETOWNER_H
#define PETOWNER_H
#include <QString>
#include <QtSql>

class petOwner
{
public:
    petOwner();
    petOwner(QString u, QString p, QString f, QString l, QString e){
        this->password = p;
        this->firstName = f;
        this->lastName = l;
        this->email = e;
    }

    // accessor methods
    QString getPassword();
    QString getFirstName();
    QString getLastName();
    QString getEmail();

    int getAge();
    QString getBreed();
    QString getColor();
    QString getHair();
    int getWeight();
    QString getOrigin();
    bool getAllergy();

    // mutator methods
    void setPassword(QString p);
    void setFirstName(QString fn);
    void setLastName(QString ln);
    void setEmail(QString e);

    void setAge(int age);
    void setBreed(QString breed);
    void setColor(QString color);
    void setHair(QString hair);
    void setWeight(int weight);
    void setOrigin(QString origin);
    void setAllergy(bool a);

    // database methods
    bool insertIntoDB();
    bool deleteFromDB();

private:
    int petOwnerID;
    QString password;
    QString firstName;
    QString lastName;
    QString email;

    // preferences
    int p_age;
    QString p_breed;
    QString p_color;
    QString p_hair_type;
    int p_weight;
    QString p_origin;
    bool p_allergy;
};

#endif // PETOWNER_H
