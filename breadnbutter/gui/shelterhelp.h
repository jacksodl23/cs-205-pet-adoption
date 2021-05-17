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
    void on_actionProfile_triggered();

    void on_actionUpload_triggered();

    void on_actionLog_out_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_BreadnButter_triggered();

private:
    Ui::shelterhelp *ui;
};

#endif // SHELTERHELP_H
