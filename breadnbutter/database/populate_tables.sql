.mode csv

DELETE from User;

DELETE from Adopter_Preferences;

DELETE from Shelter;

DELETE from Pet;

DELETE from Pet_Attributes;

.import ../../data/table_data/User_data.csv User

.import ../../data/table_data/Adopter_Preferences_data.csv Adopter_Preferences

.import ../../data/table_data/Shelter_data.csv Shelter

.import ../../data/table_data/Pet_data.csv Pet

.import ../../data/table_data/Pet_Attributes_data.csv Pet_Attributes