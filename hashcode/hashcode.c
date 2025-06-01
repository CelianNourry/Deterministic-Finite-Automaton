/* ***************************************************************
*
*  Hashcoding
*
*  F. Balmas 2021
*
******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freel-liste.h"
#include "hashcode.h"

//#define NODEBUG
//#define SIZE BUFSIZ

LINKED tabhash[N];

void init_tabhash(void) {
int i;

        for (i=0 ; i < N ; i++)
        {
           tabhash[i] = alloc_list();;
           init_list (tabhash[i]);
        }
}

int compute_hash (char *word) {
int i, nb;

        nb = 0;
        for (i=0 ; word[i] != '\0' ; i++)
           nb += word[i];
        return (nb % N);
}

// retourne pointeur sur chaînon si trouve
// NULL sinon
LINKED search_nom (char *nom) {
int hash;

	hash = compute_hash (nom);
	return (member(nom, tabhash[hash]));
}

void add_nom(char *nom) {
int hash;
LINKED new;

	hash = compute_hash (nom);

	new = alloc_list();
	strcpy(new->nom, nom);
	add_begin (tabhash[hash], new);
}

void print_tabhash(void) {
int i;
	printf("print tabhash\n");
	for(i=0 ; i < N; i++) {
		print_list(tabhash[i]);
	}
}
