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

void CreateAccount::writeUserToFile(User newUser)
{
    std::ofstream config("currentuser.config");

    SimpleCrypt crypto(CRYPTO_KEY);
    QString id = QString::number(newUser.getID());
    QString encoded = crypto.encryptToString(id);

    config << encoded.toStdString();
    config.close();
}

/* void CreateAccount::on_createOkay_accepted()
{
    QString firstName = ui->firstNameField->text();
    QString lastName = ui->lastNameField->text();
    QString email = ui->emailField->text();
    QString password = ui->passwordField->text();
    QString confirmPassword = ui->passwordField_2->text();
    QString location = ui->locationField->text();
//    QString welcomeMessage = "Welcome ";

    if (password != confirmPassword) {
        QMessageBox::critical(this, "Error!", "Passwords do not match - try again!");
        //QMessageBox passwordErrorBox;
        //passwordErrorBox.setText("Error!\nPasswords do not match - try again!");
        //passwordErrorBox.exec();
        return;
    }

    // what about shelter owner?

    if (ui->roleBox->currentIndex() == 0) {
        PetOwner newAdopter(password, firstName, lastName, email, location);
        signUpSuccessful = newAdopter.insertInDB();

        if (signUpSuccessful) {
            currentUser = newAdopter;

            writeUserToFile(newAdopter);
        } else {
            if (newAdopter.existsInDB()) {
                QMessageBox::critical(this, "Email taken!", "This email is already taken. Please try again.");
            }
        }
    } else {
        ShelterOwner newOwner(firstName, lastName, location, email, password);
        signUpSuccessful = newOwner.insertInDB();

        if (signUpSuccessful) {
            currentUser = newOwner;

            writeUserToFile(newOwner);
        } else {
            if (newOwner.existsInDB()) {
                QMessageBox::critical(this, "Email taken!", "This email is already taken. Please try again.");
            }
        }
    }
} */

void CreateAccount::on_createOkay_clicked(QAbstractButton *button)
{
    QString firstName = ui->firstNameField->text();
    QString lastName = ui->lastNameField->text();
    QString email = ui->emailField->text();
    QString password = ui->passwordField->text();
    QString confirmPassword = ui->passwordField_2->text();
    QString location = ui->locationField->text();

    if (button == ui->createOkay->button(QDialogButtonBox::Ok)) {
        if (password != confirmPassword) {
            QMessageBox::critical(this, "Error!", "Passwords do not match - try again!");
            return;
        }

        if (ui->roleBox->currentIndex() == 0) {
            PetOwner newAdopter(password, firstName, lastName, email, location);
            signUpSuccessful = newAdopter.insertInDB();

            if (signUpSuccessful) {
                currentUser = newAdopter;

                writeUserToFile(newAdopter);
            } else {
                if (newAdopter.existsInDB()) {
                    QMessageBox::critical(this, "Email taken!", "This email is already taken. Please try again.");
                }
            }
        } else {
            ShelterOwner newOwner(firstName, lastName, location, email, password);
            signUpSuccessful = newOwner.insertInDB();

            if (signUpSuccessful) {
                currentUser = newOwner;


                // adding more shelter profile information
                // TODO CANNOT TEST until we fix the signup issue
                // "recursive call"
                MoreShelterInfo moreShelterInfoUI;
                moreShelterInfoUI.setModal(true);
                moreShelterInfoUI.exec();


                writeUserToFile(newOwner);
            } else {
                if (newOwner.existsInDB()) {
                    QMessageBox::critical(this, "Email taken!", "This email is already taken. Please try again.");
                }
            }
        }
    } else {
        qDebug() << "Should dismiss.";
    }
}
