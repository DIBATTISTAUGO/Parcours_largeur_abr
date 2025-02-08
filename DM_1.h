#include <stdio.h>


typedef struct _noeud{
    int valeur;
    struct _noeud *fg, *fd;
}Noeud, *Arbre;

typedef struct cell{
    Noeud * n;
    struct cell * suivant;
    struct cell * precedent;
}Cellule, *Liste;

typedef struct {
    Liste debut;
    Liste fin; 
    int taille;
}Queue, * File;

Cellule * alloue_cellule(Noeud * n);
void insere_en_tete(Liste * l, Cellule * c);
Cellule * extrait_tete(Liste * l);
void affiche_liste_renversee(Liste lst);
File initialisation(void);
int est_vide(File f);
int enfiler(File f, Noeud * n);
int defiler(File f, Noeud ** sortant);
Noeud * alloue_noeud(int val, Arbre fg, Arbre fd);
int construit_complet(int h, Arbre * a);
int construit_filiforme_aleatoire(int h, Arbre * a, int graine);