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

private:
    Ui::shelterhelp *ui;
};

#endif // SHELTERHELP_H
