#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gestion.h"      // Accès aux structures (Voiture, parking, nbVoitures)
#include "files_stats.h"

/**
 * Sauvegarde toutes les données (voitures sorties et présentes) dans le fichier texte.
 */
void sauvegarderDonnees() {
    FILE* fichier = fopen(FICHIER_DONNEES, "w");
    
    if (fichier == NULL) {
        printf("(!) Erreur de sauvegarde : Impossible d'ouvrir le fichier %s.\n", FICHIER_DONNEES);
        return;
    }
    
    // Écriture du nombre de voitures total
    fprintf(fichier, "%d\n", nbVoitures);
    
    // Format: PLAQUE H_IN M_IN H_OUT M_OUT PRIX
    for (int i = 0; i < nbVoitures; i++) {
        fprintf(fichier, "%s %d %d %d %d %.2f\n",
                parking[i].plaque,
                parking[i].heureEntree,
                parking[i].minuteEntree,
                parking[i].heureSortie,
                parking[i].minuteSortie,
                parking[i].montant);
    }
    
    fclose(fichier);
    printf(">> Sauvegarde effectuee.\n");
}

/**
 * Charge les données depuis le fichier texte au démarrage.
 */
void chargerDonnees() {
    FILE* fichier = fopen(FICHIER_DONNEES, "r");
    
    if (fichier == NULL) {
        // C'est normal si c'est le premier lancement
        return; 
    }
    
    // Lecture du nombre de voitures total
    if (fscanf(fichier, "%d", &nbVoitures) != 1) {
        nbVoitures = 0;
        fclose(fichier);
        return;
    }
    
    // Lecture des données de chaque voiture
    for (int i = 0; i < nbVoitures; i++) {
        if (fscanf(fichier, "%s %d %d %d %d %lf",
               parking[i].plaque,
               &parking[i].heureEntree,
               &parking[i].minuteEntree,
               &parking[i].heureSortie,
               &parking[i].minuteSortie,
               &parking[i].montant) != 6) 
        {
            // S'il y a une erreur de lecture, on s'arrête là
            nbVoitures = i; 
            break;
        }
    }
    
    fclose(fichier);
}

/**
 * Calcule et retourne le revenu total généré par toutes les sorties enregistrées.
 */
double calculerRevenuTotal() {
    double total = 0.0;
    for (int i = 0; i < nbVoitures; i++) {
        if (parking[i].heureSortie != -1) {
            total += parking[i].montant;
        }
    }
    return total;
}

/**
 * Réinitialise complètement les données du parking, en effaçant le fichier
 * et en vidant la mémoire. (Utilisé par l'option 7 du menu)
 */
void reinitialiserDonnees() {
    // 1. Suppression du fichier de sauvegarde sur le disque
    if (remove(FICHIER_DONNEES) == 0) {
        printf("[OK] Fichier de sauvegarde efface (%s).\n", FICHIER_DONNEES);
    } else {
        printf("[INFO] Fichier de sauvegarde non trouve ou erreur de suppression (ce n'est pas critique).\n");
    }

    // 2. Réinitialisation des données en mémoire
    nbVoitures = 0;
    // On met à zéro la mémoire pour s'assurer que l'état est propre
    memset(parking, 0, sizeof(Voiture) * MAX_VOITURES); 

    printf("[RESET] Memoire du parking videe. Le systeme redemarre a zero.\n");
}

/**
 * Affiche les statistiques du parking (nombre de voitures présentes et revenus).
 */
void afficherStatistiques() {
    int presents = 0;
    int sortis = 0;
    
    for(int i=0; i<nbVoitures; i++) {
        if(parking[i].heureSortie == -1) presents++;
        else sortis++;
    }

    printf("\n--- STATISTIQUES FINANCIERES ---\n");
    printf("Total Entrees/Sorties : %d\n", nbVoitures);
    printf("Voitures sorties      : %d\n", sortis);
    printf("Voitures presentes    : %d\n", presents);
    printf("Revenu Total Cumule   : %.2f EUR\n", calculerRevenuTotal());
    printf("------------------------------\n\n");
}