with open("coor_f.txt") as f:
	data = f.read().split('\n')
with open('buildings_full.txt') as f:
	full_list = f.read().split('\n')
accessible = set()
for i in data:
	accessible.add(i.split(' ')[0])


with open("accessible_building.txt", 'w') as f:
	for i in full_list:
		if (i.replace(" ","") in accessible):
			f.write(i+'\n')
