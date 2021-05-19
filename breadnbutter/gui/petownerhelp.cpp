#include "petownerhelp.h"
#include "ui_petownerhelp.h"
#include "petliked.h"
#include "petdisplay.h"
#include "createaccount.h"
#include "mainwindow.h"

/* Default constructor of the petownerhelp class
 */
petownerhelp::petownerhelp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::petownerhelp)
{
    ui->setupUi(this);
}


/* Default destructor of the petownerhelp class
 */
petownerhelp::~petownerhelp()
{
    delete ui;
}


/* Method that allows a user to jump to Liked page when menu item is clicked
 */
void petownerhelp::on_actionLiked_triggered()
{
    hide();
    // instance of the PetLiked class
    PetLiked *likedUI = new PetLiked(this);
    likedUI->setAttribute(Qt::WA_DeleteOnClose);
    likedUI->show();
}

/* Method that allows a user to jump to Search page when menu item is clicked
 */
void petownerhelp::on_actionSearch_triggered()
{
    hide();
    // instance of the PetDisplay class
    PetDisplay *petUI = new PetDisplay(this);
    petUI->setAttribute(Qt::WA_DeleteOnClose);
    petUI->show();
}

/* Method that allows a user to Log out of the system and return to the Welcome page
 */
void petownerhelp::on_actionLog_out_triggered()
{
    hide();
    // instance of the MainWindow class
    MainWindow *login = new MainWindow(this);
    login->setAttribute(Qt::WA_DeleteOnClose);
    login->show();
}

/* Method that allows a user to quit the system
 */
void petownerhelp::on_actionQuit_triggered()
{
   QApplication::quit();
}

/* Method that allows a user to see a short bio of our system when menu item is clicked
 */
void petownerhelp::on_actionAbout_BreadnButter_triggered()
{
    // Message box that displays a short info about the system
    QMessageBox::about(this, "About BreadnButter", "Welcome to BreadnButter!\n"
           "This application allows quick, efficient and effective services for those looking for pets!\n"
           "If you are looking for people to adopt your pets, please don't hesistate to make a shelter account!");
}
