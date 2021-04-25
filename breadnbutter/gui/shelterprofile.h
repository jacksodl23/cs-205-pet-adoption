#ifndef SHELTERPROFILE_H
#define SHELTERPROFILE_H

#include <QMainWindow>

namespace Ui {
class shelterProfile;
}

class shelterProfile : public QMainWindow
{
    Q_OBJECT

public:
    explicit shelterProfile(QWidget *parent = 0);
    ~shelterProfile();

private:
    Ui::shelterProfile *ui;
};

#endif // SHELTERPROFILE_H
