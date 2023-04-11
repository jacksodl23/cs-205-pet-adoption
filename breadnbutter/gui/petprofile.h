#ifndef PETPROFILE_H
#define PETPROFILE_H

#include <QDialog>
#include "../backend/pet.h"
#include "../backend/shelter.h"
#include "../backend/shelterowner.h"
#include "../backend/utils.h"
#include "../backend/globals.h"

namespace Ui {
class PetProfile;
}

class PetProfile : public QDialog
{
    Q_OBJECT

public:
    explicit PetProfile(QWidget *parent = 0);
    ~PetProfile();

    void setPDisplay(const Pet &value);

private slots:
    void on_backToSearchButton_clicked(); // method to jump back to Search page


private:
    Ui::PetProfile *ui;

    Pet pDisplay; // instance of Pet class

    QStringList dogImageList; // list of dog images
    QStringList catImageList; // list of cat images

    void fetchPet(); // method to get the pet
};

#endif // PETPROFILE_H
