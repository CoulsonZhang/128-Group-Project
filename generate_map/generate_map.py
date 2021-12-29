import folium

with open('coor_f.txt', 'r') as f:
    data = f.read().split('\n')
coor = dict()
for i in data:
    name, lat, lng = i.split(" ")
    coor[name] = (float(lat), float(lng))
    
# with open('coor_f.pkl', 'rb') as f:
#     coor = pickle.load(f)



with open("path.txt", 'r') as f:
    data = f.read().split('\n')
first_coor = coor[data[0].replace(" ","")]
m = folium.Map(location=[first_coor[0], first_coor[1]], zoom_start=17)
num = 1
pre = None
for idx in range(len(data)):
    i = data[idx]
    if (idx == 0):
        bgc = 'red'
    elif (idx == (len(data)-1)):
        bgc = 'green'
    else:
        bgc = 'blue'

    coordinate = coor[i.replace(" ","")]
    folium.Marker(location=[float(coordinate[0]), float(coordinate[1])], popup="{}th Stop".format(num), tooltip=i,
                  icon=folium.Icon(icon="info-sign", color= bgc)).add_to(m)
    if (pre):
        pre_coor = coor[pre.replace(" ","")]
        folium.PolyLine(locations=[coordinate, pre_coor], rotation = 6 ).add_to(m)
    num += 1
    pre = i

m.save('demo_map.html')