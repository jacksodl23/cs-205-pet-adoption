#include "login.h"
#include "ui_login.h"
#include "../backend/petowner.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    ui->loginOkay->button(QDialogButtonBox::Ok)->setText("Login");
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
        //QMessageBox::setTextFormat(QColor(255,255,255,127));
        QMessageBox::information(this, "Welcome!", welcomeMessage);
        //QMessageBox welcomeBox;
        //welcomeBox.setText(welcomeMessage);
        //welcomeBox.exec();

    } else {
        QMessageBox::critical(this, "Error Logging In", "Something went wrong while trying to log you in. Please try again.");
        //QMessageBox errorBox;
        //errorBox.setText("Error Logging In!\nSomething went wrong while trying to log you in. Please try again.");
        //errorBox.exec();
    }


    loginSuccessful = true;

}
