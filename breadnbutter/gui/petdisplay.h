/*
 * The PetDisplay class handles all members and methods
 * for searching, displaying, liking, disliking, and
 * learning about Pets from our database.
 */

#ifndef PETDISPLAY_H
#define PETDISPLAY_H

#include <QMainWindow>
#include <QDebug>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <QMessageBox>
#include <QColor>
#include <QColorDialog>
#include <QtSql>
#include "../backend/globals.h"
#include "../backend/utils.h"
#include "../backend/petowner.h"
#include "../backend/pet.h"
#include "../backend/location.h"
#include "petprofile.h"
#include "petliked.h"
#include "petownerhelp.h"

namespace Ui {
class PetDisplay;
}

class PetDisplay : public QMainWindow
{
    Q_OBJECT

public:
    // default PetDisplay constructor
    explicit PetDisplay(QWidget *parent = nullptr);
    // PetDisplay destructor
    ~PetDisplay();

    QPixmap getPetPic() const;

private slots:
    // slot method for handling selecting the type of
    // Pet - Dog or Cat
    // determines what breeds are available
    void on_typeBox_currentTextChanged(const QString &arg1);

    // for selecting the breed of the Pet
    // determines what color and hair lengths are
    // available
    void on_breedBox_activated(int index);

    // triggered by the search button in the PetDisplay
    // fetches Pets based off of search attributes
    void on_pushButton_clicked();

    // triggered when the profile menu option is
    // clicked and opens the PetProfile page for
    // the currently displayed Pet on the PetDisplay
    void on_profileButton_clicked();

    // triggered when the like button is selected
    // handles the members and methods involved with
    // liking a Pet, including adding the Pet to the
    // liked Pets of the currentUser, moving to the
    // next Pet, and more
    void on_button_like_clicked();

    // triggered when the dislike button is selected
    // moves to the next Pet in the searched Pets vector
    void on_button_dislike_clicked();

    // triggered when the Log out menu option is selected
    // logs the currentUser out of the application and
    // returns to the MainWindow page with Login and
    // CreateAccount options
    void on_actionLog_out_triggered();

    // triggered when the Liked menu option is selected
    // closes the PetDisplay page and opens the
    // adopter/PetOwner's PetLiked pages which has
    // all of the currentUser's liked Pets and their
    // information
    void on_actionLiked_triggered();

    // triggered when the Help menu option is selected
    // closes the PetDisplay page and opens an instance
    // of the PetOwnerHelp page with gives the adopter
    // more information about how to use BreadnButter
    void on_actionHelp_triggered();

    // triggered when the value on the minumum age
    // slider is changed on the PetDisplay GUI
    // updates the label next to the slider with
    // the current value
    void on_minAgeSlider_valueChanged(int value);

    // triggered when the value on the maximum age
    // slider is changed on the PetDisplay GUI
    // updates the label next to the slider with
    // the current value
    void on_maxAgeSlider_valueChanged(int value);

    // triggered when the value on the minumum weight
    // slider is changed on the PetDisplay GUI
    // updates the label next to the slider with
    // the current value
    void on_minWeightSlider_valueChanged(int value);

    // triggered when the value on the maximum weight
    // slider is changed on the PetDisplay GUI
    // updates the label next to the slider with
    // the current value
    void on_maxWeightSlider_valueChanged(int value);

    // triggered when the Quit menu option is selected
    // and quits the BreadnButter application
    void on_actionQuit_triggered();

    // triggered when the About BreadnButter menu
    // option is selected and opens a dialog window
    // with some basic information about BreadnButter
    void on_actionAbout_BreadnButter_triggered();



private:
    // PetDisplay UI pointer named ui
    Ui::PetDisplay *ui;

    // pointer to a PetProfile instance
    PetProfile *profileUI;

    // QSqlQuery variable used for all queries
    QSqlQuery query;

    // image lists for Dog and Cat pictures
    QStringList dogImageList;
    QStringList catImageList;

    // QPixmap for displaying Pet photos
    QPixmap petPic;

    QString selectedPetType;

    // Pet vector of pets from each search query
    std::vector<std::pair<Pet, float>> pets;

    int currentPos;

    // method for fetching Pets from the database with
    // a specified set of attributes
    void fetchPets();

    // method for displaying a given Pet, p
    void displayPet(Pet p);

    //
    void getCurrentUser();
    void updateBar();
};

#endif // PETDISPLAY_H
