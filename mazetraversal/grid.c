#include <stdio.h>
#include "grid.h"
#include <stdlib.h>

//this reads the number of rows from the input file
short get_m(FILE *input){
    short m = 0;
    fread(&m, 2, 1, input);

    return m;
}

//this reads the number of columns from the input file
short get_n(FILE *input){
    short n = 0;
    fread(&n, 2, 1, input);

    return n;
}

//this reads the input file, creates a 2D array grid of shorts, and returns that grid
short **make_grid(FILE *input, FILE *output1, short m, short n){

    //initialize 2D array for the grid
    short **grid = malloc(m * sizeof(short*));
    for (int x = 0; x < m; x++)
    {
        grid[x] = malloc(sizeof(short) * n);
    }
    
    //write m and n to output 1
    fprintf(output1,"%hd %hd\n", m, n);

    //print text grid to output 1
    short temp = 0;
    for(int k = 0; k < m; k++){ //for each row

        for(int i = 0; i < n; i++){ //for each column

            //read a short from the input and put it in the grid
            fread(&temp, 2, 1, input);
            fprintf(output1,"%hd", temp);

            //put this short into the 2d grid array
            grid[k][i] = temp;

            //if its not the last short in the row, put a space
            if(i != n - 1){
                fprintf(output1," ");
            }

        }
        
        fprintf(output1,"\n"); //move to next row
    }

    return grid;

}

//upward heapify given heap array and new size
void upward_heapify(heap_node **heap, int n){
    heap_node *temp;
    for (int i = 0; i < n; i++){
        int parent = i;
        while((parent > 0 && (heap[parent / 2]->dist > heap[parent]->dist))){
            temp = heap[parent / 2];
            heap[parent / 2] = heap[parent];
            heap[parent] = temp;
            parent = parent / 2;
        }
    }
}

//downward heapify based on the element to be removed and the size of the heap
void downward_heapify(heap_node **heap, int i, int n){
    heap_node *temp = heap[i];
    int j = 0;
    while((j = 2*i + 1) < n){
        if((j < n) && heap[j]->dist > heap[j + 1]->dist){
            j = j + 1;
        }
        if(temp->dist <= heap[j]->dist){
            break;
        }
        else{
            heap[i] = heap[j];
            i = j;
        }
    }
    heap[i] = temp;
}

//extract the minimum from the heap given its size
short extract_min(heap_node **heap, int size){
    short min = heap[0]->idx;
    heap_node *temp;
    temp = heap[0];
    heap[0] = heap[size - 1];
    heap[size - 1] = temp;
    heap[size - 1]->dist = 3000000000;
    downward_heapify(heap, 0, size - 1);
    return min;
}

//this 
void fastest_paths(FILE *output2, short **grid, short m, short n, FILE *output3){
    
    short * weights = malloc(sizeof(short) * m * n);
    for(int j = 0; j < m; j++){
        for(int k = 0; k < n; k++){
            weights[(j * n) + k] = grid[j][k];
        }
    }

    path_node **fastest_path = malloc(sizeof(path_node*) * n);

    //output 2 writing
    fwrite(&n, sizeof(short), 1, output2);
    long long min = 0;
    long long overall_min = 0;
    int best = 0;
    for (int i = 0; i < n; i++){ //entrance location
        long long *bottom = dijkstra(grid, weights, i, m, n, output3, fastest_path); //bottom exit times
        
        min = bottom[0]; //set the min to the first bottom exit time
        for(int p = 1; p < n; p++){ //for each exit location
            if(bottom[p] < min){ //if its smaller than the current
                min = bottom[p]; //replace the current one
            }
        }
        if(overall_min > min || overall_min == 0){ 
                    overall_min = min;
                    best = i;
        }
        fwrite(&min, sizeof(int), 1, output2);
        free(bottom);
    }

    //-------------output3  
    path_node *temp = fastest_path[best];
    int count = 0;
    while(temp != NULL){
        count++;
        temp = temp->prev;
    }

    fwrite(&overall_min, sizeof(int), 1, output3);
    fwrite(&count, sizeof(int), 1, output3);

    //reverses the path found so that its in the correct order
    reverse(fastest_path[best], output3, m, n);    

    free_path(fastest_path, n);

    free(weights);

}

void free_path(path_node **path, int len){
    for (int i = 0; i < len; i++)
    {
        path_node * temp;
        while(path[i] != NULL){
            temp = path[i];
            path[i] = path[i]->prev;
            free(temp);
        }
    }
    free(path);
}

void reverse(path_node *temp, FILE *output3, short m, short n){
    if(temp == NULL){
        return;
    }
    reverse(temp->prev, output3, m, n);
    //fprintf(output3, "%d %d\n", temp->idx / n, temp->idx % n);
    short x = temp->idx / n;
    short y = temp->idx % n;

    fwrite(&x, sizeof(short), 1, output3);
    fwrite(&y, sizeof(short), 1, output3);
}

heap_node *create_heap_node(short index, long long distance){
    heap_node *new = malloc(sizeof(heap_node));
    new->dist = distance;
    new->idx = index;
    return new;
}

long long *dijkstra(short **grid, short *weights, short start, short m, short n, FILE *output3, path_node **fastest_path){
    
    //create heap, prev, and distance arrays
    heap_node **heap = malloc(sizeof(heap_node*) * m * n);

    //initialize distance grid
    long long **distance = malloc(m * sizeof(long long*));
    for (int x = 0; x < m; x++)
    {
        distance[x] = malloc(sizeof(long long) * n);
    }

    //initializing stuff
    for (int i = 0; i < m; i++){ //for each row
        for (int k = 0; k < n; k++){ //for each column
            if (i != 0 || (i == 0 && k != start)){ //if its not the start node
                distance[i][k] = 3000000000; //set its distance to -1
                
                heap[(i * n) + k] = create_heap_node((i * n) + k, distance[i][k]); //put the current index in the heap
                upward_heapify(heap, (i * n) + k); //move the smallest to top of heap
            }
            else{ //if it was the start node
                distance[i][k] = 0; //set distance to start node value
                heap[(i * n) + k] = create_heap_node((i * n) + k, distance[i][k]);; //put it into heap
                upward_heapify(heap, (i * n) + k); //upward heapify (this should leave this node at the end since its the biggest at the start)
            }
        }
    }

    int quit = m * n;
    int curr = -1;
    while(quit != 0){

        curr = extract_min(heap, quit);
        quit--;

        if(check_q(heap, curr + n, quit) == 1 && ((distance[(curr / n) + 1][curr % n] > distance[curr / n][curr % n] + weights[curr]))){

            distance[(curr / n) + 1][curr % n] = distance[curr / n][curr % n] + weights[curr];

            update_dist_in_heap(heap, curr + n, distance[curr / n][curr % n] + weights[curr], quit);
            update_prev_in_heap(heap, curr + n, curr, quit);

            upward_heapify(heap, quit);

        }
        if(check_q(heap, curr + 1, quit) == 1 && ((curr % n) != (n - 1)) && ((distance[(curr / n)][(curr % n) + 1] > distance[curr / n][curr % n] + weights[curr]))){
            distance[curr / n][(curr % n) + 1] = distance[curr / n][curr % n] + weights[curr];

            update_dist_in_heap(heap, curr + 1, distance[curr / n][curr % n] + weights[curr], quit);
            update_prev_in_heap(heap, curr + 1, curr, quit);

            upward_heapify(heap, quit);
        }
        if(check_q(heap, curr - 1, quit) == 1 && (curr % n != 0) && ((distance[(curr / n)][(curr % n) - 1] > distance[curr / n][curr % n] + weights[curr]))){

            distance[curr / n][(curr % n) - 1] = distance[curr / n][curr % n] + weights[curr];

            update_dist_in_heap(heap, curr - 1, distance[curr / n][curr % n] + weights[curr], quit);
            update_prev_in_heap(heap, curr - 1, curr, quit);

            upward_heapify(heap, quit);
        }
    }

    //set the bottom row of the distance grid to a new return variable
    long long *bottom_row = malloc(sizeof(long long) * n);
    for(int i = 0; i < n; i++){
        bottom_row[i] = distance[m - 1][i] + grid[m - 1][i];
    }

    int min = bottom_row[0];
    int min_idx = 0;
    for (int i = 0; i < n; i++)
    {
        if(bottom_row[i] < min){
            min_idx = i;
            min = bottom_row[i];
        }
    }
    
    path_node * fastest_path_local = actual_path(heap, m, n, start, min_idx);

    fastest_path[start] = fastest_path_local;

    free_distance(distance, m);
    free_heap(heap, n * m);

    return bottom_row;
}

path_node * actual_path(heap_node **heap, short m, short n, short start, short end){
    

    path_node *path = create_path_node((m * n) - (n - end));
    path_node *temp = path;
    
    int curr = (m * n) - (n - end);
    int y = m - 1;
    int prev = -1;

    while(y > 0){
        prev = heap[find_in_heap(heap, m * n, curr)]->prev;
        temp->prev = create_path_node(prev);
        temp = temp->prev;
        curr = prev;
        
        y = curr / m - 1;
    }
    while(curr != start){
        prev = heap[find_in_heap(heap, m * n, curr)]->prev;
        temp->prev = create_path_node(prev);
        temp = temp->prev;
        curr = prev;
    }

    return path;
}

path_node * create_path_node(int index){
    path_node * new = malloc(sizeof(path_node));
    new->idx = index;
    new->prev = NULL;
    return new;
}

int find_in_heap(heap_node **heap, int size, int looking){
    for (int i = 0; i < size; i++)
    {
        if(heap[i]->idx == looking){
            return i;
        }
    }
    return -1;
}

void free_paths(int **paths, int len){
    for (int i = 0; i < len; i++)
    {
        free(paths[i]);
    }
    free(paths);
}

//frees the 2d array grid
void free_grid(short **grid, int m){
    for (int i = 0; i < m; i++)
    {
        free(grid[i]);
    }
    free(grid);
}

//frees the 2d array grid
void free_distance(long long **grid, int m){
    for (int i = 0; i < m; i++)
    {
        free(grid[i]);
    }
    free(grid);
}

//free the heap
void free_heap(heap_node **heap, int size){
    for (int i = 0; i < size; i++){
        free(heap[i]);
    }
    free(heap);
}

void update_dist_in_heap(heap_node **heap, int idx, long long new_dist, int size){
    for(int i = 0; i < size; i++){
        if(heap[i]->idx == idx){
            heap[i]->dist = new_dist;
            break;
        }
    }
}

void update_prev_in_heap(heap_node **heap, int idx, int new_prev, int size){
    for(int i = 0; i < size; i++){
        if(heap[i]->idx == idx){
            heap[i]->prev = new_prev;
            break;
        }
    }
}

//checks if a location is in the heap
int check_q(heap_node **heap, short grid_idx, int q_size){
    for(int i = 0; i < q_size; i++){
        if (heap[i]->idx == grid_idx){
            return 1;
        }
    }
    return 0;
}

void print_distance_grid(long long **grid, short m, short n){
    for (int y = 0; y < m; y++){
        for (int x = 0; x < n; x++){
            printf("%lld ", grid[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_grid(short **grid, short m, short n){
    for (int y = 0; y < m; y++){
        for (int x = 0; x < n; x++){
            printf("%hd ", grid[y][x]);
        }
        printf("\n");
    }
    printf("\n");
}

void print_heap(heap_node **heap, int n){
    for (int i = 0; i < n; i++){
        printf("%hd ", heap[i]->idx);
    }
    printf("\n");
    
}

void print_array(short *weights, int size){
    for (int i = 0; i < size; i++){
        printf("%hd ", weights[i]);
    }
    printf("\n");
}

void print_heap_dist(heap_node **heap, int size){
    for(int i = 0; i < size; i++){
        printf("%lld ", heap[i]->dist);
    }
    printf("\n");
}

void print_heap_prev(heap_node **heap, int size){
    for(int i = 0; i < size; i++){
        printf("node:%hd prev: %d\n", heap[i]->idx, heap[i]->prev);
    }
    printf("\n");
}