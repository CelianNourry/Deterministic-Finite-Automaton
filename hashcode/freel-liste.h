/************************************************************
*
*   Ce fichier contient les declarations necessaires pour
*    utiliser la librairie list
*
*   F. Balmas 2023
*
*************************************************************/


struct linked {
    char nom[21]; // le nom, max 20 char
    struct linked *cell; // pointeur sur le chainon suivant
};

// creation du type LINKED pour simplifier les declarations
typedef struct linked *LINKED;

// alloue un chainon
LINKED alloc_list(void);
// initialise la liste
void init_list(LINKED p);
// initialise la freeliste
void init_freeliste(void);
// remplir la freelistevoid remplir_freeliste(void);
void remplir_freeliste(void);

// ajoute un chainon au debut de la liste
void add_begin (LINKED t, LINKED l);
// ajoute a la fin
void add_end (LINKED t, LINKED l);
// enleve au debut
LINKED remove_begin (LINKED t);
// enleve a la fin
LINKED remove_end (LINKED t);

// affiche le contenu d'une liste
void print_list (LINKED l);
// affiche un chainon
void print_nom(LINKED p);

// teste si un elt appartient a une liste
LINKED member (char *x, LINKED l);
int MEMBER (char *x, LINKED l);

// calcule la longueur de la liste
int length(LINKED l);
