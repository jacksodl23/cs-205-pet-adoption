.mode csv

DELETE from Shelter;

DELETE from Pet_Attributes;

DELETE from Pet;

DELETE from Adopter;

.import ../../data/table_data/Shelter_data.csv Shelter

.import ../../data/table_data/Pet_Attributes_data.csv Pet_Attributes

.import ../../data/table_data/Pet_data.csv Pet

.import ../../data/table_data/Adopter_data.csv Adopter