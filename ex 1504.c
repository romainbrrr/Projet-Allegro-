int lire_taille_depuis_fichier(const char* nom_fichier) {
    FILE* fichier = fopen(nom_fichier, "r");
    if (fichier == NULL) {
        perror("Erreur à l'ouverture du fichier");
        exit(EXIT_FAILURE);
    }

    int taille;
    fscanf(fichier, "%d", &taille);

    fclose(fichier);

    return taille;
}

void ecrire_multiples(const char* nom_fichier_mult3, const char* nom_fichier_autres, int* tableau, int taille) {
    FILE* fichier_mult3 = fopen(nom_fichier_mult3, "w");
    FILE* fichier_autres = fopen(nom_fichier_autres, "w");

    if (fichier_mult3 == NULL || fichier_autres == NULL) {
        perror("Erreur à l'ouverture des fichiers");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < taille; i++) {
        if (tableau[i] % 3 == 0) {
            fprintf(fichier_mult3, "%d\n", tableau[i]);
        } else {
            fprintf(fichier_autres, "%d\n", tableau[i]);
        }
    }

    fclose(fichier_mult3);
    fclose(fichier_autres);
}

int main() {
    int taille = lire_taille_depuis_fichier("donnee.txt");

    int* mon_tableau = (int*)malloc(taille * sizeof(int));

    srand(time(NULL));
    for (int i = 0; i < taille; i++) {
        mon_tableau[i] = rand() % 176 - 25;
    }

    FILE* fichier_resultat = fopen("resultat.txt", "w");
    if (fichier_resultat == NULL) {
        perror("Erreur à l'ouverture du fichier resultat.txt");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < taille; i++) {
        fprintf(fichier_resultat, "%d\n", mon_tableau[i]);
    }

    fclose(fichier_resultat);

    ecrire_multiples("mult3.txt", "autres.txt", mon_tableau, taille);

    free(mon_tableau);

    return 0;
}