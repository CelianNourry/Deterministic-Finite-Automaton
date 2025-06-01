/*  Ce fichier contient les definitions necessaires pour
    l'implementation de la librairie list (version avec freelist)

    F. Balmas 2023
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "freel-liste.h"


// taille "standard" de la freelist
// #define NL 200
// taille de la freelist (pour demo)
#define NL 20
#define NODEBUG


// tete et pointeur pour la freelist
static struct linked TETE;
static struct linked *T;

// initialiser le ptr T sur TETE (T est la tete de la freeliste)
void init_freeliste(void) {
    T = &TETE;
}

// allouer un chainon, si necessaire remplir la freeliste
LINKED alloc_list(void) {
LINKED p;
    if (T->cell == NULL)
        remplir_freeliste();
    //print_list(T);
    p = remove_begin(T);
    init_list(p);
    return p;
}

void init_list (LINKED l) {
	l->cell = NULL;
}

void add_begin (LINKED t, LINKED l) {
	l->cell = t->cell;
	t->cell = l;
}

void add_end (LINKED t, LINKED l) {
LINKED p;
	for (p=t ; p->cell!=NULL ; p=p->cell);
	p->cell = l;
}

LINKED remove_begin (LINKED t) {
LINKED ptr;
    if (t->cell == NULL) {
        fprintf(stderr, "liste vide, remove imposible\n");
        return NULL;
    }
    ptr = t->cell;
	t->cell = (t->cell)->cell;
    return ptr;
}

LINKED remove_end (LINKED t) {
LINKED p, ptr;
    if (t->cell == NULL) {
        fprintf(stderr, "liste vide, remove imposible\n");
        return NULL;
    }
	for (p=t ; (p->cell)->cell != NULL ; p=p->cell);
    ptr = p->cell;
	p->cell = NULL;
	return ptr;
}

void print_list (LINKED l) {
LINKED p;

	for (p=l->cell ; p!= NULL ; p=p->cell) print_nom(p);
	printf ("\n");
}

void print_nom(LINKED contact) {
  printf ("%s, ", contact->nom);
}

LINKED member (char *x, LINKED l) {
LINKED p;
	for (p=l->cell ; p!=NULL ; p=p->cell) {
	   if ( strcmp(p->nom, x) == 0 )
		return (p);
	   }
	return ((LINKED) 0);
}

int MEMBER (char *x, LINKED l) {
LINKED p;
	for (p=l->cell ; p!=NULL ; p=p->cell) {
	   if ( strcmp(p->nom, x) == 0 )
		return 2;
	   }
	return 0;
}

int length(LINKED l) {
LINKED p;
int n=0;
 for (p=l->cell ; p!=NULL ; p=p->cell)
   n++;
 return n;
}

// allouer un tableau de structures linked et les chainer
// pour en faire la freeliste
int cpt=0;
void remplir_freeliste(void) {
LINKED m, pm, pf;
#ifdef DEBUG
printf ("Remplissage de la freeliste ...\n");
#endif
 m = (LINKED) malloc(NL * sizeof(struct linked));
 if (m == NULL) {
   printf ("Plus de memoire disponible ...\n");
   exit(1);
 }
 pf = T;
 for (pm=m; pm<m+NL ; pm++) {
   pf->cell = pm;
   pf = pf->cell;
 }
 pf->cell = NULL;
#ifdef DEBUG
printf ("Length FREELIST : %d\n", length(T));
#endif
}
