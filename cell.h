#ifndef UNTITLED_CELL_H
#define UNTITLED_CELL_H

// on a une valeur et un tableau de pointeur sur la ou les cellule(s) suivante
typedef struct s_d_cell {
    int value;
    int max_level;
    struct s_d_cell **next;
} t_d_cell;

t_d_cell *create_cell(int, int);
#endif // UNTITLED_CELL_H