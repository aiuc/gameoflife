#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "ecosys.h"


#define NB_PROIES 20
#define NB_PREDATEURS 20





int main(void) {

  /* A Completer. */
  /* Part 1, exercice 5, question 3 */
  Animal *proies=NULL, *p2=creer_animal(5, 3, 3.5),*p4=creer_animal(4, 3, 1.3),*p1=creer_animal(0, 2, 4.5),*p3=creer_animal(2, 7, 5.9);
  Animal *predateurs=NULL, *p5=creer_animal(3, 3, 3.5),*p6=creer_animal(6, 3, 1.3),*p7=creer_animal(1, 2, 4.5),*p8=creer_animal(7, 7, 5.9);
  proies = ajouter_en_tete_animal(proies, p1);
  proies = ajouter_en_tete_animal(proies, p2);
  proies = ajouter_en_tete_animal(proies, p3);
  proies = ajouter_en_tete_animal(proies, p4);
  predateurs = ajouter_en_tete_animal(predateurs, p5);
  predateurs = ajouter_en_tete_animal(predateurs, p6);
  predateurs = ajouter_en_tete_animal(predateurs, p7);
  predateurs = ajouter_en_tete_animal(predateurs, p8);
  
 
  printf("Le nombre de proies est : %d\n", compte_animal_rec(proies));
  printf("Le nombre de predateurs est : %d\n", compte_animal_rec(predateurs));
  enlever_animal(&proies, p1);
  enlever_animal(&proies, p2);
  enlever_animal(&proies, p3);
  enlever_animal(&proies, p4);
  enlever_animal(&predateurs, p5);
  enlever_animal(&predateurs, p6);
  enlever_animal(&predateurs, p7);
  enlever_animal(&predateurs, p8);
  
  return 0;
}
