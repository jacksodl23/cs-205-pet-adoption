#include "createaccount.h"
#include "ui_createaccount.h"

CreateAccount::CreateAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAccount)
{
    ui->setupUi(this);
}

CreateAccount::~CreateAccount()
{
    delete ui;
}

void CreateAccount::on_createOkay_accepted()
{
    QString firstName = ui->firstNameField->text();
    QString lastName = ui->lastNameField->text();
    QString email = ui->emailField->text();
    QString password = ui->passwordField->text();
    QString confirmPassword = ui->passwordField_2->text();
    QString welcomeMessage = "Welcome ";
    welcomeMessage.append(firstName);
    welcomeMessage.append(" ");
    welcomeMessage.append(lastName);
    welcomeMessage.append(",  ");
    welcomeMessage.append(email);
    welcomeMessage.append(" to this amazing app!");
    welcomeMessage.append("\nYour password: ");
    welcomeMessage.append(password);
    welcomeMessage.append("\nYour confirmed password: ");
    welcomeMessage.append(confirmPassword);
    QMessageBox::information(this, "Login", welcomeMessage);

}
