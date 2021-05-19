#include "shelterhelp.h"
#include "ui_shelterhelp.h"
#include "shelterprofile.h"
#include "shelterupload.h"
#include "createaccount.h"
#include "mainwindow.h"

shelterhelp::shelterhelp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::shelterhelp)
{
    ui->setupUi(this);
}

shelterhelp::~shelterhelp()
{
    delete ui;
}

// hides the current window and presents the shelter profile page.
void shelterhelp::on_actionProfile_triggered()
{
    hide();
    shelterProfile *profileUI = new shelterProfile(this);
    profileUI->setAttribute(Qt::WA_DeleteOnClose);
    profileUI->show();
}

// hides the current window and presents the pet upload page.
void shelterhelp::on_actionUpload_triggered()
{
    hide();
    shelterUpload *uploadUI = new shelterUpload(this);
    uploadUI->setAttribute(Qt::WA_DeleteOnClose);
    uploadUI->show();
}

// hides the current window and logs the user out.
void shelterhelp::on_actionLog_out_triggered()
{
    hide();
    MainWindow *login = new MainWindow(this);
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
}

// quits the program when the quit menu item is clicked.
void shelterhelp::on_actionQuit_triggered()
{
   QApplication::quit();
}

// shows a dialog explaining the program.
void shelterhelp::on_actionAbout_BreadnButter_triggered()
{
    QMessageBox::about(this, "About BreadnButter", "Welcome to BreadnButter!\n"
           "This application allows quick, efficient and effective services for those looking for pets!\n"
           "If you are looking for people to adopt your pets, please don't hesistate to make a shelter account!");
}
