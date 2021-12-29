from itertools import combinations
import requests
import json
import time
import API_KEY as a
API = a.API #actual key not shown

def find_dis(ori, des):

    origin = ori+',champaign,IL'
    destination = des+',champaign,IL'

    url = "https://maps.googleapis.com/maps/api/distancematrix/json?origins={}&destinations={}&key={}".format(origin.replace(" ",""), destination.replace(" ",""), API)
    print(url)
    payload={}
    headers = {}
    response = requests.get(url, headers=headers, data=payload).json()
    print("response:{}".format(response))
    try:
        distance = ((response['rows'][0]['elements'][0]['distance']['text']))
    except:
        return False,0
    #print("bool:{}; type:{}\nori:{}\ndes:{}\ndis:{}\nresponse:{}\nurl:{}\n".format(bool,type(distance),origin,destination,distance.split(' ')[0],response,url))
    #print("type of result:{}".format(type(distance.split(' ')[0])))

    return True, float(distance.split(' ')[0].replace(",",""))

if __name__ == "__main__":
    building = []
    with open('/Users/coulson/Desktop/CS128_final/buildings.txt', "r") as f:
        for i in (f.read().split('\n')):
            building.append((i))


    with open('/Users/coulson/Desktop/CS128_final/test_data.csv', "w") as f:
        rela = combinations(building, 2)
        for i in rela:
            time.sleep(0.5)
            bool, dis = find_dis(i[0], i[1])
            if (bool and dis <= 5):
                f.write("{},{},{}\n".format(i[0].replace(",",""), i[1].replace(",",""), dis))
                print("{}".format("{},{},{}\n".format(i[0].replace(",",""), i[1].replace(",",""), dis)))
