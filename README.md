# Breadnbutter

To build the system:

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
