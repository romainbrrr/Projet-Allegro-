#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_PHONE_LENGTH 15
#define MAX_NAME_LENGTH 50
#define MAX_LINE_LENGTH (MAX_PHONE_LENGTH + MAX_NAME_LENGTH * 2 + 3)

// Fonction pour trier un tableau de chaînes de caractères par insertion
void tri_par_insertion(char arr[][MAX_LINE_LENGTH], int n) {
    int i, j;
    char key[MAX_LINE_LENGTH];
    for (i = 1; i < n; i++) {
        strcpy(key, arr[i]);
        j = i - 1;

        // Déplacement des éléments du tableau arr[0..i-1], qui sont plus grands que la clé, d'une position vers le haut
        while (j >= 0 && strcmp(arr[j], key) > 0) {
            strcpy(arr[j + 1], arr[j]);
            j = j - 1;
        }
        strcpy(arr[j + 1], key);
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

    // Appel de la fonction de tri par insertion pour trier les lignes du tableau
    tri_par_insertion(lines, count);

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
