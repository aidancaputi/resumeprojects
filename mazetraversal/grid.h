#ifndef GRID_H
#define GRID_H

typedef struct HeapNode {
    short idx;
    long long dist;
    short x;
    short y;
    int prev;
} heap_node;

typedef struct PrevNode {
    int idx;
    struct PrevNode *prev;
} path_node;


short **make_grid(FILE *input, FILE *output1, short m, short n);
void free_grid(short **grid, int m);
short get_m(FILE *input);
short get_n(FILE *input);
void upward_heapify(heap_node **heap, int idx);
void fastest_paths(FILE *output2, short **grid, short m, short n, FILE *output3);
long long *dijkstra(short **grid, short *weights, short start, short m, short n, FILE *output3, path_node **fastest_path);
void downward_heapify(heap_node **heap, int i, int n);
int check_q(heap_node **heap, short grid_idx, int q_size);
void print_grid(short **grid, short m, short n);
void print_heap(heap_node **heap, int n);
heap_node *create_heap_node(short index, long long distance);
void print_array(short *weights, int size);
void free_heap(heap_node **heap, int size);
short extract_min(heap_node **heap, int size);
void update_dist_in_heap(heap_node **heap, int idx, long long new_dist, int size);
void print_heap_dist(heap_node **heap, int size);
void free_distance(long long **grid, int m);
void print_distance_grid(long long **grid, short m, short n);
void print_heap_prev(heap_node **heap, int size);
void update_prev_in_heap(heap_node **heap, int idx, int new_prev, int size);
void free_paths(int **paths, int len);
int find_in_heap(heap_node **heap, int size, int looking);
path_node * actual_path(heap_node **heap, short m, short n, short start, short end);
path_node * create_path_node(int index);
void reverse(path_node *temp, FILE *output3, short m, short n);
void free_path(path_node **path, int len);

#endif