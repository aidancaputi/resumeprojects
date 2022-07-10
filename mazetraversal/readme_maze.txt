This project is essentially finding the fastest way out of a maze in which each point in the maze has a 
designated amount of "time" that is required to be "spent" there.

Imagine this grid: 
4 2 1 0 5 
2 0 4 1 0 
4 2 2 2 7 
1 7 2 9 2

This project finds the path:
4 X 1 0 5 
2 X 4 1 0 
4 X X 2 7 
1 7 X 9 2

Which would result in a total time of 6 seconds (you do not have to count the time of the starting grid 
location). 

It takes one input, which is the grid information stored in a file formatted in the following way:

- the first two shorts stored are the rows and columns in the grid
- after the dimensions, the grid is listed as shorts where the first M shorts are the top row, the second
  M shorts are the second row, etc. 

This makes the total input file size: ((2 + MN) * 2) bytes.

It produces 3 output files in the following format:

- the first output file will be a textual representation of the grid provided that is displayed as the above
  grids in this readMe are
- the second output file will store the fastest time to exit the grid for all entry locations in binary
- the third output will be the fastest path out of all the possible entry points, again in binary 


