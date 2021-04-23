import random as r
import string
import lorem

"""
create shelters 
	for each shelter create a shelter owner
create pets
	use number that defines average number of pets per shelter (rand(1-5) per shelter will average to 3*numShelter)
	for each shelter create, the random number of pets will be in each shelter
	each pet creates their pet_attributes values and pushes those
create adopters
	each adopter creates their adopter_preferences values and pushes those
	TODO: each adopter creates their breed_preferences values, links to their adopter_preferences and pushes
	TODO: each adopter creates liked_by entries based on pets (not within preferences for now)
"""

numShelters = 100
avg_pets_shelter = 10
numAdopters = 100
avg_adopt_likes = 10


class ID_ctr:
	def __init__(self):
		self.id_ctr = 0

	def nextID(self):
		self.id_ctr += 1
		return self.id_ctr

_user_id = ID_ctr()
_shelter_id = ID_ctr()
_pet_id = ID_ctr()
_pet_attr_id = ID_ctr()
_adopt_pref_id = ID_ctr()
_liked_by_id = ID_ctr()
_breed_pref_id = ID_ctr()

class Shelter_Owner:
	def __init__(self):
		self.user_id = _user_id.nextID()
		self.name = genName()
		self.location = randLine("sample_data/Locations.txt")
		self.email = genEmail()
		self.password = genPassword()

	def toCSV(self):
		line = str(self.user_id) + ","
		line += self.name + ","
		line += self.location + ","
		line += self.email + ","
		line += self.password + ","
		line += "0"
		line += "\n"
		return line

class Shelter:
	def __init__(self):
		self.shelter_id = _shelter_id.nextID()
		self.name = randLine("sample_data/ShelterNames.txt")
		self.location = randLine("sample_data/Locations.txt")
		self.email = genEmail()
		self.owner = Shelter_Owner()


	def toCSV(self):
		line = str(self.shelter_id) + ","
		line += str(self.owner.user_id) + ","
		line += self.name + ","
		line += self.location + ","
		line += self.email
		line += "\n"
		return line

class Pet_Attributes:
	def __init__(self, pet_id):
		self.pet_attribute_id = _pet_attr_id.nextID()
		self.pet_id = pet_id
		self.is_cat = r.choice([1, 0])
		self.age = r.randint(0, 20)
		if self.is_cat:
			self.breed = randLine("sample_data/CatBreeds.txt") if (r.random() < 0.5) else "Unknown"
			self.weight = r.randint(5, 18)
		else: 
			self.breed = randLine("sample_data/DogBreeds.txt") if (r.random() < 0.5) else "Mutt"
			self.weight = r.randint(5, 25)
		self.origin = r.choice(["Shelter", "Breeder", "Rescue"])
		self.hypoallergenic = 1 if (r.random() < 0.05) else 0

	def toCSV(self):
		line = str(self.pet_attribute_id) + ","
		line += str(self.pet_id) + ","
		line += str(self.is_cat) + ","
		line += str(self.age) + ","
		line += self.breed + ","
		line += str(self.weight) + ","
		line += self.origin + ","
		line += str(self.hypoallergenic)
		line += "\n"
		return line

class Pet:
	def __init__(self, shelter_id):
		self.pet_id = _pet_id.nextID()
		self.name = randLine("sample_data/PetNames.txt")
		self.shelter_id = shelter_id
		self.attributes = Pet_Attributes(self.pet_id)
		self.pet_attribute_id = self.attributes.pet_attribute_id
		self.color = r.choice(["black", "white", "orange", "spotted", "brown"])
		self.hair_length = r.choice(["short", "medium", "long"])
		self.description = lorem.sentence()

	def toCSV(self):
		line = str(self.pet_id) + ","
		line += self.name + ","
		line += str(self.shelter_id) + ","
		line += str(self.pet_attribute_id) + ","
		line += self.color + ","
		line += self.hair_length + ","
		line += self.description
		line += "\n"
		return line

class Adopter_Preferences:
	def __init__(self, adopter_id):
		self.adopter_pref_id = _adopt_pref_id.nextID()
		self.adopter_id = adopter_id
		self.age_min = r.randint(0, 20)
		self.age_max = r.randint(self.age_min, 20)
		self.weight_min = r.randint(0, 50)
		self.weight_max = r.randint(self.weight_min, 50)
		self.origin = r.choice(["Shelter", "Breeder", "Rescue", "Either"])
		self.hypoallergenic = 1 if (r.random() < 0.05) else 0
		self.wants_cat = r.choice([1, 0])

	def toCSV(self):
		line = str(self.adopter_pref_id) + ","
		line += str(self.adopter_id) + ","
		line += str(self.age_min) + ","
		line += str(self.age_max) + ","
		line += str(self.weight_min) + ","
		line += str(self.weight_max) + ","
		line += self.origin + ","
		line += str(self.hypoallergenic) + ","
		line += str(self.wants_cat)
		line += "\n"
		return line

class Adopter:
	def __init__(self):
		self.user_id = _user_id.nextID()
		self.name = genName()
		self.location = randLine("sample_data/Locations.txt")
		self.email = genEmail()
		self.password = genPassword()
		self.preferences = Adopter_Preferences(self.user_id)

	def toCSV(self):
		line = str(self.user_id) + ","
		line += self.name + ","
		line += self.location + ","
		line += self.email + ","
		line += self.password + ","
		line += "1"
		line += "\n"
		return line

	def changeInfo(self, name, email, password):
		self.name = name
		self.email = email
		self.password = password

def randLine(filename):
	return r.choice(list(open(filename))).strip()

def genName():
	return randLine("sample_data/FirstNames.txt") + " " + randLine("sample_data/LastNames.txt")

def genEmail():
	return ''.join(r.choice(string.ascii_letters) for _ in range(r.randint(5,10))) + "@gmail.com"

def genPassword():
	return ''.join(r.choice(string.ascii_letters) for _ in range(r.randint(5,10)))

# Shelters
csv1 = open("table_data/Shelter_data.csv", "w")
csv2 = open("table_data/User_data.csv", "w")
shelters = []
shelter_owners = []
for _ in range(numShelters):
	s = Shelter()
	shelters.append(s)
	csv1.write(s.toCSV())
	csv2.write(s.owner.toCSV())
csv1.close()
csv2.close()

# Pets
pets = []
csv1 = open("table_data/Pet_data.csv", "w")
csv2 = open("table_data/Pet_Attributes_data.csv", "w")
for s in shelters:
	for _ in range(avg_pets_shelter):
		p = Pet(s.shelter_id)
		pets.append(p)
		csv1.write(p.toCSV())
		csv2.write(p.attributes.toCSV())
csv1.close()
csv2.close()

# Adopters
adopters = []
csv1 = open("table_data/User_data.csv", "a")
csv2 = open("table_data/Adopter_Preferences_data.csv", "w")
for i in range(numAdopters):
	a = Adopter()
	adopters.append(a)
	csv1.write(a.toCSV())
	csv2.write(a.preferences.toCSV())
# default account to login
default = Adopter()
default.changeInfo("John Smith", "johnsmith@gmail.com", "hello")
adopters.append(default)
csv1.write(default.toCSV())
csv2.write(default.preferences.toCSV())
csv1.close()