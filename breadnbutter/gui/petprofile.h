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

private slots:
    void on_backToSearchButton_clicked();

private:
    Ui::PetProfile *ui;

    QPixmap petPic;
};

#endif // PETPROFILE_H
