f = open('Location_data.csv', 'r')
lines = f.readlines()
i = 1
for i in range(len(lines)):
	lines[i] = str(i) + ',' + lines[i]
	i += 1
f.close()

f = open('Location_data.csv', 'w')
f.writelines(lines)
f.close()
