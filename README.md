# About

This is a university project for the course "Object-Oriented Programming". The task was to implement a simuation of a pizzeria in which guests come to the premise in groups and order food from the user-defined menu. The simulation is turn-based, meaning that events for each table are progressed (if possible) in a concurrent way. Food can also have different preparation time (number of turns), and is delivered to the table only if every order position is ready to be delivered (for example, if one guest at the table orders something that takes 4 turns to prepare, and another person orders food that takes 6 turns, food will be delivered to both of them at once after 6 turns). At the end the total earnings are summed up and displayed to the user. Each event (guests coming, their orders, unforseen events, payments, etc.) is also logged in a file so that you can analyze the simulation course.

# How to run

In order to run the simulation, you will need:
- C++ in version 17
- CMake in version at least 3.10

After you have installed these programs, you can build the project by running the following commands (Linux):
```bash
mkdir build
cd build
cmake ..
make
```

In order to run the tests, you can do the following command:
```bash
./src/tests/Pizzeria-tests
```

In order to run the simulation, you need to run the following command:
```bash
./src/Pizzeria-simulator <menu file path> <number of turns> <number of 2-person tables> <number of 4-person tables> <number of 8-person tables> <number of waiters>
```
Example run: `./src/Pizzeria-simulator ../menu.txt 2 3 4 5`.
