#include <allegro.h>
#include <math.h>
#include <stdbool.h>
#include "time.h"
#ifndef UNTITLED54_HEADER_H
#define UNTITLED54_HEADER_H
#define DISTANCE_MIN_RAMASSAGE 30
#define LARGEUR_ECRAN 800
#define HAUTEUR_ECRAN 600
#define VITESSE 5
#define NOM_MAX 20
#define MAX_OBJETS 10
#include <string.h>
BITMAP* page;
BITMAP* image_menu;
BITMAP* image1_menu;
BITMAP* image2_menu;
BITMAP* image3_menu;
BITMAP* image4_menu;
BITMAP *image_joueur1;
BITMAP *image_joueur2;
BITMAP *image_background;
void init();

typedef struct Personnage {
    int x, y; // Position
    char pseudo[NOM_MAX];
    BITMAP *image;

} Personnage;

typedef struct {
    int x, y;
    int posXInit, posYInit; // Position initiale de l'objet
    bool estTenu;
    int parJoueur;
    time_t lastTakenTime;
    int regenDelay; // Délai de régénération en secondes
} Objet;

typedef struct Poubelle {
    int x, y; // Position de la poubelle
    int largeur, hauteur; // Dimensions de la poubelle
} Poubelle;

bool collision_cercles(int x1, int y1, int r1, int x2, int y2, int r2);

Personnage joueur1, joueur2;

char pseudoJoueur1[1000];
char pseudoJoueur2[1000];


void jouer();
void demanderPseudo(char *pseudo, const char *message);
void pseudo();
void init_poubelle(Poubelle *p, int x, int y, int largeur, int hauteur);
void dessiner_poubelle(Poubelle *p, BITMAP *buffer);
bool est_pres_poubelle(int objX, int objY, Poubelle *p);
void dessiner_personnage(Personnage *p, BITMAP *buffer);
void dessiner_salade(Objet *o, Personnage *joueur1, Personnage *joueur2, BITMAP *buffer);
void dessiner_steak(Objet *o, Personnage *joueur1, Personnage *joueur2, BITMAP *buffer);
void deplacer_personnage(Personnage *p, int dx, int dy, Poubelle *pb);

#endif //UNTITLED54_HEADER_H
