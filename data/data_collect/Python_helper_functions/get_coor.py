import API_KEY as a
API = a.API #actual key not shown
import requests

with open('buildings_full.txt') as f:
    data = f.read().split('\n')

with open('test.txt', 'w') as f:
    for i in range(1):
        test = data[i]
        print(test)
        url = ("https://maps.googleapis.com/maps/api/geocode/json?address={}&key={}".format(test +',champaign,IL', API)).replace(" ","")
        res = requests.get(url).json()
        print(res)
        if (res['status'] == 'OK'):
            lat = res['results'][0]['geometry']['location']['lat']
            lng = res['results'][0]['geometry']['location']['lng']
            f.write('{} {} {}\n'.format(test.replace(" ",""), lat, lng))
        else:
            f.write('{} {} {}\n'.format(test, "No", "Info"))




# with open('try.txt', 'w') as f:
#     f.write(str(res))