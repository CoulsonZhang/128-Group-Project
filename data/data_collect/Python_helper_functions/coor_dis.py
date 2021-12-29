from itertools import combinations
import pickle


with open('accessible_building.txt') as f:
	data = f.read().split("\n")


# with open('coor_f.txt') as f:
# 	tmp = f.read().split('\n')
# coor = dict()
# for i in tmp:
# 	name, lat, lng = i.split(" ")
# 	coor[name] = (float(lat), float(lng))

with open('coor_f.pkl', 'rb') as f:
	coor = pickle.load(f)

relation = combinations(data, 2)
with open("building_coor_dis.csv", 'w') as f:
	for i in relation:
		coor_one = coor[i[0].replace(" ","")]
		coor_two = coor[i[1].replace(" ","")]
		weight = 100000 * (coor_one[0] - coor_two[0])**2 + (coor_one[1] - coor_two[1])**2 
		# if (weight != 0):
		f.write("{},{},{}\n".format(i[0].replace(",","."),i[1].replace(",","."),weight))
