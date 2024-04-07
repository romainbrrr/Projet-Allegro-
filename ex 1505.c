typedef struct {
    int lignes;
    int colonnes;
    int** data;
} Matrice;

Matrice allouer_matrice() {
    Matrice matrice;

    printf("Entrez le nombre de lignes de la matrice : ");
    scanf("%d", &matrice.lignes);
    printf("Entrez le nombre de colonnes de la matrice : ");
    scanf("%d", &matrice.colonnes);

    matrice.data = (int**)malloc(matrice.lignes * sizeof(int*));
    if (matrice.data == NULL) {
        perror("Erreur d'allocation pour les lignes de la matrice");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < matrice.lignes; i++) {
        matrice.data[i] = (int*)malloc(matrice.colonnes * sizeof(int));
        if (matrice.data[i] == NULL) {
            perror("Erreur d'allocation pour les colonnes de la matrice");
            exit(EXIT_FAILURE);
        }
    }

    return matrice;
}

void remplir_matrice(Matrice* matrice) {
    srand(time(NULL));
    for (int i = 0; i < matrice->lignes; i++) {
        for (int j = 0; j < matrice->colonnes; j++) {
            matrice->data[i][j] = rand() % 256;
        }
    }
}

void afficher_matrice(const Matrice* matrice) {
    printf("Matrice :\n");
    for (int i = 0; i < matrice->lignes; i++) {
        for (int j = 0; j < matrice->colonnes; j++) {
            printf("%4d ", matrice->data[i][j]);
        }
        printf("\n");
    }
}

void liberer_matrice(Matrice* matrice) {
    for (int i = 0; i < matrice->lignes; i++) {
        free(matrice->data[i]);
    }
    free(matrice->data);
}

int main() {
    Matrice ma_matrice = allouer_matrice();

    remplir_matrice(&ma_matrice);

    afficher_matrice(&ma_matrice);

    liberer_matrice(&ma_matrice);

    return 0;
}