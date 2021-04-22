#ifndef PETPROFILE_H
#define PETPROFILE_H

#include <QDialog>

namespace Ui {
class PetProfile;
}

class PetProfile : public QDialog
{
    Q_OBJECT

public:
    explicit PetProfile(QWidget *parent = 0);
    ~PetProfile();

private:
    Ui::PetProfile *ui;
};

#endif // PETPROFILE_H
