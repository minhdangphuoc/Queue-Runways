# Queue-Runways 🛫🛬
- This is a repository for airport simulation using Queues data structure.
- The source code is done for 5G00DM61-3003 Programming Languages 3.

## Concept
Simulation is the use of one system to imitate the behavior of another system. A computer simulation is a program to imitate the behavior of the system under study.
1. The same runway is used for both landings and takeoffs.
2. One plane can land or take off in a unit of time, but not both.
3. A random number of planes arrive in each time unit.
4. A plane waiting to land goes before one waiting to take off.
5. The planes that are waiting are kept in queues landing and takeoff, both of which have a strictly limited size.
 
## Requirements
1. Combine all the functions and methods for the airport simulation into a com-plete program. Experiment with several sample runs of the airport simulation, adjusting the values for the expected numbers of planes ready to land and take off. Find approximate values for these expected numbers that are as large as possible subject to the condition that it is very unlikely that a plane must be refused service. What happens to these values if the maximum size of the queues is increased or decreased? 
2. Modify the simulation to give the airport two runways, one always used for landings and one always used for takeoffs. Compare the total number of planes that can be served with the number for the one-runway airport. Does it more than double? 
3. Modify the simulation to give the airport two runways, one usually used for landings and one usually used for takeoffs. If one of the queues is empty, then both runways can be used for the other queue. Also, if the landing queue is full and another plane arrives to land, then takeoffs will be stopped and both runways used to clear the backlog of landing planes. 
4. Modify the simulation to have three runways, one always reserved for each of landing and takeoff and the third used for landings unless the landing queue is empty, in which case it can be used for takeoffs. 
5. Modify the original (one-runway) simulation so that when each plane arrives to land, it will have (as one of its data members) a (randomly generated) fuel level, measured in units of time remaining. If the plane does not have enough fuel to wait in the queue, it is allowed to land immediately. Hence the planes in the landing queue may be kept waiting additional units, and so may run out of fuel themselves. Check this out as part of the landing function, and find about how busy the airport can become before planes start to crash from running out of fuel. 

## Manual
This project using meson to build, so you have to download and install it to your computer.
[Meson Build](https://mesonbuild.com/)

### Build
``` cli
meson setup builddir //  Initialize the build
cd builddir // Move to build dirrectory
ninja && ./main // Run built
```

### Change name of built
Change this code in meson.build for changing the name.
```
// meson.build
...
executable('main', './/src//main.cpp', link_with : lib) // change main to another name
...
```
## Issues
- In Program 5, if there are 2 planes which have low fuel - equal to 1 unit, the program keeps running because the requirement did not include consequence for that scenario.
