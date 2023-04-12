# Breadnbutter

## Building the system

In Qt Creator, build the GUI subproject

The project uses a series of images for placeholders of cats and dogs.

To get these images, navigate to data/photos.
Unzip the Archive.zip file
Move the two directories within the zip file to breadnbutter/gui

In Qt, right click petPhotos.qrc -> open in editor
Add the images in the prefixes corresponding to the directories

The program will also require a SQLite database.
To generate it, navigate to breadnbutter/database

Run the following scripts on db.sqlite:
create_tables.sql
populate_tables.sql

Move this database file into build-breadnbutter-Desktop-Debug/gui

## Two types of users
This software is meant to be used by two kinds of people: prospective pet adopters and owners of animal shelters. Depending on the account currently logged in to the system, the interface will look different. A prospective adopter will be presented with the option to search for pets while a shelter owner will see a dashboard that lists all of the pets in their shelter.

## Sample login credentials

You can create your own account to start using the system. Alternatively, to use the system with sample data already loaded, you can use a sample account. Log in with the following credentials to access a sample adopter account:

> Email: a
> Password: a
