#include "mainwindow.h"
#include "../backend/globals.h"
#include "../backend/petowner.h"
#include "../backend/shelterowner.h"
#include <QApplication>
#include <QtSql>
#include <fstream>
#include <cstring>

/*
 * the getCurrentUser() method
 * allows for auto login for verified users
 * who have selected the Stay Logged In option
 * on the Login page
 * This method checks to see what the ID of the
 * currentUser is on a given on a machine with the User
 * configuration file
 * If the method returns -1 then there is no
 * currentUser logged into the system, and the
 * main window with Login and CreateAccount options
 * will open
 * If a valid User is logged in then the default pages
 * will open for Adopter/PetOwner and Provider/ShelterOwner
 * respectively
 */
int getCurrentUser() {
    // file line variable
    std::string line;
    // creating file stream, config
    std::ifstream config(QApplication::applicationDirPath().toStdString() + "/currentuser.config");

    // attempting to open the config file
    if (config.is_open()) {
        // looping through all lines of the file
        while (getline(config, line)) {
            // taking line from file and storing in QString
            QString lineString = QString::fromStdString(line);
            // getting User ID from decrypting
            int theID = lineString.toInt();

            // creating a select query to get information about the User
            // with our decrypted ID
            QSqlQuery query;
            query.prepare("select is_adopter from User where user_id = ?");
            query.addBindValue(theID);

            // attempting to execute the select query above
            if (query.exec()) {
                // getting the first column value from the User with our
                // decrypted ID
                if (query.next()) {
                    int is_adopter = query.value(0).toInt();

                    // if the User is an adopter/PetOwner...
                    if (is_adopter == 1)
                        // set currentUser global variable to new PetOwner
                        // object
                        currentUser = PetOwner(theID);
                    // if the User is a provider/ShelterOwner...
                    else if (is_adopter == 0)
                        // set currentUser global variable to the new
                        // ShelterOwner object
                        currentUser = ShelterOwner(theID);
                } else { // first column value doesn't exist -> no User with our ID
                    qDebug() << "No valid user could be found.";
                    return -1;
                }
            } else { // trouble executing our select query to find User with our ID
                qDebug() << "Error getting user:" << query.lastError().text();
                return -1;
            }
            // User ID found
            return theID;
        }
    }
    // unable to open the config file
    return -1;
}

// main method for starting our application
int main(int argc, char *argv[])
{
    // setup code
    QApplication a(argc, argv);
    // our default page with no auto login
    MainWindow w;

    // no User is already logged in
    if (getCurrentUser() == -1)
        // default window
        w.show();
    else {
        // Provider/ShelterOwner already logged in
        if (!currentUser.getIs_adopter())
            // show Shelter profile page
            w.showShelterDisplay();
        // Adopter/PetOwner already logged in
        else
            // show pet search page
            w.showPetDisplay();
    }
    return a.exec();
}
