#include <stdio.h>
#include <string.h>
#include "gestion.h"

// Définition réelle des variables
Voiture parking[MAX_VOITURES];
int nbVoitures = 0;

int verifierExistence(const char* plaque) {
    for (int i = 0; i < nbVoitures; i++) {
        if (strcmp(parking[i].plaque, plaque) == 0 && parking[i].heureSortie == -1) {
            return 1;
        }
    }
    return 0;
}

int rechercherVoiture(const char* plaque) {
    for (int i = 0; i < nbVoitures; i++) {
        if (strcmp(parking[i].plaque, plaque) == 0 && parking[i].heureSortie == -1) {
            return i;
        }
    }
    return -1;
}

int ajouterVoiture(const char* plaque, int h, int m) {
    if (nbVoitures >= MAX_VOITURES) {
        printf("(!) Parking complet.\n");
        return 0;
    }
    if (verifierExistence(plaque)) {
        printf("(!) Voiture deja presente.\n");
        return 0;
    }
    if (h < 0 || h > 23 || m < 0 || m > 59) return 0;

    strcpy(parking[nbVoitures].plaque, plaque);
    parking[nbVoitures].heureEntree = h;
    parking[nbVoitures].minuteEntree = m;
    parking[nbVoitures].heureSortie = -1;
    parking[nbVoitures].minuteSortie = -1;
    parking[nbVoitures].montant = 0.0;
    
    nbVoitures++;
    printf("[OK] Voiture %s ajoutee a %02dh%02d.\n", plaque, h, m);
    return 1;
}

int enregistrerSortie(const char* plaque, int h, int m) {
    int index = rechercherVoiture(plaque);
    if (index == -1 || h < 0 || h > 23 || m < 0 || m > 59) return 0;

    int debut = parking[index].heureEntree * 60 + parking[index].minuteEntree;
    int fin = h * 60 + m;
    int duree = fin - debut;
    if (duree < 0) duree += 24 * 60; 

    parking[index].heureSortie = h;
    parking[index].minuteSortie = m;
    parking[index].montant = (double)duree * PRIX_PAR_MINUTE;

    printf("\n=== TICKET SORTIE ===\n");
    printf("Plaque : %s\n", plaque);
    printf("Duree  : %dh %dmin\n", duree/60, duree%60);
    printf("PRIX   : %.2f EUR\n", parking[index].montant);
    printf("=====================\n");
    return 1;
}

void afficherPresents() {
    printf("\n--- VOITURES GAREES ---\n");
    int count = 0;
    for(int i=0; i<nbVoitures; i++) {
        if(parking[i].heureSortie == -1) {
            printf("- %s (Entree: %02dh%02d)\n", 
                   parking[i].plaque, parking[i].heureEntree, parking[i].minuteEntree);
            count++;
        }
    }
    if(count == 0) printf("Aucune voiture.\n");
    printf("\n");
}