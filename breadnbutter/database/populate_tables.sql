.mode csv

DELETE from User;
DELETE from Shelter;
DELETE from Pet;
DELETE from Adopter_Preferences;
DELETE from Liked_By;
DELETE from Breed_Pref;
DELETE from Location;

.import ../../data/table_data/User_data.csv User
.import ../../data/table_data/Shelter_data.csv Shelter
.import ../../data/table_data/Pet_data.csv Pet
.import ../../data/table_data/Adopter_Preferences_data.csv Adopter_Preferences
.import ../../data/table_data/Liked_By_data.csv Liked_By
--.import ../../data/table_data/Breed_Pref_data.csv Breed_Pref
.import ../../data/table_data/Location_data.csv Location
