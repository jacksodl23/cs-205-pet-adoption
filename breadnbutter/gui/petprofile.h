#ifndef PETPROFILE_H
#define PETPROFILE_H

#include <QWidget>

namespace Ui {
class PetProfile;
}

class PetProfile : public QWidget
{
    Q_OBJECT

public:
    explicit PetProfile(QWidget *parent = nullptr);
    ~PetProfile();

private:
    Ui::PetProfile *ui;
};

#endif // PETPROFILE_H
