![image](https://github.com/cs128-2021c/final-project-chong/blob/main/image/UIUC_logo.png)
# CS 128 Final Project Proposal
_Group Name: CHONG_

_Group Member: Jing Zhan, LiLi Sheehan, Zheyu Zhang, Wen Song_

## Project Summary:
Find the shortest route from building A and building B on Campus

## Proposed features & What we accomplish
- Proposed features: given two buildings, calculating the shortest path
- What we have accomplish: a visualized shortest path highlighted on the map
### Sample output:
![image](https://github.com/cs128-2021c/final-project-chong/blob/main/image/demo.png)
### Features we were unable to implement: 
everything in the proposal is accomplished, but maybe we could improve our project by making it more user-friendly, like implementing an iteractive user interface etc. 

## How to run the code
### Compilation environment: standard CS128 environment
- To get the generated map, run
```bash
make
./bin/exec
cd generate_map
python3 generate_map.py
```
Then a file named `demo_map.html` will be generated. Simply double click on it, you will see the generated map.

- To run the tests, simply run
```bash
make tests
./bin/tests
```

### Programming Language used
- C++
- Python

### Data structure Used:
- Graph （Adjacency List)
    - vertex: buildings on campus
    - edge: route between buildings under distance restriction


### Dataset:
- Source: crawling data from website with help of Google API


### Preliminary algorithm applied:
- BFS traversal
- Dijsktra's algorithm


## Planned Workload distribution (subject to change)
- Data retrival : Zheyu Zhang, Wen Song
- Graph structure implementation: Jing Zhan, Wen Song 
- Graph algorithm implementation: Jing Zhan, LiLi Sheehan
- Test: LiLi Sheehan, Zheyu Zhang

## Working Directory Structure
```bash
├── netids
│   ├── jingz15.txt
│   ├── lsheeh3.txt
│   ├── wensong2.txt
│   └── zheyu3.txt
├── data
│   ├── data_collect
│   │   ├── dis_google.py
│   │   └── get_building_list.py
│   ├── data.csv
│   └── test_data.csv
├── includes
│   ├── edge.hpp
│   ├── utilities.hpp
│   └── graph.hpp
├── src
│   ├── utilities.cc
│   └── main.cc
├── Makefile
├── README.md
├── tests
│   ├── catch.cc
│   ├── catch.hpp
│   └── tests.cc
├── image
├── generated_map
├── obj
└── bin
```
