import random as r
import string
import lorem

class Shelter:
	def __init__(self, shelter_id):
		self.shelter_id = shelter_id
		self.name = randLine("sample_data/ShelterNames.txt")
		self.location = randLine("sample_data/Locations.txt")
		self.email = genEmail()

	def toCSV(self):
		line = str(self.shelter_id)
		line += ","
		line += self.name
		line += ","
		line += self.location
		line += ","
		line += self.email
		line += "\n"
		return line

class Pet:
	def __init__(self, pet_id, shelter_id, pet_attribute_id):
		self.pet_id = pet_id
		self.is_cat = r.choice([True, False])
		self.name = randLine("sample_data/PetNames.txt")
		self.shelter_id = shelter_id
		self.pet_attribute_id = pet_attribute_id

	def toCSV(self):
		line = str(self.pet_id)
		line += ","
		line += self.name
		line += ","
		line += str(self.shelter_id)
		line += ","
		line += str(self.pet_attribute_id)
		line += "\n"
		return line

class Adopter:
	def __init__(self, adopter_id, adopter_preferences_id):
		self.adopter_id = adopter_id
		self.name = randLine("sample_data/FirstNames.txt") + " " + randLine("sample_data/LastNames.txt")
		self.email = genEmail()
		self.password = genPassword()
		self.adopter_preferences_id = adopter_preferences_id

	def toCSV(self):
		line = str(self.adopter_id)
		line += ","
		line += self.name
		line += ","
		line += self.email
		line += ","
		line += self.password
		line += ","
		line += str(self.adopter_preferences_id)
		line += "\n"
		return line

class Pet_Attributes:
	def __init__(self, pet_attribute_id, is_cat):
		self.pet_attribute_id = pet_attribute_id
		self.age = r.randint(0, 20)
		if is_cat:
			self.breed = randLine("sample_data/CatBreeds.txt") if (r.random() < 0.5) else "Unknown"
			self.weight = r.randint(5, 18)
		else: 
			self.breed = randLine("sample_data/DogBreeds.txt") if (r.random() < 0.5) else "Mutt"
			self.weight = r.randint(5, 25)
		self.color = r.choice(["black", "white", "orange", "spotted", "brown"])
		self.hair_length = r.choice(["short", "medium", "long"])
		self.origin = r.choice(["Shelter", "Rescue"])
		self.hypoallergenic = (r.random() < 0.05)
		self.description = lorem.sentence()

	def toCSV(self):
		line = str(self.pet_attribute_id)
		line += ","
		line += str(self.age)
		line += ","
		line += self.breed
		line += ","
		line += self.color
		line += ","
		line += self.hair_length
		line += ","
		line += str(self.weight)
		line += ","
		line += self.origin
		line += ","
		line += str(self.hypoallergenic)
		line += ","
		line += self.description
		line += "\n"
		return line

def randLine(filename):
	return r.choice(list(open(filename))).strip()

def genEmail():
	return ''.join(r.choice(string.ascii_letters) for _ in range(r.randint(5,10))) + "@gmail.com"

def genPassword():
	return ''.join(r.choice(string.ascii_letters) for _ in range(r.randint(5,10)))

# Shelters
numShelters = 100
#csv = CsvWriter("Shelter_data.csv")
csv = open("table_data/Shelter_data.csv" ,"w")
shelters = []
for i in range(numShelters):
	s = Shelter(i+1)
	shelters.append(s)
	csv.write(s.toCSV())
csv.close()

# Pets
numPets = 100
# csv.setFile("Pet_data.csv")
pets = []
csv = open("table_data/Pet_data.csv" ,"w")
for i in range(numPets):
	p = Pet(i+1, r.randint(1, 100), i+1)
	pets.append(p)
	csv.write(p.toCSV())
csv.close()

# Adopters
numAdopters = 100
adopters = []
csv = open("table_data/Adopter_data.csv", "w")
for i in range(numAdopters):
	a = Adopter(i+1, numPets+i+1) # to ensure that adopter_preferences_id is unique from pet_preferences_id
	adopters.append(a)
	csv.write(a.toCSV())
csv.close()

# Pet Attributes
petAttributes = []
csv = open("table_data/Pet_Attributes_data.csv", "w")
for i in range(numPets):
	pa = Pet_Attributes(pets[i].pet_attribute_id, pets[i].is_cat)
	petAttributes.append(pa)
	csv.write(pa.toCSV())

for i in range(numAdopters):
	pa = Pet_Attributes(adopters[i].adopter_preferences_id, r.choice([True, False]))
	petAttributes.append(pa)
	csv.write(pa.toCSV())
csv.close()