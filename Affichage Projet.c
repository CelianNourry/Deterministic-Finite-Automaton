void affichage(INFO_MOTS *LISTE_MOTS, float val, const char *etape, int *TAB_POINTS_DIFF, int nb_comparaisons){
int espace_nb = 0, hors_espaces = 0, I_DEBUT, I_FIN;
    
    if ((strcmp(etape, "ETAPE 2-3") == 0) || strcmp(etape, "ETAPE 3") == 0){
        int POINTS;
        printf("\033[4;34mEtape 2-3 :\033[0m\n\n");
        printf(" ---------------------------------\n| \033[1;35mChaîne    \033[0m|\033[1;35m Points \033[0m| \033[1;35mIndice\033[0m     |\n ---------------------------------\n");
        for (int i = 0; LISTE_MOTS[i].mot[0] != '\0'; i++) {
            POINTS = LISTE_MOTS[i].points, I_DEBUT = LISTE_MOTS[i].position[0], I_FIN = LISTE_MOTS[i].position[1];
            printf("| %s", LISTE_MOTS[i].mot);

            I_FIN > 10 ? hors_espaces += (I_FIN - I_DEBUT) - 10 : hors_espaces;
            for (unsigned short int j = 10; j > (I_FIN - I_DEBUT); j--) printf(" ");
            printf("|   %d   ", POINTS);
            printf("| %d-%d", I_DEBUT, I_FIN);
            if (I_DEBUT > 999) espace_nb++; else if (I_DEBUT > 99) espace_nb += 2; else if (I_DEBUT > 9) espace_nb += 3; else if (I_DEBUT >= 0) espace_nb += 4;
            if ((I_FIN) > 999) espace_nb++; else if ((I_FIN) > 99) espace_nb += 2; else if ((I_FIN) > 9) espace_nb += 3; else if (I_FIN >= 0) espace_nb += 4;
            for (; espace_nb > 0; espace_nb--) printf(" ");
            printf("|\n ---------------------------------\n");
            hors_espaces = 0;
        }
        #ifdef MOTIF_1
        printf("\nNombre total d'occurrences du motif 1 : %d\n", (int)val);
        #endif

        #ifdef MOTIF_2
        printf("\nNombre total d'occurrences du motif 2 : %d\n", (int)val);
        #endif
    }

    else if ((strcmp(etape, "ETAPE 5") == 0) || strcmp(etape, "ETAPE 6") == 0){
        int DOUBLONS;
        (strcmp(etape, "ETAPE 5") == 0) ? printf("\033[4;34mEtape 5 :\033[0m\n\n") : printf("\033[4;34mEtape 6 :\033[0m\n\n");
        printf(" ------------------------------\n| \033[1;35mChaîne unique \033[0m|\033[1;35m Occurences \033[0m |\n ------------------------------\n");
        for (int i = 0; LISTE_MOTS[i].mot[0] != '\0'; i++) {
            if (LISTE_MOTS[i].doublons > 0 && LISTE_MOTS[i].prem_lu){
                DOUBLONS = LISTE_MOTS[i].doublons, I_DEBUT = LISTE_MOTS[i].position[0], I_FIN = LISTE_MOTS[i].position[1];
                printf("| %s    ", LISTE_MOTS[i].mot);

                I_FIN > 10 ? hors_espaces += (I_FIN - I_DEBUT) - 10 : hors_espaces;
                for (unsigned short int j = 10; j > (I_FIN - I_DEBUT); j--) printf(" ");
                printf("|   %d  ", DOUBLONS);
                if (DOUBLONS > 999) espace_nb += 4; else if (DOUBLONS > 99) espace_nb += 5; else if (DOUBLONS > 9) espace_nb += 6; else if (DOUBLONS >= 0) espace_nb += 7;
                for (; espace_nb > 0; espace_nb--) printf(" ");
                printf("|\n ------------------------------\n");
                hors_espaces = 0;
            }
        }
        printf("\nNombre total de mots uniques trouvés avec le motif : %d\n\n", (int)val);
    }

    else if ((strcmp(etape, "ETAPE 7") == 0)){
        printf("\033[4;34mEtape 7 :\033[0m\n\n");
        printf("Points moyens rapportés par le motif : %f\n\n", val);
    }

    else if ((strcmp(etape, "ETAPE 8_1") == 0) || (strcmp(etape, "ETAPE 8_2") == 0)){
        unsigned short int nb_points_uniques = 0;
        printf("\033[4;34mEtape 8 :\033[0m");
        strcmp(etape, "ETAPE 8_1") == 0 ? printf(" Algorithme d'itération\n\n") : printf(" Algorithme de suppression\n\n");
        printf(" ---------------\n| \033[1;35mPoints uniques\033[0m|\n ---------------");
        for (int i = 0; TAB_POINTS_DIFF[i + 1] != -1; i++, nb_points_uniques++) printf("\n|      %d       |\n ---------------", TAB_POINTS_DIFF[i]);
        printf("\nNombre de points uniques : %d\n", nb_points_uniques);
        printf("Nombre de comparaisons: %d\n", nb_comparaisons);
    }

    else if ((strcmp(etape, "ETAPE 9") == 0)){
        printf("\033[4;34mEtape 9 :\033[0m\n\n");
        printf("Points moyens rapportés par l'ensemble des points différents : %2f\n\n", val);
    }
}