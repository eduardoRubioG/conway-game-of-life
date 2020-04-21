# The Game of Life 

famous game called The Game of Lifewhich was formulated by British mathematician J.H. Conway. The Game of Life is a simulation that models the life cycle of ​simorgs​ (simulatedorganisms). Given an initial pattern, the game simulates the birth and death of future generations using simple rules.  Think of it as a Lava Lamp formathematicians.

Our CSC 380 version of the game will be played on a 20 x 20 two-dimensional grid.Each grid location is either empty or occupied by a single cell (X). 

## Rules 
Each grid location is either empty or occupied by a single living cell (X). A location's neighbors are any cells in the surrounding eight adjacent locations.The simulation starts with an initial pattern of cells on the grid and computes successive generations of cells according to the following five rules:

* A location that has zero or one neighbors will be empty in the next generation. If a cell was there, it does of lonliness. 
* A location with two neighbors is stable. If it had a cell, it still contains a cell. If it was empty, it's still empty. 
* A location with three neighbors will contain a cell in the next generation. If it was unoccupied before, a new cell is born. If it currently contains a cell, the cell remains. 
* A location with four or more neighbors will be empty in the next generation. If there was a cell in that location, it would die of overcrowding. 
* A cell that ages more than 10 generations dies, and will be empty the next generation, regardless of how mnay neighbors it has. 

The births and deaths that transform one generation to the next all take effect simultaneously. When you are computing a new generation, new births/deaths in that generation don't impact other cells in that generation. Any changes (births or deaths) in a given generation​ k start to have effect on other neighboring cells in generation k+1. ​

## User Manual  
There are two main ways to run this program. The first is by feeding it a file representing an intial environment state, and the second is by generating a random environment. 

### File Defined Starting Environment 
This is the deafult way to run the program. Simply type ```make``` in the command line and the default executable will be generated such that you may run the program with the following command: ```./Simorg -f FILE``` where file is the text file you wish to submit. See the ```envs/``` directory for examples on how to format environment files. 

### Randomly Generated Environments 
In order to run the program with a ranomly generated board, type ```make random``` in the command line to compile the program for random initialization. From there, you may run the executable ```./Simorg``` and it will prompt you for a yield percentage. In other words, what percentage of the board you would like to start off active (0 < yield < 1). If an invalid yield is submitted, a default value will be used. 

### Additional Options 
User may also define the max number of generations be editing the pre-processed macro variable, ```MAXGEN``` found on line 4 of ```main.cpp```. Further, user may modify the dimension of the environment by modifying ```DIM``` in line 3 of ```main.cpp``` although this is not recommended as there is no safeguarding features for differently valued dimensions and the user will be prone to errors and segfaults. 

## Project Design 
The main bulk of work is contained within the Simorg class defined in ```Simorg.cpp``` and ```Simorg.h```. The class contains two bool arrays and one int array. The two bool arrays represent the board's active/inactive states and borrow from the concept of buffering in Graphics. One array represents the currently rendered state while the other stores the active states of the next generation so that current moves do not impact calculations for the rest of the board. The int array keeps track of the how many generations a cell has been active and is reset if any generation grows older than 10, in accordance to rule 5. 

> Happy livin' 