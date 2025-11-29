#include <stdio.h>
#include <stdlib.h>
#include "menu_logique.h"
#include "gestion_voitures.h"
#include "statistiques.h"

// Déclaration externe de clearScreen (définie dans main.c)
extern void clearScreen(); 

/**
 * Affiche le menu principal
 */
void afficherMenu() {
    printf("\n");
    printf("========================================\n");
    printf("|     PARKING INTELLIGENT v1.0         |\n");
    printf("========================================\n");
    printf("\n");
    printf("   1. Enregistrer une entree\n");
    printf("   2. Enregistrer une sortie\n");
    printf("   3. Voir les voitures presentes\n");
    printf("   4. Afficher l'historique complet\n");
    printf("   5. Afficher les statistiques\n");
    printf("   6. Sauvegarder et quitter\n");
    printf("\n");
    printf("   Votre choix : ");
}

/**
 * Lit et valide le choix de l'utilisateur
 */
int lireChoix() {
    int choix;
    if (scanf("%d", &choix) != 1) {
        // Nettoyage du buffer en cas d'entree invalide
        while (getchar() != '\n');
        return -1;
    }
    // Nettoyage du buffer
    while (getchar() != '\n');
    return choix;
}

/**
 * Gere l'entree d'une nouvelle voiture
 */
void traiterEntree() {
    char plaque[TAILLE_PLAQUE];
    int heure;
    
    printf("\n-----------------------------\n");
    printf("|   ENREGISTREMENT ENTREE     |\n");
    printf("-----------------------------\n\n");
    
    printf("Plaque d immatriculation : ");
    scanf("%s", plaque);
    
    printf("Heure d entree (0-23) : ");
    if (scanf("%d", &heure) != 1) {
        printf("x Entree invalide !\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    ajouterVoiture(plaque, heure);
}

/**
 * Gere la sortie d'une voiture
 */
void traiterSortie() {
    char plaque[TAILLE_PLAQUE];
    int heure;
    
    printf("\n-----------------------------\n");
    printf("|   ENREGISTREMENT SORTIE     |\n");
    printf("-----------------------------\n\n");
    
    printf("Plaque d immatriculation : ");
    scanf("%s", plaque);
    
    printf("Heure de sortie (0-23) : ");
    if (scanf("%d", &heure) != 1) {
        printf("x Entree invalide !\n");
        while (getchar() != '\n');
        return;
    }
    while (getchar() != '\n');
    
    enregistrerSortie(plaque, heure);
}

/**
 * Affiche l'historique complet des tickets
 */
void afficherHistorique() {
    printf("\n===============================================================\n");
    printf("|                    HISTORIQUE COMPLET                       |\n");
    printf("===============================================================\n\n");
    
    if (nbVoitures == 0) {
        printf("   Aucun ticket enregistre.\n\n");
        return;
    }
    
    printf("----------+--------+--------+---------+----------\n");
    printf("| Plaque   | Entree | Sortie | Duree   | Montant |\n");
    printf("----------+--------+--------+---------+----------\n");
    
    for (int i = 0; i < nbVoitures; i++) {
        printf("| %-8s |   %2dh   |", 
                parking[i].plaque, 
                parking[i].heureEntree);
        
        if (parking[i].heureSortie == -1) {
            printf("   --     |   --    |   --      |\n");
        } else {
            int duree = parking[i].heureSortie - parking[i].heureEntree;
            if (duree < 0) duree += 24;
            
            printf("   %2dh   |   %2dh    |   %.2f e  |\n",
                    parking[i].heureSortie,
                    duree,
                    parking[i].montant);
        }
    }
    
    printf("----------+--------+--------+---------+----------\n\n");
}

/**
 * Boucle principale du menu
 */
void executerMenu() {
    int choix;
    int continuer = 1;
    
    // Chargement des donnees au demarrage
    chargerDonnees();
    
    while (continuer) {
        
        // 1. EFFACE L'ÉCRAN AVANT D'AFFICHER LE MENU
        clearScreen(); 
        
        afficherMenu();
        choix = lireChoix();
        
        // 2. EFFACE L'ÉCRAN APRES AVOIR REÇU LE CHOIX
        clearScreen();
        
        switch (choix) {
            case 1:
                traiterEntree();
                break;
            case 2:
                traiterSortie();
                break;
            case 3:
                afficherVoituresPresentes();
                break;
            case 4:
                afficherHistorique();
                break;
            case 5:
                afficherStatistiques();
                break;
            case 6:
                sauvegarderDonnees();
                printf("\na Donnees sauvegardees. Au revoir !\n\n");
                continuer = 0;
                break;
            default:
                printf("\nx Choix invalide ! Veuillez choisir entre 1 et 6.\n");
        }
        
        if (continuer) {
            printf("\nAppuyez sur ENTREE pour continuer...");
            getchar(); // Met en pause le programme
        }
    }
}