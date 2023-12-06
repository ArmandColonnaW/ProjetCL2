#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include "cell.h"
#include "list.h"
#include "timer.h"
int main(void) {
/* partie 1*/
/*
    t_d_list *list = create_list(5);
    display_all_levels(list);
    t_d_cell *cell1 = create_cell(56, 3);
    t_d_cell *cell2 = create_cell(31, 2);
    t_d_cell *cell3 = create_cell(32, 5);
    t_d_cell *cell4 = create_cell(18, 4);
    t_d_cell *cell5 = create_cell(25, 1);
    t_d_cell *cell6 = create_cell(59, 1);
    t_d_cell *cell7 = create_cell(58, 5);
    t_d_cell *cell8 = create_cell(91, 3);
    insert_cell(list, cell1);
    insert_cell(list, cell2);
    insert_cell(list, cell3);
    insert_cell(list, cell4);
    insert_cell(list, cell5);
    insert_cell(list, cell6);
    insert_cell(list, cell7);
    insert_cell(list, cell8);
    printf(".........................\n");
    display_all_levels(list);
    return 0;
    */
/* partie 2*/
    srand((unsigned int)time(NULL)); // Initialisation du générateur de nombres aléatoires

    time_t t;
    time(&t);
    srand(t);

    int n = rand() % 12 + 1;
    int size = pow(2, n) - 1;

    int tab[size];
    for (int i = 0; i < size; i++) {
        tab[i] = 0;
    }

    int a = 1;
    for (int k = 0; k < size; k++) {
        printf("%d", tab[k]);
    }
    printf("\n");

    for (int i = 1; i < n; i++) {
        a = a * 2;
        for (int j = a - 1; j < size; j += a) {
            tab[j]++;
        }
        for (int k = 0; k < size; k++) {
            printf("%d", tab[k]);
        }
        printf("\n");
    }

    t_d_list *list = create_list(n);

    for (int i = 0; i < size; i++) {
        t_d_cell *cell = create_cell(i + 1, tab[i] + 1);
        insert_cell(list, cell);
    }

    display_all_levels(list);

    FILE *log_file = fopen("log.txt", "a");
    char format[] = "%d\t%s\t%s\n";
    int level = n;
    char time_lvl0[15];
    char time_all_levels[15];

    for (int j = 2; j < 3; j++) {
        startTimer();
        clock_t debut = clock();
        for (int i = 0; i < pow(10, j + 3); i++) {
            classical_search(list, rand() % size + 1, 0);
        }
        stopTimer();
        clock_t fin = clock();
        displayTime();
        sprintf(time_lvl0, "%.6f", ((double)(fin - debut)) / CLOCKS_PER_SEC * 1000);

        startTimer();
        debut = clock();
        for (int i = 0; i < pow(10, j + 3); i++) {
            expert_search(list, list->head[n - 1], NULL, rand() % size + 1, n - 1);
        }
        stopTimer();
        fin = clock();
        displayTime();
        sprintf(time_all_levels, "%.6f", ((double)(fin - debut)) / CLOCKS_PER_SEC * 1000);
        fprintf(log_file, format, level, time_lvl0, time_all_levels);
    }

    fclose(log_file);
    return 0;
}