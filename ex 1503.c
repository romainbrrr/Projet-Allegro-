float* saisir_tableau(int* taille) {
    printf("Donner la taille du tableau : ");
    scanf("%d", taille);

    float* tableau = (float*)malloc(*taille * sizeof(float));

    printf("Donner les éléments du tableau :\n");
    for (int i = 0; i < *taille; i++) {
        printf("Élément %d : ", i + 1);
        scanf("%f", &tableau[i]);
    }

    return tableau;
}

void afficher_tableau(float* tableau, int taille) {
    printf("Contenu du tableau :\n");
    for (int i = 0; i < taille; i++) {
        printf("%.2f ", tableau[i]);
    }
    printf("\n");
}

void trier_tableau(float* tableau, int taille) {
    for (int i = 0; i < taille - 1; i++) {
        for (int j = i + 1; j < taille; j++) {
            if (tableau[i] > tableau[j]) {
                float temp = tableau[i];
                tableau[i] = tableau[j];
                tableau[j] = temp;
            }
        }
    }
}

int main() {
    int taille;
    float* mon_tableau;

    mon_tableau = saisir_tableau(&taille);

    afficher_tableau(mon_tableau, taille);

    trier_tableau(mon_tableau, taille);

    printf("Tableau trié :\n");
    afficher_tableau(mon_tableau, taille);

    free(mon_tableau);

    return 0;
}