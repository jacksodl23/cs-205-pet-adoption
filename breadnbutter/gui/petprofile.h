#ifndef PETPROFILE_H
#define PETPROFILE_H

#include <QWidget>
#include <QDialog>
#include <QMessageBox>
#include <QPushButton>

#include "petdisplay.h"
#include "ui_petdisplay.h"

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
    QPixmap petPic;
};

#endif // PETPROFILE_H
