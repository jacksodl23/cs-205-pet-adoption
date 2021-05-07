#ifndef PETPROFILE_H
#define PETPROFILE_H

#include <QDialog>
#include "../backend/pet.h"
#include "../backend/shelter.h"
#include "../backend/shelterowner.h"

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
    void on_backToSearchButton_clicked();


private:
    Ui::PetProfile *ui;

    QPixmap petPic;
    Pet pDisplay;

    void fetchPet();
};

#endif // PETPROFILE_H
