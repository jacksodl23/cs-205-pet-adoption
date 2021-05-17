#include "createaccount.h"
#include "ui_createaccount.h"

// CreateAccount constructor with reference to QWidget parent
CreateAccount::CreateAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateAccount)
{
    // setup code
    ui->setupUi(this);
    // changing the text in the standard "Ok" button to "Sign up!"
    ui->createOkay->button(QDialogButtonBox::Ok)->setText("Sign up!");
}

// CreateAccount destructor
CreateAccount::~CreateAccount()
{
    delete ui;
}

/*
 * writes a user's information to a configuration file
 * when they sign up for an account
 */
void CreateAccount::writeUserToFile(User newUser)
{
    std::ofstream config("currentuser.config");

    // simple encryption for the user's information
    SimpleCrypt crypto(CRYPTO_KEY);
    QString id = QString::number(newUser.getID());
    QString encoded = crypto.encryptToString(id);

    // writing encrypted user ID to the config file
    config << encoded.toStdString();
    // close file
    config.close();
}

/*
 * Changes labels on CreateAccount page
 * If an adopter is signing up then the labels ask for
 * the user's first name and last name
 * If a shelter owner or other pet provider wants to sign up
 * then the labels change and prompt the user for the
 * full name of the owner and the name of the shelter
 */
void CreateAccount::on_roleBox_activated(const QString &arg1)
{
    if (arg1 == "Adopter") {	// Adopter labels
        ui->firstNameLabel->setText("First Name");
        ui->lastNameLabel->setText("Last Name");
    } else if (arg1 == "Provider") {    // Provider/Shelter labels
        ui->firstNameLabel->setText("Full Name");
        ui->lastNameLabel->setText("Shelter Name");
    }
}

/*
 * Method to handle creating a PetOwner object based off of
 * the information provided in the CreateAccount page
 * If the new PetOwner information does not conflict with
 * another User that is already in the system then the
 * currentUser global variable is set to the new User and
 * the new PetOwner is added to the User configuration file
 */
void CreateAccount::signUpAdopter(QString firstName, QString lastName, QString location, QString email, QString phone, QString password)
{
    // creating new PetOwner named newAdopter and adding the User to the
    // database
    PetOwner newAdopter(password, firstName, lastName, email, phone, location);
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

void CreateAccount::linkShelterOwnerToShelter(Shelter s, QString location, QString firstName, QString email, QString phone, QString lastName, QString password)
{
    ShelterOwner newOwner(firstName, lastName, location, email, phone, password);
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
    QString phone = ui->phoneField->text();
    QString password = ui->passwordField->text();
    QString confirmPassword = ui->passwordField_2->text();
    QString location = ui->locationField->text();

    if (button == ui->createOkay->button(QDialogButtonBox::Ok)) {
        if (password != confirmPassword) {
            QMessageBox::critical(this, "Error!", "Passwords do not match - try again!");
            return;
        }

        if (ui->roleBox->currentIndex() == 0) {
            signUpAdopter(firstName, lastName, location, email, phone, password);
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

                linkShelterOwnerToShelter(s, location, oFirstName, email, phone, oLastName, password);
            } else {
                QMessageBox::critical(this, "Unable to create shelter", "Something went wrong while trying to register a new shelter. Please try again.");
            }
        }
        this->close();
    } else {
        qDebug() << "Should dismiss.";
        this->close();
    }
}
