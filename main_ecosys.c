#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 20
#define T_WAIT 40000
#define MAX_ITERATIONS 200

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/


int main(void) {
 
  /* A completer. Part 2:
   * exercice 6, question 1*/
  int i, x, y, tabHerbe[SIZE_X][SIZE_Y]={0};// declaration du tableau static a deux dimensions
  float en;
  /* exercice 7, question 2*/
  Animal* lproie=NULL;
  for(i=0; i<NB_PROIES; i++){
    en=(rand()/(float)RAND_MAX*10)+1.;  // energie aleatoire entre 1 et 11
    x=(rand()%SIZE_X);
    y=rand()%SIZE_Y;
    printf("x=%d\ty=%d\ten=%lf\n", x, y, en);
    lproie=ajouter_en_tete_animal(lproie, creer_animal(x, y, en));
  }
  printf("nombre de proies : %d\n", compte_animal_rec(lproie));
  i=0;
  while(lproie && i++<MAX_ITERATIONS){
    clear_screen();
    printf("%d\n\n\n\n", i);
    rafraichir_proies(&lproie, tabHerbe);
    afficher_ecosys(NULL, lproie);
    sleep(1);
  }
  /* exercice 8, question 3
   * exercice 9, question 1
   */

  printf("nombre de proies : %d\n", compte_animal_it(lproie));
  return 0;
}



