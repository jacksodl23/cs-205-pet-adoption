#ifndef SHELTERHELP_H
#define SHELTERHELP_H

#include <QMainWindow>

namespace Ui {
class shelterhelp;
}

class shelterhelp : public QMainWindow
{
    Q_OBJECT

public:
    explicit shelterhelp(QWidget *parent = 0);
    ~shelterhelp();

private slots:
    // handles when the profile menu item is clicked.
    void on_actionProfile_triggered();

    // handles when the pet upload menu item is clicked.
    void on_actionUpload_triggered();

    // handles when the log out menu item is clicked.
    void on_actionLog_out_triggered();

    // handles when the quit menu item is clicked.
    void on_actionQuit_triggered();

    // presents a dialog explaining the program.
    void on_actionAbout_BreadnButter_triggered();

private:
    Ui::shelterhelp *ui;
};

#endif // SHELTERHELP_H
