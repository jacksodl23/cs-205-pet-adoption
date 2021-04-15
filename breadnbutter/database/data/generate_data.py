import random as r
import string

class CsvWriter:
	def __init__(self, filename):
		file = open(filename, "w")
		line = ""

	def __del__(self):
		file.close()

	def addCol(self, str):
		line += str
		line += ","

	def nextLine(self):
		file.write(line + "\n")
		line = ""

	def setFile(self, filename):
		file.close()
		file.open(filename, "w")
		line = ""

class Shelter:
	def __init__(self, shelter_id_):
		shelter_id = shelter_id_
		name = randLine("samples/ShelterNames.txt")
		location = randLine("samples/ShelterNames.txt")
		email = genEmail()

	def toCSV(self):
		line = str(shelter_id)
		line += ","
		line += name
		line += ","
		line += location
		line += ","
		line += email
		line += "\n"

class Pet:
	def __init__(self, pet_id_, shelter_id_, pet_attribute_id_):
		pet_id = pet_id_
		is_cat = r.choice([True, False])
		if is_cat:
			name = randLine("samples/CatNames.txt")
		else: 
			name = randLine("samples/DogNames.txt")
		shelter_id = shelter_id_
		pet_attribute_id = pet_attribute_id_

	def toCSV(self):
		line = str(pet_id)
		line += ","
		line += name
		line += ","
		line += shelter_id
		line += "\n"

class Pet_Attributes:
	def __init__(self, pet_attribute_id_, is_cat):
		pet_attribute_id = pet_attribute_id_
		age = r.randint(0, 20)
		if is_cat:
			breed = randLine("samples/CatBreeds.txt")
		else: 
			breed = randLine("samples/DogBreeds.txt")
		color = r.choice(["black", "white", ""])


  Color TEXT,
  Hair_Length TEXT,
  Weight INTEGER,
  Origin TEXT,
  Hypoallergenic TEXT,
  Description TEXT

def randLine(filename):
	return r.choice(list(open(filename)))

def genEmail():
	return ''.join(r.choice(string.ascii_letters) for _ in range(r.randint(5,10))) + "@gmail.com"


# Shelters
numShelters = 100

CsvWriter csv("Shelter_data.csv")
for i in range(numShelters):
	csv.addCol(i+1)
	csv.addCol(randLine('samples/ShelterNames.txt'))
	csv.addCol(randLine('samples/Locations.txt'))
	csv.addCol(genEmail())
	csv.nextLine()

# Pets
numPets = 100
csv.setFile("Pet_data.csv")
for i in range(numPets):
	csv.addCol(i+1)
	csv.addCol(randLine('samples/PetNames'))
	csv.addLine()
	csv.nextLine()


# Pet Attributes

csv.setFile("Pet_Attributes_data.csv")
for i in range(numPets):
	if (r.randint(0, 1)):
		# cat
		csv.addCol(i+1)
		csv.addCol()
		csv.addCol(r.randint(0, 20))
		csv.addCol(r.choice(line(open('samples/Locations.txt'))))
		csv.addCol(genEmail())
		
	else:
		# dog
		csv.addCol(i+1)
		csv.
		csv.addCol(r.randint(0, 20))
		csv.addCol(r.choice(line(open('samples/Locations.txt'))))
		csv.addCol(genEmail())
	csv.nextLine()


  Breed TEXT,
  Color TEXT,
  Hair_Length TEXT,
  Weight INTEGER,
  Origin TEXT,
  Hypoallergenic TEXT,
  Description TEXT