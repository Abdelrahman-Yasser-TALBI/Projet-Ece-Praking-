#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "gestion.h"      // Appelle Talbi pour les actions
#include "files_stats.h"  // Appelle Laarif pour save/stats

// --- FONCTIONS UTILITAIRES ---

void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseConsole() {
    printf("\nAppuyez sur [Entree] pour continuer...");
    // Vider le buffer
    while(getchar() != '\n'); 
    // Attendre la touche entrée (elle est consommée ici)
    getchar(); 
}

void viderBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// --- AFFICHAGE ---

void afficherHeader() {
    clearScreen();
    printf("==================================================\n");
    printf("|           P A R K I N G   M A N A G E R        |\n");
    printf("==================================================\n");
    
    int presents = 0;
    // Utiliser la boucle de comptage ici est peu efficace, mieux vaut la faire une seule fois.
    // Pour simplifier et éviter de changer gestion.c, on compte directement ici.
    for(int i=0; i<nbVoitures; i++) { 
        if(parking[i].heureSortie == -1) presents++;
    }
    
    printf("| Places Occupees : %03d / %03d                    |\n", presents, MAX_VOITURES);
    printf("| Tarif Actuel    : %.2f EUR / Heure             |\n", (PRIX_PAR_MINUTE * 60));
    printf("==================================================\n");
}

void afficherHistorique() {
    printf("\n--- HISTORIQUE DES TICKETS ---\n");
    printf("PLAQUE          | ENTREE  | SORTIE  | MONTANT\n");
    printf("----------------+---------+---------+---------\n");
    
    int count = 0;
    for(int i = 0; i < nbVoitures; i++) {
        printf("%-15s | %02dh%02d   | ", parking[i].plaque, parking[i].heureEntree, parking[i].minuteEntree);
        
        if(parking[i].heureSortie == -1) 
            printf("--:--   | En cours\n");
        else 
            printf("%02dh%02d   | %.2f e\n", parking[i].heureSortie, parking[i].minuteSortie, parking[i].montant);
        count++;
    }
    if (count == 0) printf("Aucun historique disponible.\n");
    printf("\n");
}

// --- LOGIQUE DU MENU ---

void executerMenu() {
    int choix = 0;
    char plaque[TAILLE_PLAQUE];
    int h, m;

    // Chargement automatique au démarrage (Laarif)
    chargerDonnees(); 

    while (choix != 6) {
        afficherHeader();
        
        printf("\n[ GESTION ]\n");
        printf("  1. Enregistrer une Entree\n");
        printf("  2. Enregistrer une Sortie\n");
        
        printf("\n[ INFORMATIONS ]\n");
        printf("  3. Voir les vehicules presents\n");
        printf("  4. Afficher l'historique complet\n");
        printf("  5. Voir les statistiques financieres\n");
        
        printf("\n[ SYSTEME ]\n");
        printf("  6. Sauvegarder et Quitter\n");
        printf("  7. Reinitialiser la Memoire\n"); // NOUVELLE OPTION
        
        printf("\n>> Votre choix : ");
        
        if (scanf("%d", &choix) != 1) {
            viderBuffer();
            choix = 0;
            continue; 
        }

        printf("\n--------------------------------------------------\n");
        viderBuffer(); // Vider le buffer après le choix pour éviter les problèmes de pause

        switch(choix) {
            case 1: 
                printf(">> Nouvelle Entree\n");
                printf("   Plaque d'immatriculation : "); 
                scanf("%s", plaque);
                printf("   Heure d'arrivee (HH MM)  : ");
                if(scanf("%d %d", &h, &m) == 2) {
                    if(!ajouterVoiture(plaque, h, m)) {
                        printf("(!) Echec de l'ajout (Plaque ou heure invalide).\n");
                    }
                } else {
                    printf("(!) Erreur de format d'heure.\n");
                }
                pauseConsole();
                break;

            case 2: 
                printf(">> Enregistrement Sortie\n");
                printf("   Plaque du vehicule       : "); 
                scanf("%s", plaque);
                printf("   Heure de depart (HH MM)  : ");
                if(scanf("%d %d", &h, &m) == 2) {
                    if(!enregistrerSortie(plaque, h, m)) {
                        printf("(!) Echec de la sortie (Plaque introuvable ou Heure invalide).\n");
                    }
                } else {
                    printf("(!) Erreur de format d'heure.\n");
                }
                pauseConsole();
                break;

            case 3: 
                afficherPresents(); 
                pauseConsole();
                break;

            case 4: 
                afficherHistorique(); 
                pauseConsole();
                break;

            case 5: 
                afficherStatistiques(); 
                pauseConsole();
                break;

            case 6: 
                printf("Sauvegarde en cours...\n");
                sauvegarderDonnees();
                printf("Fermeture du programme. A bientot !\n");
                break;
                
            case 7: // NOUVEAU : Reset Memoire
                printf("ATTENTION : Cette action va effacer TOUTES les donnees.\n");
                printf("Confirmez-vous la reinitialisation complete ? (O/N) : ");
                char confirmation;
                if (scanf(" %c", &confirmation) == 1 && (confirmation == 'O' || confirmation == 'o')) {
                    reinitialiserDonnees(); // Appel à la fonction de LAARIF
                } else {
                    printf("[ANNULATION] Reinitialisation annulee.\n");
                }
                pauseConsole();
                break;

            default: 
                printf("(!) Choix invalide. Veuillez choisir entre 1 et 7.\n");
                pauseConsole();
        }
    }
}