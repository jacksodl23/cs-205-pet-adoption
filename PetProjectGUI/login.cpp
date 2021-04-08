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
    QString email = ui->emailField->text();
    QString password = ui->passwordField->text();
    QString welcomeMessage = "Welcome ";
    welcomeMessage.append(email);
    welcomeMessage.append(" to this amazing app!");
    welcomeMessage.append("\nYour password is ");
    welcomeMessage.append(password);
    QMessageBox::information(this, "Login", welcomeMessage);
}
