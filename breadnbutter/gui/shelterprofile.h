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
    void showEvent(QShowEvent *event);

private slots:
    void on_actionUpload_triggered();

    void on_actionLog_out_triggered();

    void on_actionHelp_triggered();

    void on_actionAdopters_triggered();

    void on_actionQuit_triggered();

    void on_deletePetButton_clicked();

    void on_actionAbout_BreadnButter_triggered();

private:
    Ui::shelterProfile *ui;
    Shelter *currentShelter;

    void fetchShelter();
    void populatePetsTable();
    void logOutShelterOwner();
};

#endif // SHELTERPROFILE_H
