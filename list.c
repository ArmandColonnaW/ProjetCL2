#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

// Créer une liste avec un nombre maximal de niveaux spécifié
t_d_list *create_list(int max_level) {
    // Vérifier si le nombre maximal de niveaux est valide
    if (max_level <= 0) {
        fprintf(stderr, "Nombre maximal de niveaux non valide.\n");
        exit(EXIT_FAILURE);
    }

    // Allouer de la mémoire pour la liste
    t_d_list *list = malloc(sizeof(t_d_list));

    // Vérifier l'allocation de mémoire pour la liste
    if (list == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la liste.\n");
        exit(EXIT_FAILURE);
    }

    // Allouer de la mémoire pour le tableau de pointeurs de tête
    list->head = malloc(max_level * sizeof(t_d_cell *));

    // Vérifier l'allocation de mémoire pour le tableau de pointeurs de tête
    if (list->head == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les pointeurs de tête.\n");
        free(list);
        exit(EXIT_FAILURE);
    }

    // Initialiser les pointeurs de tête à NULL
    for (int i = 0; i < max_level; i++) {
        list->head[i] = NULL;
    }

    // Enregistrer le nombre maximal de niveaux
    list->max_level = max_level;

    return list;
}

// Insérer une cellule au niveau spécifié en tête de la liste
void insert_list(t_d_list *list, t_d_cell *cell) {
    // Vérifier la validité de la cellule
    if (cell == NULL || cell->max_level > list->max_level) {
        fprintf(stderr, "Insertion de cellule invalide.\n");
        return;
    }

    // Mettre à jour les pointeurs de la cellule pour pointer vers les cellules actuellement en tête
    for (int i = 0; i < cell->max_level && i < list->max_level; i++) {
        cell->next[i] = list->head[i];
    }

    // Mettre à jour les pointeurs de tête pour pointer vers la nouvelle cellule
    for (int i = cell->max_level - 1; i >= 0 && i < list->max_level; i--) {
        list->head[i] = cell;
    }
}

// Insérer une cellule triée dans la liste
void insert_cell(t_d_list *list, t_d_cell *cell) {
    // Vérifier la validité de la cellule
    if (cell == NULL || cell->max_level > list->max_level) {
        fprintf(stderr, "Insertion de cellule invalide.\n");
        return;
    }

    int level;
    t_d_cell *current;

    // Parcourir les niveaux de la cellule
    for (level = 0; level < cell->max_level; level++) {
        // Si la liste est vide au niveau actuel, insérer la cellule
        if (list->head[level] == NULL) {
            list->head[level] = cell;
        } else if (cell->value < list->head[level]->value) {
            // Si la valeur de la cellule est inférieure à la tête actuelle, insérer la cellule en tant que nouvelle tête
            t_d_cell *temp = list->head[level];
            list->head[level] = cell;
            cell->next[level] = temp;
        } else {
            // Trouver la position correcte pour insérer la cellule
            current = list->head[level];
            while (current->next[level] != NULL && current->next[level]->value < cell->value) {
                current = current->next[level];
            }
            cell->next[level] = current->next[level];
            current->next[level] = cell;
        }
    }
}

// Afficher une ligne de la liste pour un niveau donné
void display_one_level(t_d_list *list, int level) {
    t_d_cell *cell = list->head[level];
    printf("[list head_%d @-]", level);

    // Afficher "NULL" si la liste est vide
    if (cell == NULL) {
        printf("NULL\n");
        return;
    }

    int old = cell->value;
    int cpt = 0;

    // Si la tête du niveau 0 est différente de la tête du niveau actuel, ajuster l'affichage
    if (list->head[0]->value != list->head[level]->value) {
        t_d_cell *cell0 = list->head[0];
        while (cell0 != NULL) {
            if (cell0->value < cell->value) {
                cpt++;
            }
            cell0 = cell0->next[0];
        }

        for (int i = 0; i < cpt; i++) {
            printf("-----------");
        }
    }

    // Parcourir la liste pour afficher les cellules du niveau actuel
    while (cell != NULL) {
        t_d_cell *cell0 = list->head[0];
        cpt = 0;

        while (cell0 != NULL) {
            if (cell0->value > old && cell0->value < cell->value) {
                cpt++;
            }
            cell0 = cell0->next[0];
        }

        for (int i = 0; i < cpt; i++) {
            printf("-----------");
        }

        // Afficher la valeur de la cellule
        printf("-->[%3d|@-]", cell->value);
        old = cell->value;
        cell = cell->next[level];
    }

    cpt = 0;
    int last0;
    t_d_cell *cell0 = list->head[0];
    while (cell0 != NULL) {
        last0 = cell0->value;
        cell0 = cell0->next[0];
    }

    // Si la dernière valeur du niveau 0 n'est pas égale à la dernière valeur du niveau actuel, ajuster l'affichage
    if (last0 != old) {
        cell0 = list->head[0];
        while (cell0 != NULL) {
            if (cell0->value > old) {
                cpt++;
            }
            cell0 = cell0->next[0];
        }

        for (int i = 0; i < cpt; i++) {
            printf("-----------");
        }
    }

    printf("-->NULL\n");
}

// Afficher tous les niveaux de la liste
void display_all_levels(t_d_list *list) {
    for (int i = 0; i < list->max_level; i++) {
        display_one_level(list, i);
    }
}

// Recherche d'une valeur dans une liste au niveau spécifié
int classical_search(t_d_list *list, int value, int level) {
    t_d_cell *current = list->head[level];

    // Parcourir la liste au niveau spécifié
    while (current != NULL) {
        // Si la valeur est trouvée, retourner 0 (valeur trouvée)
        if (current->value == value) {
            return 0;
        } else {
            // Passer à la cellule suivante
            current = current->next[level];
        }
    }

    // Retourner 1 (valeur non trouvée)
    return 1;
}

// Recherche d'une valeur dans une liste de manière experte
int expert_search(t_d_list *list, t_d_cell *first, t_d_cell *last, int value, int level) {
    t_d_cell *current = first;
    t_d_cell *prec = first;

    // Parcourir la liste de manière experte
    while (current != last && current != NULL) {
        // Si la valeur est plus grande que la valeur recherchée, effectuer une recherche récursive dans le niveau inférieur
        if (current->value > value) {
            if (level == 0) {
                return 1;
            } else {
                return expert_search(list, prec, current, value, level - 1);
            }
        } else if (current->value < value) {
            // Si la valeur est plus petite, mettre à jour les pointeurs pour passer à la cellule suivante
            prec = current;
            current = current->next[level];
        } else {
            // Si la valeur est trouvée, retourner 0 (valeur trouvée)
            return 0;
        }
    }

    // Si la recherche n'a pas abouti au niveau actuel, effectuer une recherche récursive dans le niveau inférieur
    return (level == 0) ? 1 : expert_search(list, prec, NULL, value, level - 1);
}