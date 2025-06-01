#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#define MOTIF_2
//#define MOTIF_2

//Importation des fichiers hashcode vus en cours
#include "hashcode/freel-liste.h"
#include "hashcode/hashcode.h"

// Fichier où se trouve le tableau de 4000 caractères utilisé par la suite ainsi
// que les différentes structures et bases de données
#include "Structures-BDD-tableau.c"
#include "Affichage Projet.c"

#define ETATENTREE 0
#define ETATERREUR -1
#define NBTYPES 5

enum types {C, R, O, Y, AUTRE};

#ifdef MOTIF_1
#define ETATSORTIE 10
#define NBETATS 4
int ttransit[NBETATS][NBTYPES] = {{ 1, -1, -1, -1, -1 },
                                  { -1, -1, 1, 2, -1 },
                                  { -1, -1, 3, 2, -1 },
                                  { -1, 10, -1, -1, -1 }};
#endif

#ifdef MOTIF_2
#define ETATSORTIE 5
#define NBETATS 6
int ttransit[NBETATS][NBTYPES] = {{ 1, -1, -1, -1, -1 },
                                  { 1, -1, 2, -1, -1 },
                                  { -1, -1, -1, 3, -1 },
                                  { -1, 5, 4, 4, -1 },
                                  { -1, 5, -1, 4, -1 },
                                  { -1, 5, -1, -1, -1 }};
#endif

enum types get_type(char str) {
    switch (str) {
        case 'C': return C;
        case 'R': return R;
        case 'O': return O;
        case 'Y': return Y;
        default: return AUTRE;
    }
}

char automate(char *str, char etat, int *len) {
    for (int i = 0; str[i] != '\0'; i++) {
        enum types t = get_type(str[i]);
        etat = ttransit[(int)etat][t];

        //La taille du mot incrémente tant que les caractères lus ne sont pas une erreur
        (etat == ETATERREUR) ? *len = 0 : (*len)++;

        #ifdef MOTIF_1
        if(etat == ETATERREUR || etat == ETATSORTIE) return etat;
        #endif

        #ifdef MOTIF_2
        if(etat == ETATERREUR) return etat;
        if (etat == ETATSORTIE && ttransit[(int)etat][get_type(str[i + 1])] == ETATERREUR) return etat; //Vérification pour R+, on ne s'arrête pas de lire tant qu'il n'y a pas d'erreur (donc pas de R)
        #endif
    }
    return etat;
}
int analyse_tableau(char *str, INFO_MOTS *LISTE_MOTS){
int occurrences = 0, len = 0;
char *current_ptr = str;

    for (int i = 0; *current_ptr != '\0'; i++, current_ptr++) {
        if (automate(current_ptr, ETATENTREE, &len) == ETATSORTIE) {
            LISTE_MOTS[occurrences].position[0] = i;
            LISTE_MOTS[occurrences].position[1] = i + len;

            char *mot = (char *) malloc((len + 1) * sizeof(char)); if (mot == NULL) { printf("Erreur d'allocation de mémoire.\n"); return -1; }

            for (unsigned short int j = i; j < (i + len); j++){
                enum types t = get_type(str[j]);

                switch (t) {
                    case C: LISTE_MOTS[occurrences].points += alphabet.points[0]; break;
                    case R: LISTE_MOTS[occurrences].points += alphabet.points[1]; break;
                    case O: LISTE_MOTS[occurrences].points += alphabet.points[2]; break;
                    case Y: LISTE_MOTS[occurrences].points += alphabet.points[3]; break;
                    default: return -1;
                }
                mot[j - i] = str[j];
            }

            mot[len] = '\0';
            strcpy(LISTE_MOTS[occurrences].mot, mot);
            free(mot);
            occurrences++;
        }
        len = 0;
    }
    return occurrences;
}

void assert_verification(INFO_MOTS *LISTE_MOTS_TEMP){

    #ifdef MOTIF_1
    int occurrences = analyse_tableau(MOTIF_1_TEST, LISTE_MOTS_TEMP);
    assert(occurrences == 2); //Il y a 2 occurences dans le tableau MOTIF_1_TEST
    assert(LISTE_MOTS_TEMP[0].position[0] == 1); //L'occurence 1 est à la position 1 dans le tableau
    assert(LISTE_MOTS_TEMP[1].position[0] == 5); //L'occurence 2 est à la position 6 dans le tableau
    assert(LISTE_MOTS_TEMP[0].points == 38); //L'occurence 1 vaut 38 points
    assert(LISTE_MOTS_TEMP[1].points == 50); //L'occurence 2 vaut 50 points
    #endif

    #ifdef MOTIF_2
    int occurrences = analyse_tableau(MOTIF_2_TEST, LISTE_MOTS_TEMP);
    assert(occurrences == 1); //Il y a 1 occurence dans le tableau MOTIF_1_TEST
    assert(LISTE_MOTS_TEMP[0].position[0] == 3); //L'occurence 1 est à la position 3 dans le tableau
    assert(LISTE_MOTS_TEMP[0].points == 82); //L'occurence 1 vaut 82 points
    #endif
}

int doublons_hashage(INFO_MOTS *LISTE_MOTS){
int nb_mot_unique = 0, nb_mot = 0;

    init_freeliste();
    init_tabhash();

    while (LISTE_MOTS[nb_mot].mot[0] != '\0'){
        if (search_nom(LISTE_MOTS[nb_mot].mot) == NULL) {
            add_nom(LISTE_MOTS[nb_mot].mot);
            LISTE_MOTS[nb_mot].doublons++;
            LISTE_MOTS[nb_mot].prem_lu = true;
            nb_mot_unique++;
        }
        else for (int i = 0; LISTE_MOTS[i].mot[0] != '\0'; i++ ) if (strcmp(LISTE_MOTS[i].mot, LISTE_MOTS[nb_mot].mot) == 0) LISTE_MOTS[i].doublons++;
        nb_mot++;
    }
    return nb_mot_unique;
}

int *doublons_iteration(INFO_MOTS *LISTE_MOTS, int nb_occ, int *nb_comparaisons_1){
int *TAB_POINTS_DIFF = (int *) malloc((nb_occ + 1) * sizeof(int)); if (TAB_POINTS_DIFF == NULL) { printf("Erreur d'allocation de mémoire.\n"); return NULL; }
int nb_points_unique = 0;
*nb_comparaisons_1 = 0;
 
    for (int i = 0; i < nb_occ; i++) {
        (*nb_comparaisons_1)++;
        bool existe = false;
        
        for (int j = 0; j < nb_points_unique; j++) {
            (*nb_comparaisons_1)++;
            if (LISTE_MOTS[i].points == TAB_POINTS_DIFF[j]) {
                (*nb_comparaisons_1)++;
                existe = true;
                break;
            }
        }
        
        if (!existe) {
            TAB_POINTS_DIFF[nb_points_unique] = LISTE_MOTS[i].points;
           (*nb_comparaisons_1)++, nb_points_unique++;
        }
    }

    TAB_POINTS_DIFF[nb_points_unique + 1] = -1; // Marque la fin du tableau
    return TAB_POINTS_DIFF;
}

int *doublons_suppression(INFO_MOTS *LISTE_MOTS, int nb_occ, int *nb_comparaisons_2){
int *TAB_POINTS_DIFF = (int *) malloc((nb_occ + 1) * sizeof(int)); if (TAB_POINTS_DIFF == NULL) { printf("Erreur d'allocation de mémoire.\n"); return NULL; }
*nb_comparaisons_2 = 0;

    for (int i = 0; i < nb_occ; i++) {
        TAB_POINTS_DIFF[i] = LISTE_MOTS[i].points;
        (*nb_comparaisons_2)++;
    }

     for (int i = 0; i < nb_occ; i++) {
        (*nb_comparaisons_2)++;
        for (int j = i + 1; j < nb_occ; j++) {
            (*nb_comparaisons_2)++;
            if (TAB_POINTS_DIFF[i] == TAB_POINTS_DIFF[j]) {
                (*nb_comparaisons_2)++;
                for (int k = j; k < nb_occ - 1; k++){
                    (*nb_comparaisons_2)++;
                    TAB_POINTS_DIFF[k] = TAB_POINTS_DIFF[k + 1];
                }
                nb_occ--;
                j--;
            }
        }
    }

    int *temp = (int *)realloc(TAB_POINTS_DIFF, (nb_occ + 1) * sizeof(int));
    if (temp == NULL) {
        printf("Erreur de réallocation de mémoire.\n");
        free(TAB_POINTS_DIFF);
        return NULL;
    } else {
        TAB_POINTS_DIFF = temp;
    }

    TAB_POINTS_DIFF[nb_occ + 1] = -1; // Marque la fin du tableau

    return TAB_POINTS_DIFF;
}

void ordre_croissant(INFO_MOTS *LISTE_MOTS, int nb_occ){
    for (int i = 0; i < nb_occ; i++)
        for (int j = 0; j < nb_occ; j++)
            if (LISTE_MOTS[i].doublons > LISTE_MOTS[j].doublons){
                INFO_MOTS temp;
                temp = LISTE_MOTS[i];
                LISTE_MOTS[i] = LISTE_MOTS[j];
                LISTE_MOTS[j] = temp;
            }
}

float points_moyen(INFO_MOTS *LISTE_MOTS, int nb_occ, int *TAB_POINTS_DIFF){
float resultat = 0.0f;

    if (LISTE_MOTS != NULL){
        for (int i = 0; LISTE_MOTS[i].mot[0] != '\0'; i++)
            if (LISTE_MOTS[i].doublons > 0 && LISTE_MOTS[i].prem_lu) resultat += ((float)LISTE_MOTS[i].points * (float)LISTE_MOTS[i].doublons);
    }

    else if (TAB_POINTS_DIFF != NULL){
        for (int i = 0; TAB_POINTS_DIFF[i + 1] != -1; i++){
            resultat += TAB_POINTS_DIFF[i];
            nb_occ++;
        }
    }
    else {
        return -1;
    }

    return (resultat / nb_occ);
}

int main(void) {
    creation_TABLEAU();
    INFO_MOTS *LISTE_MOTS = (INFO_MOTS *)malloc((TAB_SIZE) * sizeof(INFO_MOTS));

    int occurrences = analyse_tableau(TABLEAU, LISTE_MOTS); //Etape 2-3
    int MOTS_DIFFERENTS_HASHAGE = doublons_hashage(LISTE_MOTS); //ETape 5
    float POINTS_MOYENS = points_moyen(LISTE_MOTS, occurrences, NULL);
    int nb_comparaisons_1, nb_comparaisons_2;
    int *TAB_POINTS_DIFF_1 = doublons_iteration(LISTE_MOTS, occurrences, &nb_comparaisons_1); //Etape 8_1
    int *TAB_POINTS_DIFF_2 = doublons_suppression(LISTE_MOTS, occurrences, &nb_comparaisons_2); //Etape 8_2
    float POINTS_MOYENS_1 = points_moyen(NULL, 0, TAB_POINTS_DIFF_1); //Etape 9

    affichage(LISTE_MOTS, occurrences, "ETAPE 2-3", NULL, 0);
    affichage(LISTE_MOTS, MOTS_DIFFERENTS_HASHAGE, "ETAPE 5", NULL, 0);
    ordre_croissant(LISTE_MOTS, occurrences);
    affichage(LISTE_MOTS, MOTS_DIFFERENTS_HASHAGE, "ETAPE 6", NULL, 0);
    affichage(LISTE_MOTS, POINTS_MOYENS, "ETAPE 7", NULL, 0);
    affichage(NULL, 0, "ETAPE 8_1", TAB_POINTS_DIFF_1, nb_comparaisons_1);
    affichage(NULL, 0, "ETAPE 8_2", TAB_POINTS_DIFF_2, nb_comparaisons_2);
    affichage(NULL, POINTS_MOYENS_1, "ETAPE 9", NULL, 0);

    free(LISTE_MOTS);
    LISTE_MOTS = NULL;

    INFO_MOTS *MOTS_MOTIF_1 = (INFO_MOTS *)malloc((TAB_SIZE) * sizeof(INFO_MOTS));
    INFO_MOTS *MOTS_MOTIF_2 = (INFO_MOTS *)malloc((TAB_SIZE) * sizeof(INFO_MOTS));
    assert_verification(MOTS_MOTIF_1); //Etape 4
    assert_verification(MOTS_MOTIF_2);

    free(MOTS_MOTIF_1);
    free(MOTS_MOTIF_2);

    return 0;
}
