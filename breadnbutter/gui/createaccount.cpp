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
 * A PetOwner is a potential Adopter
 *
 * Method to handle creating a PetOwner object based off of
 * the information provided in the CreateAccount page
 * If the new PetOwner information does not conflict with
 * another User that is already in the system then the
 * currentUser global variable is set to the new User and
 * the new PetOwner is added to the User configuration file
 * Otherwise, the PetOwner is not added to the database or to
 * the User configuration file of valid Users and an
 * appropriate message pops up
 */
void CreateAccount::signUpAdopter(QString firstName, QString lastName, QString location, QString email, QString phone, QString password)
{
    // creating new PetOwner named newAdopter and adding the User to the
    // database
    PetOwner newAdopter(password, firstName, lastName, email, phone, location);
    signUpSuccessful = newAdopter.insertInDB();

    // checking if the PetOwner was successfully added to the database
    if (signUpSuccessful) {
        // assigning global var
        currentUser = newAdopter;

        // adding PetOwner to configuration file that stores
        // records of all Users added to the system
        writeUserToFile(newAdopter);
    } else {	// PetOwner was not added to the database successfully
        // checking to see if a given set of PetOwner information is already
        // inside of the database
        if (newAdopter.existsInDB()) {
            QMessageBox::critical(this, "Email taken!", "This email is already taken. Please try again.");
        }
    }
}


/*
 * Method to handle creating a ShelterOwner object based off of
 * the information provided in the CreateAccount page
 * If the new ShelterOwner information does not conflict with
 * another User that is already in the system then the
 * ShelterOwner is linked with the Shelter object, s, using a
 * foriegn key, the currentUser global variable is set to the
 * new ShelterOwner, and the new ShelterOwner is added to the
 * User configuration file containing valid Users
 * Otherwise, the new ShelterOwner is not added to the database
 * or the configuration file and a message pops up
 */
void CreateAccount::linkShelterOwnerToShelter(Shelter s, QString location, QString firstName, QString email, QString phone, QString lastName, QString password)
{
    // creating ShelterOwner object with given information
    ShelterOwner newOwner(firstName, lastName, location, email, phone, password);
    // checking if ShelterOwner info is already in database and that
    // new information was successfully added to the database
    if (newOwner.insertInDB()) {
        // linking the new ShelterOwner to the Shelter object, s with a
        // foreign key
        QSqlQuery query;
        query.prepare("update shelter set owner_id = ? where shelter_id = ?");
        query.addBindValue(newOwner.getID());
        query.addBindValue(s.getShelterID());

        // checking to make sure linking was successful
        signUpSuccessful = query.exec();

        if (signUpSuccessful) {
            // if so, currentUser is assigned
            currentUser = newOwner;

            // and the new ShelterOwner is added to the User
            // configuration file containing all valid Users'
            // information
            writeUserToFile(newOwner);
        } else { // otherwise, the new ShelterOwner is not added to anything
            // checking if this ShelterOwner is already in the database
            if (newOwner.existsInDB()) {
                QMessageBox::critical(this, "Email taken!", "This email is already taken. Please try again.");
            }
        }
    }
}

/*
 * Method contains actions when the Ok/Sign up button
 * is clicked on the CreateAccount page
 */
void CreateAccount::on_createOkay_clicked(QAbstractButton *button)
{
    // pulling information from all text fields
    QString firstName = ui->firstNameField->text();
    QString lastName = ui->lastNameField->text();
    QString email = ui->emailField->text();
    QString phone = ui->phoneField->text();
    QString password = ui->passwordField->text();
    QString confirmPassword = ui->passwordField_2->text();
    QString location = ui->locationField->text();

    // TODO
    if (button == ui->createOkay->button(QDialogButtonBox::Ok)) {
        // checking to make sure that the password and confirm
        // password fields match
        if (password != confirmPassword) {
            QMessageBox::critical(this, "Error!", "Passwords do not match - try again!");
            return;
        }

        // checking to see if an Adopter is signing up
        if (ui->roleBox->currentIndex() == 0) {
            // attempt to add adopter/PetOwner information
            // to the database, User config file, and set
            // the currentUser to the new adopter
            signUpAdopter(firstName, lastName, location, email, phone, password);
        } else { // otherwise, a shelter/provider of pets is signing in
            // Shelter object created with provided info
            // lastName is used as the Shelter name whenever
            // shelters are added to the system
            Shelter s(lastName, location, email);
            // checking if the Shelter can be added to the
            // database, and if so, adding it
            if (s.insertIntoDB()) {

                QString oFirstName;
                QString oLastName;

                // splitting the firstName field into
                // the actual first and last name of the ShelterOwner
                QStringList pieces = firstName.split(" ");
                for (int i = 0; i < pieces.size(); i++) {
                    if (i == 0)
                        oFirstName = pieces.at(i);
                    else if (i == 1)
                        oLastName = pieces.at(i);
                }

                // linking Shelter s to the new ShelterOwner made in the method
                // using the information provided by the CreateAccount page
                linkShelterOwnerToShelter(s, location, oFirstName, email, phone, oLastName, password);
            } else { // error message if the Shelter could not be added to the database
                QMessageBox::critical(this, "Unable to create shelter", "Something went wrong while trying to register a new shelter. Please try again.");
            }
        }
        // closing the CreateAccount page
        this->close();
    } else { // Ok/Sign up button not clicked
        qDebug() << "Should dismiss.";
        this->close();
    }
}
