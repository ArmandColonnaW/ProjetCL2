#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cell.h"

// Fonction pour créer une nouvelle cellule
t_d_cell *create_cell(int value, int n_levels) {
    // Allocation de mémoire pour la cellule
    t_d_cell *cell = malloc(sizeof(t_d_cell));

    // Vérification de l'allocation de mémoire
    if (cell == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la cellule.\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation des champs de la cellule
    cell->value = value;
    cell->max_level = n_levels;

    // Allocation de mémoire pour le tableau de pointeurs suivants
    cell->next = malloc(n_levels * sizeof(t_d_cell *));

    // Vérification de l'allocation de mémoire
    if (cell->next == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les pointeurs suivants.\n");

        // Libération de la mémoire allouée pour la cellule
        free(cell);
        exit(EXIT_FAILURE);
    }

    // Initialisation des pointeurs suivants à NULL
    for (int i = 0; i < n_levels; i++) {
        cell->next[i] = NULL;
    }

    // Retourne un pointeur vers la nouvelle cellule initialisée
    return cell;
}