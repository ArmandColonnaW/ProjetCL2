#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H

#include "cell.h"

// structure à n niveau pour un tableau de n ligne avec une valeur max et un
// tableau de pointeur
typedef struct s_d_list {
    t_d_cell **head;
    int max_level;
} t_d_list;

t_d_list *create_list(int);
void insert_list(t_d_list *, t_d_cell *);
void insert_cell(t_d_list *, t_d_cell *);
void display_one_level(t_d_list *, int);
void display_all_levels(t_d_list *);
int classical_search(t_d_list *, int, int);
int expert_search(t_d_list *, t_d_cell *, t_d_cell *, int, int);

#endif