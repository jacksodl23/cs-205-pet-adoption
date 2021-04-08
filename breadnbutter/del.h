#ifndef DELETE_H
#define DELETE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class delete; }
QT_END_NAMESPACE

class delete : public QMainWindow
{
    Q_OBJECT

public:
    delete(QWidget *parent = nullptr);
    ~delete();

private:
    Ui::delete *ui;
};
#endif // DELETE_H
