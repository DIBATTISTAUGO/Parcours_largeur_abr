#include <stdio.h>
#include <stdlib.h>
#include "DM_1.h"

/*Modèle doc fonction*/
/*
Description...
Return:
    type: 
    type:
    type:
*/

Noeud * alloue_noeud(int val, Arbre fg, Arbre fd){
    /*
    alloue sur le tas un Noeud contenant la valeur val 
    et fg et fd comme enfant.
    Return:
        Noeud *: pointeur sur le Noeud alloué, sera NULL 
                si l'allocation n'a pas fonctionnée.
    */
    Noeud * pN = (Noeud*) malloc(sizeof(Noeud));
    if (pN){
        pN->valeur =  val;
        pN->fg = fg;
        pN->fd = fd;
    }
    return pN;
}

Cellule * alloue_cellule(Noeud * n){
    /*
    Fonction d'allocation et de création d'une cellule à partir d'un noeud, 
    Return:
        Cellule*: un pointeur sur la cellule crée, sera NULL si il y a eu
                  un problème d'allocation 
    */
   Cellule * pcell = (Cellule*) malloc(sizeof(Cellule));
    if(pcell){
        pcell->n = n;
        pcell->suivant = NULL;
        pcell->precedent = NULL;
    }
   return pcell;
}

void insere_en_tete(Liste * l, Cellule * c){
    /*
    Ajoute en tête de la liste *l la cellule *c
    Return:
        void 
    */
    if (l != NULL){
        c->suivant = *l;
        (*l)->precedent = c;
    }
    c->precedent = NULL;
    *l = c;
   return ;
}

Cellule * extrait_tete(Liste * l){
    /*
    Retire le premier maillon de la liste *l s’il existe et le
    renvoie (et qui renvoie NULL sinon).
    Return:
        Cellule*: pointeur sur la cellule extraite, il sera NULL 
                si la Liste est vide
    */
    if (*l == NULL) return NULL;
    Cellule * tete = *l;
    *l = (*l)->suivant;
   return tete;
}

void affichage_noeud(Noeud * n){
    if (!n)return ;
    printf("{%d", n->valeur);
    affichage_noeud(n->fg);
    affichage_noeud(n->fd);
    printf("}");
}

void affiche_liste_renversee(Liste lst){
    /*
    Affiche sur la sortie les éléments de la liste lst du
    dernier au premier.
    Return:
        void
    */
    if (lst == NULL) return;
    // if (lst->suivant == NULL){
    //     affichage_noeud(lst->n);
    // }
    affiche_liste_renversee(lst->suivant);
    affichage_noeud(lst->n);
    printf("\n");
    return ;
}

File initialisation(void);
int est_vide(File f);
int enfiler(File f, Noeud * n);
int defiler(File f, Noeud ** sortant);
Noeud * alloue_noeud(int val, Arbre fg, Arbre fd);
int construit_complet(int h, Arbre * a);
int construit_filiforme_aleatoire(int h, Arbre * a, int graine);

int main(){
    Noeud * n = alloue_noeud(10, NULL, NULL);
    Noeud * n1 = alloue_noeud(4, NULL, NULL);
    Noeud * n2 = alloue_noeud(6, NULL, NULL);
    Cellule * c = alloue_cellule(n);
    Cellule * c1 = alloue_cellule(n1);
    Cellule * c2 = alloue_cellule(n2);
    Liste l = alloue_cellule(NULL);
    insere_en_tete(&l, c);
    insere_en_tete(&l, c1);
    insere_en_tete(&l, c2);
    //affiche_liste_renversee(l);
    extrait_tete(&l);
    //affiche_liste_renversee(l);
    return 0;
}