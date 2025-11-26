#include <stdio.h>
#include <string.h>
#include "gestion_voitures.h"

// Variables globales
Voiture parking[MAX_VOITURES];
int nbVoitures = 0;

/**
 * Vérifie si une voiture existe déjà dans le parking (non sortie)
 * Retourne 1 si existe, 0 sinon
 */
int verifierExistence(const char* plaque) {
    for (int i = 0; i < nbVoitures; i++) {
        if (strcmp(parking[i].plaque, plaque) == 0 && parking[i].heureSortie == -1) {
            return 1;
        }
    }
    return 0;
}

/**
 * Recherche une voiture par sa plaque
 * Retourne l'index si trouvée, -1 sinon
 */
int rechercherVoiture(const char* plaque) {
    for (int i = 0; i < nbVoitures; i++) {
        if (strcmp(parking[i].plaque, plaque) == 0 && parking[i].heureSortie == -1) {
            return i;
        }
    }
    return -1;
}

/**
 * Ajoute une nouvelle voiture dans le parking
 * Retourne 1 si succès, 0 si échec
 */
int ajouterVoiture(const char* plaque, int heureEntree) {
    // Vérification de la capacité
    if (nbVoitures >= MAX_VOITURES) {
        printf("❌ Parking complet !\n");
        return 0;
    }
    
    // Vérification si la voiture est déjà présente
    if (verifierExistence(plaque)) {
        printf("❌ Cette voiture est déjà dans le parking !\n");
        return 0;
    }
    
    // Validation de l'heure
    if (heureEntree < 0 || heureEntree > 23) {
        printf("❌ Heure invalide (doit être entre 0 et 23) !\n");
        return 0;
    }
    
    // Ajout de la voiture
    strcpy(parking[nbVoitures].plaque, plaque);
    parking[nbVoitures].heureEntree = heureEntree;
    parking[nbVoitures].heureSortie = -1;
    parking[nbVoitures].montant = 0.0;
    nbVoitures++;
    
    printf("✅ Voiture %s enregistrée à %dh\n", plaque, heureEntree);
    return 1;
}

/**
 * Enregistre la sortie d'une voiture et calcule le montant
 * Retourne 1 si succès, 0 si échec
 */
int enregistrerSortie(const char* plaque, int heureSortie) {
    int index = rechercherVoiture(plaque);
    
    if (index == -1) {
        printf("❌ Voiture non trouvée dans le parking !\n");
        return 0;
    }
    
    // Validation de l'heure
    if (heureSortie < 0 || heureSortie > 23) {
        printf("❌ Heure invalide (doit être entre 0 et 23) !\n");
        return 0;
    }
    
    // Calcul de la durée
    int duree = heureSortie - parking[index].heureEntree;
    if (duree < 0) {
        duree += 24;  // Gestion du passage à minuit
    }
    
    // Calcul du montant (2€ par heure)
    parking[index].heureSortie = heureSortie;
    parking[index].montant = duree * 2.0;
    
    printf("\n═══════════════════════════════\n");
    printf("       TICKET DE SORTIE\n");
    printf("═══════════════════════════════\n");
    printf("Plaque      : %s\n", parking[index].plaque);
    printf("Entrée      : %dh\n", parking[index].heureEntree);
    printf("Sortie      : %dh\n", parking[index].heureSortie);
    printf("Durée       : %d heure(s)\n", duree);
    printf("Montant     : %.2f €\n", parking[index].montant);
    printf("═══════════════════════════════\n\n");
    
    return 1;
}

/**
 * Affiche toutes les voitures actuellement présentes
 */
void afficherVoituresPresentes() {
    int compteur = 0;
    
    printf("\n╔═══════════════════════════════════╗\n");
    printf("║   VOITURES DANS LE PARKING        ║\n");
    printf("╚═══════════════════════════════════╝\n\n");
    
    for (int i = 0; i < nbVoitures; i++) {
        if (parking[i].heureSortie == -1) {
            printf("🚗 Plaque: %-10s | Entrée: %2dh\n", 
                   parking[i].plaque, 
                   parking[i].heureEntree);
            compteur++;
        }
    }
    
    if (compteur == 0) {
        printf("   Aucune voiture dans le parking.\n");
    }
    
    printf("\n   Total: %d voiture(s) présente(s)\n\n", compteur);
}
