#ifndef SHELTERPROFILE_H
#define SHELTERPROFILE_H

#include <QMainWindow>
#include <QtSql>
#include <QMessageBox>
#include "../backend/globals.h"
#include "../backend/shelter.h"
#include "shelterprofilesqlmodel.h"
#include "shelterupload.h"
#include "shelteradopters.h"

namespace Ui {
class shelterProfile;
}

class shelterProfile : public QMainWindow
{
    Q_OBJECT

public:
    explicit shelterProfile(QWidget *parent = 0);
    ~shelterProfile();

protected:
    // called whenever the window appears after previously being dismissed.
    void showEvent(QShowEvent *event);

private slots:
    // handles when the upload menu item is clicked.
    void on_actionUpload_triggered();

    // handles when the log out menu item is clicked.
    void on_actionLog_out_triggered();

    // handles when the help menu item is clicked.
    void on_actionHelp_triggered();

    // handles when the adopters menu item is clicked.
    void on_actionAdopters_triggered();

    // handles when the quit menu item is clicked.
    void on_actionQuit_triggered();

    // handles when the delete pet button is clicked.
    void on_deletePetButton_clicked();

    // handles when the about menu item is clicked.
    void on_actionAbout_BreadnButter_triggered();

private:
    Ui::shelterProfile *ui;

    // used to keep track of the shelter the current user owns.
    Shelter *currentShelter;

    // gets information for the current shelter.
    void fetchShelter();

    // populates the table of pets in the current shelter.
    void populatePetsTable();

    // logs out the current user.
    void logOutShelterOwner();
};

#endif // SHELTERPROFILE_H
