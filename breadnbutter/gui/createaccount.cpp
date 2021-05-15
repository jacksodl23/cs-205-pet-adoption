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


void CreateAccount::on_roleBox_activated(const QString &arg1)
{
    if (arg1 == "Adopter") {
        ui->firstNameLabel->setText("First Name");
        ui->lastNameLabel->setText("Last Name");
    } else if (arg1 == "Provider") {
        ui->firstNameLabel->setText("Full Name");
        ui->lastNameLabel->setText("Shelter Name");
    }
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

void CreateAccount::signUpAdopter(QString firstName, QString lastName, QString location, QString email, QString password)
{
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
}

void CreateAccount::linkShelterOwnerToShelter(Shelter s, QString location, QString firstName, QString email, QString lastName, QString password)
{
    ShelterOwner newOwner(firstName, lastName, location, email, password);
    if (newOwner.insertInDB()) {
        QSqlQuery query;
        query.prepare("update shelter set owner_id = ? where shelter_id = ?");
        query.addBindValue(newOwner.getID());
        query.addBindValue(s.getShelterID());

        signUpSuccessful = query.exec();

        if (signUpSuccessful) {
            currentUser = newOwner;

            writeUserToFile(newOwner);
        } else {
            if (newOwner.existsInDB()) {
                QMessageBox::critical(this, "Email taken!", "This email is already taken. Please try again.");
            }
        }
    }
}

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
            signUpAdopter(firstName, lastName, location, email, password);
        } else {
            // Change to take in full name and shelter name values.
            Shelter s(lastName, location, email);
            if (s.insertIntoDB()) {

                QString oFirstName;
                QString oLastName;

                QStringList pieces = firstName.split(" ");
                for (int i = 0; i < pieces.size(); i++) {
                    if (i == 0)
                        oFirstName = pieces.at(i);
                    else if (i == 1)
                        oLastName = pieces.at(i);
                }

                linkShelterOwnerToShelter(s, location, oFirstName, email, oLastName, password);
            } else {
                QMessageBox::critical(this, "Unable to create shelter", "Something went wrong while trying to register a new shelter. Please try again.");
            }
        }
        this->close();
    } else {
        qDebug() << "Should dismiss.";
    }
}
