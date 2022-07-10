#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

int main(int argc, char *argv[]){

    //check for correct command line arguments
    if(argc != 5){
        return EXIT_FAILURE;
    }

    //open binary input file
    FILE * input = fopen(argv[1], "r");
    if(input == NULL){
        return EXIT_FAILURE;
    }

    //open text grid file (output 1)
    FILE * text_grid = fopen(argv[2], "w");
    if(text_grid == NULL){
        fclose(input);
        return EXIT_FAILURE;
    }

    //turn input file into text grid (output 1), then close output file 1
    short m = get_m(input);
    short n = get_n(input);
    short **grid = make_grid(input, text_grid, m, n);

    //close first output after writing to it
    fclose(text_grid);

    //output 2 

    //open fastest paths file (output 2)
    FILE * output2 = fopen(argv[3], "wb");
    if(output2 == NULL){
        fclose(input);
        free_grid(grid, m);
        return EXIT_FAILURE;
    }

    if(m > 50){
        //open fastest path file (output 3)
        FILE * output3 = fopen(argv[4], "w");
        if(output3 == NULL){
            fclose(input);
            fclose(output2);
            free_grid(grid, m);
            return EXIT_FAILURE;
        }
        fclose(input);
        fclose(output2);
        free_grid(grid, m);
        fclose(output3);

        return EXIT_SUCCESS;
    }

    //open fastest path file (output 3)
    FILE * output3 = fopen(argv[4], "w");
    if(output3 == NULL){
        fclose(input);
        fclose(output2);
        free_grid(grid, m);
        return EXIT_FAILURE;
    }
    
    fastest_paths(output2, grid, m , n, output3);


    //close input file
    fclose(input);
    fclose(output2);

    fclose(output3);

    //free grid
    free_grid(grid, m);

    return EXIT_SUCCESS;
}