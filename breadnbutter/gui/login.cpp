#include "login.h"
#include "ui_login.h"
#include "../backend/petowner.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    loginSuccessful = false;
}

Login::~Login()
{
    delete ui;
}

void Login::on_loginOkay_accepted()
{
    // where should we store user information?
    QString email = ui->emailField->text();
    QString password = ui->passwordField->text();
    QString welcomeMessage = "Welcome ";

    PetOwner owner(email, password);
    if (owner.attemptLogin()) {
        welcomeMessage.append(email);
        welcomeMessage.append(" to this amazing app!");
        welcomeMessage.append("\nYour password is ");
        welcomeMessage.append(password);
        welcomeMessage.append("\nYour ID is ");
        welcomeMessage.append(QString::number(owner.getID()));
        QMessageBox::information(this, "Login", welcomeMessage);
    } else {
        QMessageBox::critical(this, "Error Logging In!", "Something went wrong while trying to log you in. Please try again.");
    }


    loginSuccessful = true;

    // for adding the next window - pet display   https://www.youtube.com/watch?v=6_elY8O20I8&list=PLS1QulWo1RIZiBcTr5urECberTITj7gjA&index=10
}
