#ifndef PETLIKED_H
#define PETLIKED_H

#include <QMainWindow>
#include <QtSql>
#include <QString>
#include <vector>
#include "../backend/globals.h"
#include "../backend/pet.h"
#include "../backend/location.h"
#include "../backend/utils.h"
#include "petprofile.h"
#include "petownerhelp.h"
#include "petdisplay.h"

namespace Ui {
class petliked;
}

class PetLiked : public QMainWindow
{
    Q_OBJECT

public:
    explicit PetLiked(QWidget *parent = 0);
    ~PetLiked();

private slots:
    void on_button_next_clicked();

    void on_button_prev_clicked();

    void on_actionLog_out_triggered();

    void on_actionHelp_triggered();

    void on_actionSearch_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_BreadnButter_triggered();

private:
    Ui::petliked *ui;
    PetProfile *profileUI;

    int currentPos;

    QStringList catImageList;
    QStringList dogImageList;
    QPixmap petPic;

    std::vector<Pet> pets;
    void fetchLikedPets();

    void displayPet(Pet p);
};

#endif // PETLIKED_H
