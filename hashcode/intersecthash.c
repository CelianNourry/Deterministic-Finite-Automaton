/* -------------------------------------------------------------
   Intersection avec hashcoding

   F. Balmas                                 2022
   -------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "freel-liste.h"
#include "hashcode.h"

// importation de base et liste
#include "donnees-mots.c"

// petites base et liste pour tester
// char *base[100]={ "abc", "aft", "ahg", "aml", "apo", "arr", "att", "ass", "ati", ""};
// char *liste[]={ "mar", "mtb", "aml", "mti", "att", "muu", "" };

struct linked LINTER;
LINKED TI;

void main() {
  int i,j;
  int cptelt, cptdouble;
  int nbb, nbl, nb;
  LINKED ptr;

  init_freeliste();
  init_tabhash();

  TI = &LINTER;
  init_list(TI);

  for (i=0 ; base[i]!="" ; i++) {
    add_nom(base[i]);
  }
  nbb = cptelt = i;
  //print_tabhash();


  for (j=0, cptdouble=0 ; liste[j]!="" ; j++) {
    if (search_nom(liste[j])!=NULL) {
      //printf("mot existant\n");
      cptdouble++;
      ptr = alloc_list();
      strcpy(ptr->nom, liste[j]);
      add_begin(TI, ptr);
    }
    else {
      cptelt++;
    }
  }
  nbl = j;
  nb = length(TI);
  printf("%d dans base et %d dans liste : %d elt au total, %d doublons trouves\n", nbb, nbl, cptelt, cptdouble);
  printf("longueur liste intersection : %d\n", nb);
  print_list(TI);
}

/* traces d'execution

5263 dans base et 857 dans liste : 6008 elt au total, 112 doublons trouves
longueur liste intersection : 112

*/
