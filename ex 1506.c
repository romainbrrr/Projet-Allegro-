#define TAILLE_NOM 15
#define TAILLE_FAMILLE 10
#define NB_DINOSAURES 20

typedef struct {
    char nom[TAILLE_NOM];
    char famille[TAILLE_FAMILLE];
    int date_disparition;
    char type;
} Dinosaure;

Dinosaure* creer() {
    Dinosaure* dino = (Dinosaure*)malloc(sizeof(Dinosaure));

    if (dino == NULL) {
        perror("Erreur d'allocation de mémoire pour le dinosaure");
        exit(EXIT_FAILURE);
    }

    printf("Nom du dinosaure : ");
    scanf("%s", dino->nom);

    printf("Famille du dinosaure : ");
    scanf("%s", dino->famille);

    printf("Date de disparition du dinosaure : ");
    scanf("%d", &dino->date_disparition);

    printf("Type du dinosaure (Carnivore 'C' / Herbivore 'H') : ");
    scanf(" %c", &dino->type);

    return dino;
}

void afficher(const Dinosaure* dino) {
    printf("Nom : %s\n", dino->nom);
    printf("Famille : %s\n", dino->famille);
    printf("Date de disparition : %d\n", dino->date_disparition);
    printf("Type : %c\n", dino->type);
    printf("\n");
}

void toutAfficher(Dinosaure* tableau[], int taille) {
    for (int i = 0; i < taille; i++) {
        afficher(tableau[i]);
    }
}

void rechercher(Dinosaure* tableau[], int taille, int date, char type) {
    printf("\nRésultats de la recherche :\n");
    for (int i = 0; i < taille; i++) {
        if (tableau[i]->date_disparition == date && tableau[i]->type == type) {
            afficher(tableau[i]);
        }
    }
}

int main() {
    Dinosaure* tableau[NB_DINOSAURES];

    for (int i = 0; i < NB_DINOSAURES; i++) {
        tableau[i] = creer();
    }

    printf("\nAffichage de tous les dinosaures :\n");
    toutAfficher(tableau, NB_DINOSAURES);

    int date_recherche;
    char type_recherche;

    printf("\nEntrez une date de recherche : ");
    scanf("%d", &date_recherche);

    printf("Entrez un type de dinosaure (Carnivore 'C' / Herbivore 'H') : ");
    scanf(" %c", &type_recherche);

    rechercher(tableau, NB_DINOSAURES, date_recherche, type_recherche);

    // Libération de la mémoire
    for (int i = 0; i < NB_DINOSAURES; i++) {
        free(tableau[i]);
    }

    return 0;
}