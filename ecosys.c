#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "ecosys.h"

float p_ch_dir=0.01;
float p_reproduce_proie=0.4;
float p_reproduce_predateur=0.5;
int temps_repousse_herbe=-15;
int gain_energie_proie=6;
int gain_energie_predateur=20;
float p_manger=0.4;


/* PARTIE 1*/
/* Fourni: Part 1, exercice 3, question 2 */
Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 3, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* A faire. Part 1, exercice 5, question 1 */
void ajouter_animal(int x, int y,  float energie, Animal **liste_animal) {
  assert(0 < x); assert(x<=SIZE_X);
  assert(0 < y); assert(y <= SIZE_Y);
  Animal* nouveau = creer_animal(x, y, energie);
  nouveau->suivant = *(liste_animal);
  *(liste_animal)=nouveau;
}
/* A Faire. Part 1, exercice 5, question 2 */
Animal* liberer_liste_animaux(Animal *liste) {
Animal* a = liste;
	while(a!=NULL){
	Animal *tmp = a;
	a = a->suivant;
	free(tmp);
	tmp=NULL;
	}

  return NULL;
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal **liste, Animal *animal) {
  /*A Completer*/
  Animal *pa;

  assert(liste);
  pa=*liste;
  if(*liste==animal){ // si c'est la tete qu'il faut supprimer
    *liste=(*liste)->suivant;
    free(pa);
  }else { // si c'est au milieu on se place juste avant 
          // l'element à supprimer
    while (pa->suivant && pa->suivant!=animal)
      pa=pa->suivant;
    if(pa->suivant){
      Animal *la=pa->suivant;
      pa->suivant=la->suivant;
      free(la);
    }
  }
}

/* Part 2. Exercice 5, question 1 */
void bouger_animaux(Animal *la) {
    /*A Completer*/
  //int pas;
  while(la) {
    // dir[0]
    if(rand()/RAND_MAX < p_ch_dir){
      la->dir[0]=rand()%3-1;
    }
    //dir[1]
    if(rand()/RAND_MAX < p_ch_dir){
      la->dir[1]=rand()%3-1;
    }
    la->y = (la->y - la->dir[0] + SIZE_Y)%SIZE_Y;
    la->x = (la->x - la->dir[1] + SIZE_X)%SIZE_X;
    la=la->suivant;
  }
}

/* Part 2. Exercice 5, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
   /*A Completer*/
  assert(liste_animal);
  Animal *pa=*liste_animal;
  while(pa) {
    if(rand()/RAND_MAX < p_reproduce){
      pa->energie /= 2;
      ajouter_animal(pa->x, pa->y, pa->energie, liste_animal);
    }
    pa=pa->suivant;
  }
}

/* Part 2. Exercice 7, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    /*A Completer*/
  assert(liste_proie);
  Animal *sup, *pa=*liste_proie;
  bouger_animaux(*liste_proie);
  while (pa)
  {
    pa->energie--;  // baisser l'energie de 1
    if(monde[pa->x][pa->y] >= 0) {  // s'il ya de l'herbe
      pa->energie += gain_energie_proie;  // gagner de l'energie
      monde[pa->x][pa->y]=temps_repousse_herbe; // temps de repousse a jour
    }
    if(pa->energie < 0){  // supprimer les proies dont l'energie est inferieure à 0
      sup=pa;
      pa=pa->suivant;
      enlever_animal(liste_proie, sup);
    }else
      pa=pa->suivant;
    
  }
  reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 8, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
    /*A Completer*/
    while(l){
      if(l->x==x && l->y==y)
        return l;
      l=l->suivant;
    }
  return NULL;
} 
/* Part 2. Exercice 8, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
   /*A Completer*/
  assert(liste_predateur);
  assert(liste_proie);
  Animal *sup, *pa=*liste_predateur;
  bouger_animaux(*liste_predateur);
  while (pa)
  {
    pa->energie--;  // baisser l'energie de 1
    sup=animal_en_XY(*liste_proie, pa->x, pa->y);  // proie a la meme position
    if(sup && (rand()/(float)RAND_MAX < p_manger)) {  // s'il ya une proie et probablement peut manger
      pa->energie += gain_energie_predateur;  // gagner de l'energie
      enlever_animal(liste_proie, sup);       // la proie meurt
    }
    if(pa->energie < 0){  // supprimer les proies dont l'energie est inferieure à 0
      sup=pa;
      pa=pa->suivant;
      enlever_animal(liste_predateur, sup);
    }else
      pa=pa->suivant;
    
  }
  reproduce(liste_predateur, p_reproduce_predateur);
}


/* Part 2. Exercice 6, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){

   /*A Completer*/
  int i, j;
  for(i=0; i<SIZE_X; i++)
    for(j=0; j<SIZE_Y; j++)
      monde[i][j]++;

}
/* Part 1. Exercice 4, question 1 */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  //int nbpred=0,nbproie=0;
  Animal *pa=NULL;

  /* on initialise le tableau */
  for(i=0; i<SIZE_X; i++)
    for(j=0; j<SIZE_Y; j++)
      ecosys[i][j]=' ';


  /* on ajoute les proies */
  pa=liste_proie;
  while (pa)
  {
    ecosys[pa->x][pa->y]='*';
    pa=pa->suivant;
  }
  


  /* on ajoute les predateurs */
  pa=liste_predateur;
  while (pa)
  {
    if(ecosys[pa->x][pa->y] == '*')
      ecosys[pa->x][pa->y] = '@';
    else
      ecosys[pa->x][pa->y] = 'O';
    pa=pa->suivant;
  }
  


  /* on affiche le tableau */
  for(i=0; i<SIZE_X; i++){
    for(j=0; j<SIZE_Y; j++)
      printf("%c", ecosys[i][j]);
    printf("\n");
  }

}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 3, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la = la->suivant;
  }
  return cpt;
}

void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}



