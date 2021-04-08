#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
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
    welcomeMessage.append(email);
    welcomeMessage.append(" to this amazing app!");
    welcomeMessage.append("\nYour password is ");
    welcomeMessage.append(password);
    QMessageBox::information(this, "Login", welcomeMessage);

//	for adding the next window - pet display   https://www.youtube.com/watch?v=6_elY8O20I8&list=PLS1QulWo1RIZiBcTr5urECberTITj7gjA&index=10
    /*
     * hide()
    petDisplay = new PetDisplay(this);
    petDisplay->show();
    */
}
