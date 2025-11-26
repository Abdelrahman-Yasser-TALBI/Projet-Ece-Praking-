/**
 * PARKING INTELLIGENT
 * 
 * Programme de gestion d'un parking avec:
 * - Enregistrement des entrées/sorties
 * - Calcul automatique des montants (2€/heure)
 * - Statistiques
 * - Sauvegarde persistante
 * 
 * Auteurs: [Noms des étudiants]
 * Date: [Date]
 */

#include <stdio.h>
#include "gestion_voitures.h"
#include "menu_logique.h"
#include "statistiques.h"

int main() {
    printf("\n");
    printf("╔════════════════════════════════════════╗\n");
    printf("║   Bienvenue au Parking Intelligent !   ║\n");
    printf("╚════════════════════════════════════════╝\n");
    printf("\n");
    
    // Lancement du menu principal
    executerMenu();
    
    return 0;
}
