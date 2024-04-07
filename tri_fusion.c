#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PHONE_LENGTH 15
#define MAX_NAME_LENGTH 50
#define MAX_LINE_LENGTH (MAX_PHONE_LENGTH + MAX_NAME_LENGTH * 2 + 3)

// Fonction pour fusionner deux sous-tableaux arr[l..m] et arr[m+1..r] de arr[]
void fusion(char arr[][MAX_LINE_LENGTH], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Création de tableaux temporaires
    char L[n1][MAX_LINE_LENGTH], R[n2][MAX_LINE_LENGTH];

    // Copie des données dans les tableaux temporaires L[] et R[]
    for (i = 0; i < n1; i++)
        strcpy(L[i], arr[l + i]);
    for (j = 0; j < n2; j++)
        strcpy(R[j], arr[m + 1 + j]);

    // Fusion des tableaux temporaires L[] et R[] dans arr[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (strcmp(L[i], R[j]) <= 0) {
            strcpy(arr[k], L[i]);
            i++;
        } else {
            strcpy(arr[k], R[j]);
            j++;
        }
        k++;
    }

    // Copie des éléments restants de L[], s'il y en a
    while (i < n1) {
        strcpy(arr[k], L[i]);
        i++;
        k++;
    }

    // Copie des éléments restants de R[], s'il y en a
    while (j < n2) {
        strcpy(arr[k], R[j]);
        j++;
        k++;
    }
}

// Fonction principale qui trie arr[l..r] en utilisant le tri par fusion
void tri_par_fusion(char arr[][MAX_LINE_LENGTH], int l, int r) {
    if (l < r) {
        // Trouver le point médian pour diviser le tableau en deux moitiés
        int m = l + (r - l) / 2;

        // Trier la première moitié
        tri_par_fusion(arr, l, m);
        // Trier la seconde moitié
        tri_par_fusion(arr, m + 1, r);

        // Fusionner les deux moitiés triées
        fusion(arr, l, m, r);
    }
}

int main() {
    clock_t start, end;
    double cpu_time_used;

    start = clock(); // Mesure du temps de départ

    FILE *file = fopen("liste_numeros.txt", "r+"); // Ouverture du fichier en mode lecture et écriture
    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n"); // Affichage d'une erreur si l'ouverture échoue
        return 1;
    }

    char lines[1000][MAX_LINE_LENGTH]; // Déclaration d'un tableau pour stocker les lignes du fichier
    int count = 0;
    char line[MAX_LINE_LENGTH];

    // Lecture des lignes du fichier tant qu'il reste des lignes à lire et que le nombre maximum de lignes n'est pas atteint
    while (fgets(line, MAX_LINE_LENGTH, file) != NULL && count < 1000) {
        strcpy(lines[count], line); // Copie de la ligne lue dans le tableau de lignes
        count++;
    }

    // Appel de la fonction de tri par fusion pour trier les lignes du tableau
    tri_par_fusion(lines, 0, count - 1);

    rewind(file); // Rembobinage du fichier au début

    // Écriture des lignes triées dans le fichier
    for (int i = 0; i < count; i++) {
        fputs(lines[i], file);
    }

    fclose(file); // Fermeture du fichier

    end = clock(); // Mesure du temps de fin

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC; // Calcul du temps écoulé

    printf("Temps écoulé pour le tri : %f secondes.\n", cpu_time_used); // Affichage du temps écoulé

    return 0;
}