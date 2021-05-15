#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
#include <fstream>
#include "../backend/petowner.h"
#include "../backend/simplecrypt.h"
#include "../backend/globals.h"
#include "../backend/shelterowner.h"
#include "../backend/shelter.h"
#include "../backend/user.h"

namespace Ui {
class CreateAccount;
}

class CreateAccount : public QDialog
{
    Q_OBJECT

public:
    explicit CreateAccount(QWidget *parent = nullptr);
    ~CreateAccount();

    bool signUpSuccessful;

private slots:
    // void on_createOkay_accepted();

    void on_createOkay_clicked(QAbstractButton *button);

    void on_roleBox_activated(const QString &arg1);

private:
    Ui::CreateAccount *ui;
    void writeUserToFile(User newUser);

    void signUpAdopter(QString firstName, QString lastName, QString location, QString email, QString phone, QString password);
    void linkShelterOwnerToShelter(Shelter s, QString location, QString firstName, QString email, QString phone, QString lastName, QString password);
};

#endif // CREATEACCOUNT_H
