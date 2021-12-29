import requests
from bs4 import BeautifulSoup
import re


uiuc_building_URL = "https://fs.illinois.edu/about-us/building-list-by-building-number"

res = requests.get(uiuc_building_URL)

html = res.text
soup = BeautifulSoup(html, 'html.parser')
items = soup.find_all(class_='sflistListItem')
with open('/Users/coulson/Desktop/CS128_final/buildings.txt', "w") as f:
    for item in items:
        result = re.findall(r'\n\d{4}\n(.*?)\n',item.text)
        for i in result:
            f.write(i + '\n')

