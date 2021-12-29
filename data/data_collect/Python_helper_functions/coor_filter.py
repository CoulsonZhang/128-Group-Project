with open("clean_coor.txt", "r") as f:
	data = f.read().split('\n')

with open("coor_f.txt", 'w') as f:
	for i in data:
		name, lat, lng = i.split(" ")
		if (float(lat) <= 39.8 or float(lat) >= 40.4):
			print("Info show: name: {}; lat: {}; lng:{} \n".format(name,lat,lng))
		else:
			f.write("{}\n".format(i))

# 
# 	for i in data:
# 		if not(i.endswith('No Info')):
# 			f.write("{}\n".format(i))