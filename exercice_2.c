//EXERCICE 2 Romain Bruneau Thibault Eid 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// def de la structure   Produit
typedef struct {
    char nom[50];
    float prix;
    int quantite;
} Produit;

// on definit la fonction Departement
typedef struct {
    char nom[50];
    Produit* produits;
    int nombreProduits;
} Departement;

// fonction pour generer produit aleatoire
Produit genererProduitAleatoire() {
    Produit produit;
    char noms[5][20] = {"redbull", "nutella", "pates", "viande", "fruits"};
    strcpy(produit.nom, noms[rand() % 5]);
    produit.prix = (float)(rand() % 10 + 1);  // Prix entre 1 et 10
    produit.quantite = rand() % 100;          // Quantité entre 0 et 99
    return produit;
}

// fonction pour gerer les stock d'un departement
void gestionStock(Departement* departement) {
    // Simulation d'operations sur les stocks (ajout, vente, etc.)
    for (int a = 0; a < departement->nombreProduits; ++a) {
        departement->produits[a].quantite -= rand() % 20;  // Simulation de vente
    }
}

//fonction pour savegarder departements et produits dans un fichier
void sauvegarderDansFichier(Departement* departements, int nombreDepartements, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");

    if (fichier != NULL) {
        for (int a = 0; a< nombreDepartements; ++a) {
            fprintf(fichier, "%s\n", departements[a].nom);
            for (int b= 0; b< departements[a].nombreProduits; ++b) {
                fprintf(fichier, "%s %.2f %d\n", departements[a].produits[b].nom, departements[a].produits[b].prix, departements[a].produits[b].quantite);
            }
        }

        fclose(fichier);
    } else {
        perror("Erreur lors de l'ouverture du fichier");
    }
}

//FONCTION POUR CHARGER LES DEPARTEMNTS ET PRODUITS  
Departement* chargerDepuisFichier(int* nombreDepartements, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");

    if (fichier != NULL) {
        fscanf(fichier, "%d", nombreDepartements);

        Departement* departements = (Departement*)malloc(*nombreDepartements * sizeof(Departement));

        for (int a= 0; a < *nombreDepartements; ++a) {
            fscanf(fichier, "%s", departements[a].nom);
            fscanf(fichier, "%d", &departements[a].nombreProduits);

            departements[a].produits = (Produit*)malloc(departements[a].nombreProduits * sizeof(Produit));

            for (int b= 0; b< departements[a].nombreProduits; ++b) {
                fscanf(fichier, "%s %f %d", departements[a].produits[b].nom, &departements[a].produits[b].prix, &departements[a].produits[b].quantite);
            }
        }

        fclose(fichier);
        return departements;
    } else {
        perror("Erreur lors de l'ouverture du fichier");
        return NULL;
    }
}

//fonction pour liberer la memoire avce utilisation de l'allocution dynamique
void libererMemoire(Departement* departements, int nombreDepartements) {
    for (int a= 0; a< nombreDepartements; ++a) {
        free(departements[a].produits);
    }
    free(departements);
}

int main() {
    srand(time(NULL));

    // Création de trois départements
    int nombreDepartements = 3;
    Departement* departements = (Departement*)malloc(nombreDepartements * sizeof(Departement));

    for (int a= 0;  a< nombreDepartements; ++a) {
        sprintf(departements[a].nom, "Departement%d", a+1);
        departements[a].nombreProduits = 5;  // Nombre de produits par département
        departements[a].produits = (Produit*)malloc(departements[a].nombreProduits * sizeof(Produit));

        for (int b= 0; b< departements[a].nombreProduits; ++b) {
            departements[a].produits[b] = genererProduitAleatoire();
        }
    }

    //simuler les stocks
    for (int a= 0; a< nombreDepartements; ++a) {
        gestionStock(&departements[a]);
    }

    //SAUVEGARDE
    sauvegarderDansFichier(departements, nombreDepartements, "supermarche.txt");
    printf("Les informations sur le supermarche ont ete sauvegardees dans le fichier 'supermarche.txt'.\n");

   
    libererMemoire(departements, nombreDepartements);

    // Chargement à partir d'un fichier
    Departement* departementsCharge;
    int nombreDepartementsCharge;
    departementsCharge = chargerDepuisFichier(&nombreDepartementsCharge, "supermarche.txt");

    //Simulation du fonctionnement du supermarche aprrs le chargement
    for (int a= 0; a< nombreDepartementsCharge; ++a) {
        printf("%s\n", departementsCharge[a].nom);
        for (int b= 0; b< departementsCharge[a].nombreProduits; ++b) {
            printf("- %s: %.2f euros, stock: %d\n", departementsCharge[a].produits[b].nom, departementsCharge[a].produits[b].prix, departementsCharge[a].produits[b].quantite);
        }
    }

    //liberation de la memoire apres chargement
    libererMemoire(departementsCharge, nombreDepartementsCharge);

    return 0;
}
