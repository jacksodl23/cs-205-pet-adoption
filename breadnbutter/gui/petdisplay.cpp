#include "petdisplay.h"
#include "ui_petdisplay.h"
#include "petliked.h"
#include "petownerhelp.h"
#include "createaccount.h"
#include "mainwindow.h"

/*
 * PetDisplay contructor with photo, icons, and progress bar addtions
 * along with setup code
 */
PetDisplay::PetDisplay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PetDisplay)
{
    // setup code
    ui->setupUi(this);

    // making a lists of dog and cat images
    int width = ui->animalDisplay->width();
    int height = ui->animalDisplay->height();

    // making a lists of dog and cat images
    dogImageList = QDir(":/dogs/Dogs").entryList();
    catImageList = QDir(":/cats/Cats").entryList();
    qDebug() << "Cat image list has" << catImageList.size() << "images in it.";

    // adding icons to the page
    QPixmap icon;

    // file path to name icon in project resources
    QString icon0(":/icons/icons/Name.png");
    // loading icon from resources
    icon.load(icon0);
    // gettting the width of the photo display
    width = ui->icon0_display->width();
    // getting the height of the photo display
    height = ui->icon0_display->height();
    // setting the photo display to the loaded icon QPixmap
    ui->icon0_display->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString icon1(":/icons/icons/Type.png");
    icon.load(icon1);
    width = ui->icon1_display->width();
    height = ui->icon1_display->height();
    ui->icon1_display->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString icon2(":/icons/icons/Breed.png");
    icon.load(icon2);
    width = ui->icon2_display->width();
    height = ui->icon2_display->height();
    ui->icon2_display->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString icon3(":/icons/icons/Age.png");
    icon.load(icon3);
    width = ui->icon3_display->width();
    height = ui->icon3_display->height();
    ui->icon3_display->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString icon4(":/icons/icons/Location.png");
    icon.load(icon4);
    width = ui->icon4_display->width();
    height = ui->icon4_display->height();
    ui->icon4_display->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString icon5(":/icons/icons/Shelter.png");
    icon.load(icon5);
    width = ui->icon5_display->width();
    height = ui->icon5_display->height();
    ui->icon5_display->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    QString icon6(":/icons/icons/Distance.png");
    icon.load(icon6);
    width = ui->icon6_display->width();
    height = ui->icon6_display->height();
    ui->icon6_display->setPixmap(icon.scaled(width, height, Qt::KeepAspectRatio));

    currentPos = 0;

    getCurrentUser();

    // code for displaying progress bar
    ui->progressBar->setOrientation(Qt::Horizontal);
}

// PetDisplay destructor that deletes the PetDisplay UI
// and clearing heap space
PetDisplay::~PetDisplay()
{
    delete ui;
}

/*
 * changes available breeds based on pet type
 * handles different Pet Types from the Type drop down menu
 * pulls from the database to get different Pet breeds
 * determines breeds based off of Pet type
 */
void PetDisplay::on_typeBox_currentTextChanged(const QString &arg1)
{
    // Clear the drop down menus only if the desired type of pet was changed.
    if (!selectedPetType.isEmpty() && QString::compare(arg1, selectedPetType, Qt::CaseInsensitive) != 0) {
        // clearing all of the drop down menus
        ui->breedBox->clear();
        ui->colorBox->clear();
        ui->hairLenBox->clear();

        ui->breedBox->addItem("Any");
    }
    selectedPetType = arg1;

    // if the type chosen is Dog...
    if (arg1 == "Dog") {
        // getting Dog breeds from the database
        query.prepare("select distinct breed from pet where is_cat = 0 order by breed asc");

        if (query.exec()) {
            while (query.next()) {
                // adding breeds pulled from database to the drop down menu
                QString breed = query.value(0).toString();
                ui->breedBox->addItem(breed);
            }
        } else { // query execution failed
            qDebug() << "Error getting dog breeds:" << query.lastError().text();
        }
    }

    if (arg1 == "Cat") {
        // getting Cat breeds from database
        query.prepare("select distinct breed from pet where is_cat = 1 order by breed asc");

        if (query.exec()) {
            while (query.next()) {
                // adding breeds pulled from database to the drop down menu
                QString breed = query.value(0).toString();
                ui->breedBox->addItem(breed);
            }
        } else { // query execution failed
            qDebug() << "Error getting cat breeds:" << query.lastError().text();
        }
    }
}

/*
 * Handles different Pet breeds based off of the input in the
 * Pet breed drop down menu
 * Fills the color drop down menu based off of the Pet breed selected
 * Fills the hair length drop down menu based off of the Pet breed selected
 */
void PetDisplay::on_breedBox_activated(int index)
{
    QString breed = ui->breedBox->currentText();

    if (!breed.isEmpty()) {
        // select query for pulling Pet colors based off breed from database
        query.prepare("select distinct color from pet where breed = ? order by color asc");
        query.addBindValue(breed);

        // attempting to execute the select query
        if (query.exec()) {
            // clearing color and hair length drop down menus
            // needed for changes in breed
            ui->colorBox->clear();
            ui->hairLenBox->clear();

            // attempting to pull data from the query
            while (query.next()) {
                // getting all possible breed colors
                QString color = query.value(0).toString();
                // adding query color to the color drop down menu
                ui->colorBox->addItem(color);
            }
        } else { // unable to execute the select query
            qDebug() << "Error getting breed colors:" << query.lastError().text();
        }

        // select query for pulling Pet hair length based off breed from database
        query.prepare("select distinct hair_type from pet where breed = ? order by hair_type asc");
        query.addBindValue(breed);

        // attempting to execute query
        if (query.exec()) {
            qDebug() << "Executed query" << query.executedQuery();
            while (query.next()) {
                // adding appropriate breed hair lengths to drop down menu
                QString hairLen = query.value(0).toString();
                ui->hairLenBox->addItem(hairLen);
            }
        }
    }
}

// slot method for when search button is selected
void PetDisplay::on_pushButton_clicked()
{
    // TODO
    fetchPets();
}

/*
 * displayPet() takes a Pet, p, as an argument and
 * displays an appropriate picture in the PetDisplay
 * window based off of the Pet's type - Dog or Cat
 */
void PetDisplay::displayPet(Pet p)
{
    // seed for random function
    srand(time(0));

    // is this Pet, p, a Cat?
    if (p.getIs_cat()) {
        // getting a random image from the list of Cat images
        int imageIndex = rand() % catImageList.size();

        // making a file path to our Cat photo
        QString imageName = catImageList.at(imageIndex);
        QString dirName = ":/cats/Cats/";
        dirName.append(imageName);

        qDebug() << "Loading" << dirName;
        // loading Pet photo from the project resources
        petPic.load(dirName);
        // displaying Pet photo in the animalDisplay on the PetDisplay page
        ui->animalDisplay->setPixmap(petPic.scaled(ui->animalDisplay->width(), ui->animalDisplay->height(), Qt::KeepAspectRatio));
    } else { // Pet is not a Cat, the Pet, p, is a Dog
        int imageIndex = rand() % dogImageList.size();

        // file path to Dog photo
        QString imageName = dogImageList.at(imageIndex);
        QString dirName = ":/dogs/Dogs/";
        dirName.append(imageName);

        qDebug() << "Loading" << dirName;
        // loading Pet photo
        petPic.load(dirName);
        // displaying the Pet photo on the PetDisplay page
        ui->animalDisplay->setPixmap(petPic.scaled(ui->animalDisplay->width(), ui->animalDisplay->height(), Qt::KeepAspectRatio));
    }

    // filling the PetDisplay page with Pet information
    ui->label_name->setText(p.getName());
    ui->label_breed->setText(p.getBreed());
    ui->label_age->setText(QString::number(p.getAge()));

    // the Pet, p, is a Dog
    if (!p.getIs_cat())
        ui->label_type->setText("Dog");
    else // the Pet is a Cat
        ui->label_type->setText("Cat");

    // select query for getting Shelter information based off
    // of the Pet's Shelter
    query.prepare("select shelter_id from pet where pet_id = ?");
    query.addBindValue(p.getPet_id());

    // attempting to execute Shelter select query
    if (query.exec()) {
        if (query.next()) {
            // getting the Pet's Shelter ID
            int shelterID = query.value(0).toInt();

            // creating Shelter object with Shelter ID
            Shelter s(shelterID);
            // filling in Shelter name on PetDisplay page
            ui->label_shelter_name->setText(s.getName());

            // creating Location object with Shelter's Location
            Location loc(s.getLocID());
            // filling in the Location name on PetDisplay
            ui->label_location->setText(loc.getCity());

            // filling in distance information on PetDisplay
            // distance is measured between the adopter/PetOwner and Shelter
            double distance = distanceToUser(loc, currentUser);
            if (distance == 1)
                ui->label_distance->setText("1 mile");
            else
                ui->label_distance->setText(QString::number(distanceToUser(loc, currentUser)) + " miles");
        }
    } else { // unable to execute Shelter query
        qDebug() << "Error getting pet's shelter:" << query.lastError().text();
    }
}

/*
 * getCurrentUser() gets the first name of the User logged in
 * and uses it to display a welcome message on the PetDisplay page
 * this method also keeps track of and updates the liked pets on
 * the PetDisplay status bar at the bottom left corner of the window
 */
void PetDisplay::getCurrentUser()
{
    // getting first name of current user
    QString name = currentUser.getFirstName();
    // welcome message displayed
    ui->label_user_name->setText("Welcome " + name + "!");

    // getting the number of liked Pets for currentUser
    query.prepare("select count(pet_id) from Liked_By where adopter_id = ?");
    query.addBindValue(currentUser.getID());

    // attempting to execute number of liked Pets select query
    if (query.exec()) {
        if (query.next()) {
            // storing number of liked Pets from database into numLiked
            int numLiked = query.value(0).toInt();

            // handling different cases based off of number of liked Pets
            if (numLiked == 1)
                ui->statusbar->showMessage("You have liked 1 pet.");
            else
                ui->statusbar->showMessage("You have liked " + QString::number(numLiked) + " pets.");
        }
    } else { // issue executing number of liked Pets select query
        qDebug() << "Error getting number of pets liked:" << query.lastError().text();
    }
}

/*
 * slot method for opening the PetProfile page containing
 * more detailed information about the currently displayed
 * Pet in the animalDisplay of the PetDisplay page
 */
void PetDisplay::on_profileButton_clicked()
{
    // making sure there are Pets to display
    if (!pets.empty()) {
        // making PetProfile object with PetDisplay as the parent
        profileUI = new PetProfile(this);
        // opening with current Pet displayed
        profileUI->setPDisplay(pets.at(currentPos).first);
        // making sure PetProfile can only be interacted with
        // while still open
        profileUI->setModal(true);
        // opening page
        profileUI->exec();
    }
}

/*
 * slot method for handling liking Pets with the like button
 * on the PetDisplay page
 */
void PetDisplay::on_button_like_clicked()
{
    // checking to see if the Pet vector, pets,
    // is empty -> there are no (more) Pets pulled from
    // the database based off of the last search
    if (!pets.empty()) {
        // getting the current Pet from the Pet vector
        // currentPos is incremented each time a Pet is
        // either liked or disliked
        Pet currPet = pets.at(currentPos).first;

        // currentUser attempting to like the current Pet displayed
        if (currentUser.likePet(currPet)) {
            // checking to see if there's a next pet available
            if (currentPos + 1 > pets.size() - 1) {
                QMessageBox::warning(this, "No More Pets!", "You've successfully liked this pet, but no more pets can be found. Please try expanding your search to find more pets.");
            } else {
                currentPos++; // incrementing Pet count -> moving to next Pet
                displayPet(pets.at(currentPos).first); // display the next Pet
            }
        } else { // currentUser was unable to like the Pet
            QMessageBox::critical(this, "Unable to Like Pet!", "Something went wrong while trying to like this pet. "
                                  "You may have already liked it.");
        }
        updateBar(); // updating progress bar -- adding one more Pet
    }
}

/*
 * slot method for handling disliking Pets with the dislike
 * button on the PetDisplay page
 */
void PetDisplay::on_button_dislike_clicked()
{
    // checking to see if the Pet vector, pets,
    // is empty -> there are no (more) Pets pulled from
    // the database based off of the last search
    if (!pets.empty()) {
        // currentPos is incremented each time a Pet is
        // either liked or disliked
        // checking to see if there's a next pet available
        if (currentPos + 1 > pets.size() - 1) {
            QMessageBox::critical(this, "No More Pets!", "No more pets could be found! Please try expanding your search to find more pets.");
        } else {
            currentPos++; // incrementing Pet count -> moving to next Pet
            displayPet(pets.at(currentPos).first); // display the next Pet
        }
        updateBar(); // updating progress bar -- adding one more Pet
    }
}

/*
 * fetchPets() gets Pet search information from the
 * PetDisplay GUI and creates a select query based
 * off of the chosen attributes selected
 * Once the User has completed selecting attributes,
 * the query is complete and the search is attempted
 */
void PetDisplay::fetchPets()
{
    // getting Pet search info from the PetDisplay UI
    QString type = ui->typeBox->currentText();
    QString breed = ui->breedBox->currentText();
    QString color = ui->colorBox->currentText();
    QString hairLength = ui->hairLenBox->currentText();
    QString hypo = ui->hypoBox->currentText();
    int minAge = ui->minAgeSlider->value();
    int maxAge = ui->maxAgeSlider->value();
    int minWeight = ui->minWeightSlider->value();
    int maxWeight = ui->maxWeightSlider->value();

    // base of the select query being built
    QString queryString = "select * from pet ";

    // checking to see if the User selected a Pet type
    if (type != "Any") {
        // checking to see if the User has clicked the dislike box
        // dislike box reverses the select query to get everything
        // that ISN'T the type selected
        if (ui->dislikeBoxType->checkState() != Qt::Checked) {
            // searching for a Dog
            if (type == "Dog") {
                queryString.append("where is_cat = 0 ");
            // searching for a Cat
            } else if (type == "Cat") {
                queryString.append("where is_cat = 1 ");
            }
        } else {
            // searching for a Cat
            if (type == "Dog") {
                queryString.append("where is_cat != 0 ");
            // searching for a Dog
            } else if (type == "Cat") {
                queryString.append("where is_cat != 1 ");
            }
        }
    }

    // checking to see if the User selected a breed
    if (breed != "Any") {
        // checking to see if the dislike box was not checked
        if (ui->dislikeBoxType->checkState() != Qt::Checked) {
            if (ui->dislikeBoxBreed->checkState() != Qt::Checked) {
                // appending breed condition to select query
                queryString.append("and breed = ");
                queryString.append('\'');
                queryString.append(breed);
                queryString.append('\'');
                queryString.append(" ");
            } else {
                // find every that is not this breed
                queryString.append("and breed != ");
                queryString.append('\'');
                queryString.append(breed);
                queryString.append('\'');
                queryString.append(" ");
            }
        }
    }

    // checking to see if the User selected a color
    if (!color.isEmpty()) {
        // checking to see if the dislike box was not selected
        if (ui->dislikeBoxColor->checkState() != Qt::Checked) {
            // appending color condition to the select query
            queryString.append("and color = ");
            queryString.append('\'');
            queryString.append(color);
            queryString.append('\'');
            queryString.append(" ");
        } else {
            // find every that is not this color
            queryString.append("and color != ");
            queryString.append('\'');
            queryString.append(color);
            queryString.append('\'');
            queryString.append(" ");
        }
    }

    // checking to see if the User selected a hair length
    if (!hairLength.isEmpty()) {
        // checking to see that the dislike box was not checked
        if (ui->dislikeBoxHairLen->checkState() != Qt::Checked) {
            // appending hair length condition to the query
            queryString.append("and hair_type = ");
            queryString.append('\'');
            queryString.append(hairLength);
            queryString.append('\'');
            queryString.append(" ");
        } else {
            // find every that is not this hair length
            queryString.append("and hair_type != ");
            queryString.append('\'');
            queryString.append(hairLength);
            queryString.append('\'');
            queryString.append(" ");
        }
    }

    // checking to see if hypoallergenic status was selected
    if (hypo != "Any") {
        if (hypo == "Yes") { // hypo status selected yes
            queryString.append("and hypoallergenic = 1 ");
        } else if (hypo == "No") { // not hypoallergenic
            queryString.append("and hypoallergenic = 0 ");
        }
    }

    // adding Pet age information to the query - range with minimum and maximum
    if (minAge > 0)
        queryString.append("and age >= " + QString::number(minAge) + " "); // minimum age
    if (maxAge > 0)
        queryString.append("and age <= " + QString::number(maxAge) + " "); // maximum age

    // adding Pet weight information - min and max range
    if (minWeight > 0)
        queryString.append("and weight >= " + QString::number(minWeight) + " "); // min
    if (maxWeight > 0)
        queryString.append("and weight <= " + QString::number(maxWeight) + " "); // max

    qDebug() << "Running query" << queryString;

    std::vector<Pet> tempPets;

    // attempting to execute the built select query
    if (query.exec(queryString)) {
        // checking to see if the vector of searched Pets is not empty
        if (!tempPets.empty())
            // if so, clear the vector for new Pets
            tempPets.clear();

        // adding Pet objects to the vector Pets that fulfill
        // the search conditions
        while (query.next()) {
            // getting Pet ID from database
            int pID = query.value(0).toInt();

            // creating new Pet object by Pet ID
            Pet p(pID);
            // adding Pet to vector
            tempPets.push_back(p);
        }

        // checking to see if the searched Pet vector is not empty
        if (!tempPets.empty()) {
           pets = sortByMatch(tempPets);

            // if not empty, start the Pet counter at 0
            currentPos = 0;
            // display the first Pet in the vector, pets
            displayPet(pets.front().first);

            // reset the Pet liked/disliked progress bar
            ui->progressBar->setValue(currentPos + 1);
            ui->progressBar->setRange(1, pets.size());
        }
        else // no Pets found based off of the search attributes -> Pet vector pets is empty
            QMessageBox::critical(this, "No Pets Found", "No pets could be found with your search parameters. Please change your search and try again.");
    } else { // unable to execute built select query for getting Pet info
        qDebug() << "Error fetching pets:" << query.lastError().text();
    }
}

/*
 * slot method for Logout menu item
 * closes/hides the PetDisplay page and
 * logs the currentUser out of the app
 * shows the MainWindow page with the Login
 * and CreateAccount options
 */
void PetDisplay::on_actionLog_out_triggered()
{
    // hide PetDisplay
    hide();
    // Log out currentUser
    currentUser.logOut();
    // show MainWindow
    parentWidget()->show();
}

/*
 * slot method for triggering the Liked menu
 * item from the menu on the PetDisplay page
 * closes/hides the PetDisplay and creates an
 * instance of the PetLiked page
 * Opens the PetLiked page
 */
void PetDisplay::on_actionLiked_triggered()
{
    // hide PetDisplay
    hide();
    // create PetLiked object pointer with
    // PetDisplay as the parent
    PetLiked *likedUI = new PetLiked(this);
    // deletes PetLiked object when the window is closed
    likedUI->setAttribute(Qt::WA_DeleteOnClose);
    // show the PetLiked page with show() method
    likedUI->show();
}

/*
 * slot method for when the Help menu item is
 * selected from the PetDisplay page
 * closes/hides the PetDisplay page
 * creates and instance of the petownerhelp page
 * shows the petownerliked page
 */
void PetDisplay::on_actionHelp_triggered()
{
    // hiding PetDisplay
    hide();
    // creating a petownerhelp object pointer, helpUI
    petownerhelp *helpUI = new petownerhelp(this);
    // delte petownerhelp page when the window is closed
    helpUI->setAttribute(Qt::WA_DeleteOnClose);
    // show the petownerhelp page
    helpUI->show();
}

// simple method that updates the Pet progress bar by one Pet
void PetDisplay::updateBar()
{
    ui->progressBar->setValue(currentPos+1);
}

/*
 * slot method for keeping track of the value of the minimum
 * age slider for Pet attribute selection
 * updates the label for the slider with the current value of
 * the slider - in years
 */
void PetDisplay::on_minAgeSlider_valueChanged(int value)
{
    QString labelText = "Minimum Age: ";
    QString numText = QString::number(value);
    labelText.append(numText);
    ui->label_search_minage->setText(labelText);
}

/*
 * slot method for keeping track of the value of the maximum
 * age slider for Pet attribute selection
 * updates the label for the slider with the current value of
 * the slider - in years
 */
void PetDisplay::on_maxAgeSlider_valueChanged(int value)
{
    QString labelText = "Maximum Age: ";
    QString numText = QString::number(value);
    labelText.append(numText);
    ui->label_search_maxage->setText(labelText);
}

/*
 * slot method for keeping track of the value of the minimum
 * weight slider for Pet attribute selection
 * updates the label for the slider with the current value of
 * the slider - in pounds
 */
void PetDisplay::on_minWeightSlider_valueChanged(int value)
{
    QString labelText = "Minimum Weight: ";
    QString numText = QString::number(value);
    labelText.append(numText);
    ui->label_search_minweight->setText(labelText);
}

/*
 * slot method for keeping track of the value of the maximum
 * weight slider for Pet attribute selection
 * updates the label for the slider with the current value of
 * the slider - in pounds
 */
void PetDisplay::on_maxWeightSlider_valueChanged(int value)
{
    QString labelText = "Maximum Weight: ";
    QString numText = QString::number(value);
    labelText.append(numText);
    ui->label_search_maxweight->setText(labelText);
}

/*
 * slot method for handling the quit menu option
 * on the PetDisplay page
 * quits the application
 */
void PetDisplay::on_actionQuit_triggered()
{
   QApplication::quit();
}

/*
 * slot method for handling the About BreadnButter
 * menu option
 * opens the about dialog
 */
void PetDisplay::on_actionAbout_BreadnButter_triggered()
{
    QMessageBox::about(this, "About BreadnButter", "Welcome to BreadnButter!\n"
                   "This application allows quick, efficient and effective services for those looking for pets!\n"
                                                  "If you are looking for people to adopt your pets, please don't hesistate to make a shelter account!");
}

QPixmap PetDisplay::getPetPic() const
{
   return petPic;
}









