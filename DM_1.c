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
        pcell->noeud = n;
        pcell->suivant = NULL;
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
    }
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
    /*
Affiche sur la sortie standard la structure de l'arbre binaire représenté 
par le nœud racine n.

Return:
    void
*/
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
    affichage_noeud(lst->noeud);
    printf("\n");
    return ;
}

File initialisation(void) {
    /*
     Initialise une Queue vide sur le tas.
     Return:
     File: pointeur sur la Queue initialisée, NULL en cas d'échec
     */
    Queue * pqueue = (Queue*) malloc(sizeof(Queue));
    if (pqueue) {
        pqueue->debut = NULL;
        pqueue->fin = NULL;
        pqueue->taille = 0;
    }
    return pqueue;
}

int est_vide(File f) {
    /*
     Vérifie si la file est vide.
     Return:
     int: 1 si la file est vide, 0 sinon
     */
    return (f == NULL || f->debut == NULL);
}

int enfiler(File f, Noeud * n) {
    /*
     Fait rentrer le pointeur n dans la file f.
     Return:
     int: 1 si l'opération a réussi, 0 sinon
     */
    if (f == NULL) return 0;
    
    Cellule * nouvelle = alloue_cellule(n);
    if (nouvelle == NULL) return 0;
    
    if (f->fin == NULL) {  
        f->debut = nouvelle;
        f->fin = nouvelle;
    } else {
        f->fin->suivant = nouvelle;
        f->fin = nouvelle;
    }
    f->taille++;
    return 1;
}

int defiler(File f, Noeud ** sortant) {
    /*
     Fait sortir de la file f un pointeur sur un nœud et le stocke à l'adresse sortant.
     Return:
     int: 1 si une adresse a été retirée, 0 sinon
     */
    if (f == NULL || est_vide(f) || sortant == NULL) return 0;
    
    Cellule * premiere = f->debut;
    sortant = &(premiere->noeud);
    
    f->debut = premiere->suivant;
    if (f->debut == NULL) { 
        f->fin = NULL;
    }
    
    f->taille--;
    free(premiere);
    return 1;
}

int puissance(int a, int n) {
    if (n == 0) {
        return 1;
    }
    return a * puissance(a, n - 1);
}

int construit_complet(int h, Arbre * a) {
    /*
     Construit dans *a l'arbre complet de hauteur h avec un parcours en largeur
     de 1 à 2^(h+1) - 1.
     Return:
     int: 1 si l'arbre a été correctement construit, 0 sinon
     */
    if (h < 0 || a == NULL) return 0;
    
    int nb_noeuds = puissance(2, h + 1) - 1;
    int valeur_courante = 1;

    Noeud ** noeuds = (Noeud **)malloc(sizeof(Noeud *) * (nb_noeuds + 1));
    if (noeuds == NULL) return 0;
    
    for (int i = 1; i <= nb_noeuds; i++) {
        noeuds[i] = alloue_noeud(valeur_courante++, NULL, NULL);
        if (noeuds[i] == NULL) {
            
            for (int j = 1; j < i; j++) {
                free(noeuds[j]);
            }
            free(noeuds);
            return 0;
        }
    }
    
    for (int i = 1; i <= nb_noeuds / 2; i++) {
        int fg_index = 2 * i;
        int fd_index = 2 * i + 1;
        
        if (fg_index <= nb_noeuds) {
            noeuds[i]->fg = noeuds[fg_index];
        }
        if (fd_index <= nb_noeuds) {
            noeuds[i]->fd = noeuds[fd_index];
        }
    }
    
    *a = noeuds[1]; 
    free(noeuds);    
    return 1;
}

void libere_arbre(Arbre a) {
    if (a == NULL) return;
    libere_arbre(a->fg);
    libere_arbre(a->fd);
    free(a);
}


int construit_filiforme_aleatoire(int h, Arbre *a, int graine) {
    /*
     Construit en mémoire un arbre filiforme de forme aléatoire avec un
     parcours en profondeur préfixe de 1 à h+1.
     Return:
     int: 1 si l'arbre a été correctement construit, 0 sinon
     */
    if (h < 0) {
        *a = NULL;
        return 1;
    }

    *a = alloue_noeud(graine, NULL, NULL);
    (graine)++;
    if (*a == NULL) return 0;

    if (h > 0) {
        if (rand() % 2) {
            if (!construit_filiforme_aleatoire(h - 1, &((*a)->fg), graine)) {
                libere_arbre(*a);
                return 0;
            }
        } else {
            if (!construit_filiforme_aleatoire(h - 1, &((*a)->fd), graine)) {
                libere_arbre(*a);
                return 0;
            }
        }
    }

    return 1;
}


void affiche_arbre(Noeud *a) {
    if (a == NULL) return;
    printf("%d ", a->valeur);
    affiche_arbre(a->fg);
    affiche_arbre(a->fd);

}

int insere_niveau(Arbre a, int niv, Liste * lst) {
    /*
    Ajoute les nœuds de niveau `niv` de l'arbre `a` à la liste `lst`.
    Return:
        int: 1 si les nœuds ont été insérés, 0 en cas d'échec.
    */
    if (a==NULL) return 1;

    if (niv == 0) {
        Cellule * c = alloue_cellule(a);
        if (c==NULL) return 0;
        insere_en_tete(lst, c);
        return 1;
    }

    if(insere_niveau(a->fg, niv - 1, lst)==0) return 0;
    if(insere_niveau(a->fd, niv - 1, lst)==0) return 0;


    return 1;
}

void afficher_liste(Liste lst) {
    while (lst != NULL) {
        printf("%d ", lst->noeud->valeur);
        lst = lst->suivant;
    }
    printf("\n");
}

Liste test_liste(void){
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
    return l;
}

int main(){
    Liste liste_test = test_liste();
    File f = initialisation();
    printf("%d \n", est_vide(f));
    enfiler(f, liste_test->n);
    printf("%d \n", est_vide(f));
    Noeud * sortie = alloue_noeud(0, NULL, NULL);
    defiler(f, &sortie);
    printf("%d \n", est_vide(f));
    return 0;
}
