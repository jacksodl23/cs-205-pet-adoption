import random as r
import string
import lorem

# class CsvWriter:
# 	def __init__(self, filename):
# 		self.filename = filename
# 		self.file = open(filename, "w")
# 		self.line = ""

# 	# def __del__(self):
# 	# 	self.file.close()

# 	def addCol(self, string):
# 		self.line += string
# 		self.line += ","

# 	def nextLine(self):
# 		self.file.write(line + "\n")
# 		self.line = ""

# 	def addLine(self, string):
# 		self.file.write(str(string) + "\n")
# 		self.line = ""

# 	def setFile(self, filename):
# 		self.file.close()
# 		self.file.open(filename, "w")
# 		self.line = ""

class Shelter:
	def __init__(self, shelter_id):
		self.shelter_id = shelter_id
		self.name = randLine("samples/ShelterNames.txt")
		self.location = randLine("samples/Locations.txt")
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
		self.name = randLine("samples/PetNames.txt")
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

class Pet_Attributes:
	def __init__(self, pet_attribute_id, is_cat):
		self.pet_attribute_id = pet_attribute_id
		self.age = r.randint(0, 20)
		if is_cat:
			self.breed = randLine("samples/CatBreeds.txt")
			self.weight = r.randint(5, 18)
		else: 
			self.breed = randLine("samples/DogBreeds.txt")
			self.weight = r.randint(5, 25)
		self.color = r.choice(["black", "white", "orange", "spotted", "brown"])
		self.hair_length = r.choice(["short", "medium", "long"])
		self.origin = lorem.sentence()
		self.hypoallergenic = (r.random() < 0.20)
		self.description = lorem.sentence()

	def toCSV(self):
		line = str(pet_attribute_id)
		line += ","
		line += age
		line += ","
		line += breed
		line += ","
		line += color
		line += ","
		line += hair_length
		line += ","
		line += weight
		line += ","
		line += origin
		line += ","
		line += hypoallergenic
		line += ","
		line += description
		line += "\n"
		return line

def randLine(filename):
	return r.choice(list(open(filename))).strip()

def genEmail():
	return ''.join(r.choice(string.ascii_letters) for _ in range(r.randint(5,10))) + "@gmail.com"


# Shelters
numShelters = 100
#csv = CsvWriter("Shelter_data.csv")
csv = open("Shelter_data.csv" ,"w")
for i in range(numShelters):
	s = Shelter(i+1)
	csv.write(s.toCSV())
csv.close()

# Pets
numPets = 100
# csv.setFile("Pet_data.csv")
csv = open("Pet_data.csv" ,"w")
for i in range(numPets):
	p = Pet(i+1, r.randint(1, 100), i+1)
	csv.write(p.toCSV())
csv.close()



# # Pet Attributes
# csv.setFile("Pet_Attributes_data.csv")
# for i in range(numPets):
# 	if (r.randint(0, 1)):
# 		# cat
# 		csv.addCol(i+1)
# 		csv.addCol()
# 		csv.addCol(r.randint(0, 20))
# 		csv.addCol(r.choice(line(open('samples/Locations.txt'))))
# 		csv.addCol(genEmail())
		
# 	else:
# 		# dog
# 		csv.addCol(i+1)
# 		csv.
# 		csv.addCol(r.randint(0, 20))
# 		csv.addCol(r.choice(line(open('samples/Locations.txt'))))
# 		csv.addCol(genEmail())
# 	csv.nextLine()