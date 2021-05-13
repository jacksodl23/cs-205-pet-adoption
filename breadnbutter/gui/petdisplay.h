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
#include "../backend/petowner.h"
#include "../backend/pet.h"
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
    explicit PetDisplay(QWidget *parent = nullptr);
    ~PetDisplay();

private slots:
    void on_typeBox_activated(const QString &arg1);

    void on_breedBox_activated(const QString &arg1);

    void on_pushButton_clicked();

    void on_profileButton_clicked();

    void on_button_like_clicked();

    void on_button_dislike_clicked();

    void on_hypoBox_activated(const QString &arg1);

    void on_actionLog_out_triggered();

    void on_actionLiked_triggered();

    void on_actionHelp_triggered();

    void on_dislikeBoxType_clicked(bool checked);

    void on_dislikeBoxBreed_clicked(bool checked);

    void on_dislikeBoxColor_clicked(bool checked);

    void on_dislikeBoxHairLen_clicked(bool checked);

    void updateBar();

    void on_minAgeSlider_valueChanged(int value);

    void on_maxAgeSlider_valueChanged(int value);

    void on_minWeightSlider_valueChanged(int value);

    void on_maxWeightSlider_valueChanged(int value);

    void on_minAgeSlider_sliderReleased();

    void on_maxAgeSlider_sliderReleased();

    void on_minWeightSlider_sliderReleased();

    void on_maxWeightSlider_sliderReleased();

    void on_actionQuit_triggered();

private:
    Ui::PetDisplay *ui;
    PetProfile *profileUI;

    QPixmap petPic;
    std::vector<Pet> pets;
    int currentPos;
    QString baseQuery;
    QString prefString;

    void fetchPets();
    void displayPet(Pet p);
    void getCurrentUser();
};

#endif // PETDISPLAY_H
