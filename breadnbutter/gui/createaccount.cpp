#include "createaccount.h"
#include "ui_createaccount.h"

CreateAccount::CreateAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAccount)
{
    ui->setupUi(this);
    ui->createOkay->button(QDialogButtonBox::Ok)->setText("Sign up!");
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
//    QString welcomeMessage = "Welcome ";

    if (password != confirmPassword) {
        QMessageBox::critical(this, "Error!", "Passwords do not match - try again!");
        //QMessageBox passwordErrorBox;
        //passwordErrorBox.setText("Error!\nPasswords do not match - try again!");
        //passwordErrorBox.exec();
        return;
    }

    // what about shelter owner?

    PetOwner newOwner(password, firstName, lastName, email);

    if (newOwner.insertIntoDB()) {
        signUpSuccessful = true;

        std::ofstream config("currentuser.config");

        SimpleCrypt crypto(CRYPTO_KEY);
        QString id = QString::number(newOwner.getID());
        QString encoded = crypto.encryptToString(id);

        config << encoded.toStdString();
        config.close();
    } else {
        if (newOwner.existsInDB()) {
            QMessageBox::critical(this, "Email taken!", "This email is already taken. Please try again.");
            //QMessageBox databaseErrorBox;
            //databaseErrorBox.setText("Email taken!\nThis email is already taken. Please try again.");
            //databaseErrorBox.exec();
        }
    }

    /* welcomeMessage.append(firstName);
    welcomeMessage.append(" ");
    welcomeMessage.append(lastName);
    welcomeMessage.append(",  ");
    welcomeMessage.append(email);
    welcomeMessage.append(" to this amazing app!");
    welcomeMessage.append("\nYour password: ");
    welcomeMessage.append(password);
    welcomeMessage.append("\nYour confirmed password: ");
    welcomeMessage.append(confirmPassword);
    welcomeMessage.append("\nPlease now login\n");
    QMessageBox::information(this, "Login", welcomeMessage); */
}
