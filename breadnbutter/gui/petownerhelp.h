#ifndef PETOWNERHELP_H
#define PETOWNERHELP_H

#include <QMainWindow>

namespace Ui {
class petownerhelp;
}

class petownerhelp : public QMainWindow
{
    Q_OBJECT

public:
    explicit petownerhelp(QWidget *parent = 0);
    ~petownerhelp();

private slots:
    void on_actionLiked_triggered(); // method to jump to Liked page

    void on_actionSearch_triggered(); // method to jump to Search page

    void on_actionLog_out_triggered(); // method to log out of the system

    void on_actionQuit_triggered(); // method to quit the system

    void on_actionAbout_BreadnButter_triggered(); // method to show a short info about the system

private:
    Ui::petownerhelp *ui;
};

#endif // PETOWNERHELP_H
