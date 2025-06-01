/* ***************************************************************
*
*  Hashcoding
*
*  F. Balmas 2021
*
******************************************************************/
// valeur standard
// #define N 53
// valeur de demo
#define N 1

extern LINKED tabhash[N];

LINKED search_nom(char *nom);
void add_nom(char *s);
void init_tabhash(void);
void print_tabhash(void);
int compute_hash(char *word);
