#include "login.h"
#include "ui_login.h"

// Constructor for Login display with a QWidget parent
Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    // standard setup code
    ui->setupUi(this);

    // changing the text of the "Ok" button to be "Login"
    ui->loginOkay->button(QDialogButtonBox::Ok)->setText("Login");
    // boolean for keeping track of whether or not the User
    // has successfully logged into the application
    loginSuccessful = false;
}

// destructor for the Login class
Login::~Login()
{
    // removing ui from and freeing heapspace
    delete ui;
}

/*
 * slot method for handling Login information
 * takes the email and password input by the
 * User and attempts to login to the app
 * with the provided information.
 * If the login is successful, then the app
 * opens to the appropriate page for the User:
 * Adopters/PetOwners see the pet display/search
 * page at open
 * Providers/ShelterOwners see the Shelter
 * profile page at open
 * The User can choose to stay logged in
 * Any problems will throw an error message
 */
void Login::on_loginOkay_accepted()
{
    // pulling User's email and password from Login GUI
    QString email = ui->emailField->text();
    QString password = ui->passwordField->text();

    // creating User object with User constructor
    User user(email, password);
    // attempting and checking if Login is successful
    loginSuccessful = user.attemptLogin();

    // if Login successful then...
    if (loginSuccessful) {
        // creating query to pull User information
        // from the database to assign currentUser
        // global variable to the logged in User
        QSqlQuery query;
        query.prepare("select is_adopter from User where user_id = ?");
        query.addBindValue(user.getID());

        // attempting and checking to execute select query
        if (query.exec()) {
            // attempting to using query to get info
            if (query.next()) {
                // checking if the logged in User is an adopter
                int is_adopter = query.value(0).toInt();
                // if User is an adopter, set currentUser to
                // PetOwner, otherwise the logged in User is
                // a ShelterOwner
                if (is_adopter == 1) {
                    // creating PetOwner object with User ID
                    currentUser = PetOwner(user.getID());
                } else {
                    // creating ShelterOwner object with User ID
                    currentUser = ShelterOwner(user.getID());
                }

                // checking to see if User selected stay logged in
                // check box... if so, write their info to the User
                // configuration file to allow auto login
                if (ui->checkBox->checkState() == Qt::Checked)
                    writeUserToFile(currentUser);
            }
        } else { // select query was unable to be executed
            qDebug() << "Error determining if user is adopter:" << query.lastError().text();
        }
    } else { // throwing an error as a message box if the login was unsuccessful
        QMessageBox::critical(this, "Error Logging In", "Something went wrong when logging in. Please try again.");
    }
}

/*
 * Writes the User's information to the User config
 * file to allow for login without providing email
 * or password for a previously verified User
 */
void Login::writeUserToFile(User user)
{
    // opening file stream to the User config file
    std::ofstream config("currentuser.config");

    // Set up the ID to be written to the User config file.
    QString id = QString::number(user.getID());

    // writing User ID to config file
    config << id.toStdString();
    // closing file stream
    config.close();
}
