#ifndef PETOWNER_H
#define PETOWNER_H
#include <QString>
#include <QSql>

class petOwner
{
public:
    petOwner();

    // accessor methods
    QString getUsername();
    QString getPassword();
    QString getFirstName();
    QString getLastName();
    QString getEmail();

    // mutator methods
    void setUsername(QString u);
    void setPassword(QString p);
    void setFirstName(QString fn);
    void setLastName(QString ln);
    void setEmail(QString e);

    // database methods
    bool insertIntoDB();
    bool deleteFromDB();

private:
    int petOwnerID;
    QString username;
    QString password;
    QString firstName;
    QString lastName;
    QString email;
};

#endif // PETOWNER_H
