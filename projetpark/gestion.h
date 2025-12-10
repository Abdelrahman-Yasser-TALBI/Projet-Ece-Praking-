#ifndef GESTION_H
#define GESTION_H

#define MAX_VOITURES 100
#define TAILLE_PLAQUE 20

// Tarif : 3.00 EUR par heure
#define PRIX_PAR_MINUTE (3.0 / 60.0)

typedef struct {
    char plaque[TAILLE_PLAQUE];
    int heureEntree;
    int minuteEntree;
    int heureSortie;
    int minuteSortie;
    double montant;
} Voiture;

// Variables partagées (accessibles par LAARIF et TAMDA)
extern Voiture parking[MAX_VOITURES];
extern int nbVoitures;

// Fonctions TALBI
int ajouterVoiture(const char* plaque, int h, int m);
int enregistrerSortie(const char* plaque, int h, int m);
void afficherPresents();
int verifierExistence(const char* plaque);

#endif