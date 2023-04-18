#include "mainwindow.h"
#include "ui_mainwindow.h"

/*
 * this method, setWelcomePhoto() sets up design on the main Login/CreateAccount
 * page by adding a wonderful welcome photo of a cat and by adding our BreadnButter
 * logo
 */
void MainWindow::setWelcomePhoto() {
    QString filePath(":/cats/Cats/CoverPhoto4.jpg");

    // welcome cat photo
    welcomePic.load(filePath);
    int width = ui->labelPic->width();
    int height = ui->labelPic->height();
    ui->labelPic->setPixmap(welcomePic.scaled(width, height, Qt::KeepAspectRatio));

    // BreadnButter logo
    QPixmap icon;
    QString icon0(":/icons/icons/logo.png");
    icon.load(icon0);
    width = ui->icon0_display->width();
    height = ui->icon0_display->height();
    ui->icon0_display->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));
}

/*
 * MainWindow constructor with setup code
 * and design and database code
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // standard setup code of the GUI
    ui->setupUi(this);
    setWindowTitle("Breadnbutter");
    // setting up design on the MainWindow
    setWelcomePhoto();
    // opening the database for our app
    openDB();
}

// MainWindow destructor that deletes the object of the ui pointer
MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * method for opening the pet search page for adopters/PetOwners
 * when they login
 */
void MainWindow::showPetDisplay()
{
    // hiding/closing MainWindow Login/CreateAccount page
    hide();
    // creating the PetDisplay/pet search page
    petDisplay = new PetDisplay(this);
    // deleting PetDisplay page when it's closed
    petDisplay->setAttribute(Qt::WA_DeleteOnClose);
    petDisplay->setWindowTitle("Search");
    // showing PetDisplay page
    petDisplay->show();
}

void MainWindow::showShelterDisplay()
{
    // hiding/closing MainWindow Login/CreateAccount page
    hide();
    // creating the shelterProfile page
    shelterDisplay = new shelterProfile(this);
    // deleting shelterProfile page when it's closed
    shelterDisplay->setAttribute(Qt::WA_DeleteOnClose);
    shelterDisplay->setWindowTitle("Breadnbutter");
    // showing the shelterProfile page
    shelterDisplay->show();
}

/*
 * this slot method opens up the Login window
 * when the User clicks the Login button on
 * the MainWindow page
 * this slot method lets the User login and then
 * opens the appropriate page based off of their role:
 * Adopter/PetOwner or Provider/ShelterOwner
 */
void MainWindow::on_loginButton_clicked()
{
    // creating an instance of the Login UI
    Login loginUI;
    // setModal(true) prevents widgets in all other windows
    // from being able to get any input
    loginUI.setModal(true);
    // executes the Login UI page
    loginUI.exec();

    // checking to see if the User successfully logged in
    if (loginUI.loginSuccessful) {
        // if the user logged in as a ShelterOwner then...
        if (!currentUser.getIs_adopter())
            // show the shelterProfile page
            showShelterDisplay();
        else // if logged in as adopter/PetOwner then...
            // open up the PetDisplay/pet search page
            showPetDisplay();
    }
}

/*
 * this slot method opens up the CreateAccount window
 * when the User clicks the CreateAccount button on
 * the MainWindow page
 * this method also adds new valid User to both the
 * system's database and to the User configuration file
 * that allows for auto login
 * links Shelters to ShelterOwners if needed
 */
void MainWindow::on_createButton_clicked()
{
    // on the stack - do we need to put it on the heap?
    CreateAccount createUI;
    createUI.setModal(true);
    createUI.exec();

    if (createUI.signUpSuccessful) {
       if (!currentUser.getIs_adopter())
           showShelterDisplay();
       else
           showPetDisplay();
    }
}

/*
 * openDB() attempts to open the application's database of
 * information about all Pets, PetOwners, Shelters, ShelterOwners,
 * an more
 */
void MainWindow::openDB()
{
    // creating QT database object, QSqlDatabase named db
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    // tells the QSqlDatabase object where the database is held
    // in a file named db.sqlite
    db.setDatabaseName(QApplication::applicationDirPath() + "/db.sqlite");

    // attempting to open the database
    if (db.open()) {
        qDebug() << "Database opened successfully.";
    } else { // unable to open database
        QMessageBox::critical(this, "Database Error", "An error occurred while trying to open the database: " + db.lastError().text());
    }
}

/*
 * this slot method will quit the BreadnButter application
 * if the Quit menu button is triggered
 */
void MainWindow::on_actionQuit_triggered()
{
    QApplication::quit();
}

/*
 * this slot method opens a QMessageBox or pop-up window to
 * explain more about our app when the About BreadnButter button
 * is selected
 */
void MainWindow::on_actionAbout_Bread_and_Butter_triggered()
{
   QMessageBox::about(this, "About BreadnButter", "Welcome to BreadnButter!\n"
                   "This application allows quick, efficient and effective services for those looking for pets!\n"
                   "If you are looking for people to adopt your pets, please don't hesistate to make a shelter account!");
}
