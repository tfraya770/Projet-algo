#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <stdbool.h>
typedef struct liste liste;
struct liste {
    int info;
    liste *pred;
    liste *suiv;
} cellule;

void create_listebid(liste **tete, int nbElmt) {
    liste *Q = NULL;
    liste *nouv = NULL;
    *tete = NULL;

    for (int i = 0; i < nbElmt; i++) {
        nouv = (liste *)malloc(sizeof(liste));

        if (nouv == NULL) {
            printf("Memory allocation failed");
            exit(1);
        }

        nouv->pred = NULL;
        nouv->suiv = NULL;
        nouv->info = rand() % 100; 

        if (*tete == NULL) {
            *tete = nouv;
        } else {
            Q->suiv = nouv;
            nouv->pred = Q;
        }
        Q = nouv;
    }
    if (Q != NULL) {
        Q->suiv = NULL;
    }
}

void affiche_listebid(liste *tete) {
    liste *p = tete;
    while (p != NULL) {
        printf("%d ", p->info);
        p = p->suiv;
    }
}

void delet(liste** tete,int pos,int n){
liste*p;
p=*tete;
    if(pos==1){

 *tete=p->suiv;
    if(p->suiv!=NULL){
    p->suiv->pred=NULL;}
    free(p);
    }
    else{if(pos==n){
        while((p->suiv)!=NULL){
            p=p->suiv;}
            p->pred->suiv=NULL;
            free(p);
    }

        else{
        while (p->suiv!=NULL&&pos!=1)
        {p=p->suiv;
                pos=pos-1;
            }
            if(pos==1){
                (p->pred)->suiv=p->suiv;
                (p->suiv)->pred=p->pred;
                free(p);
            }
        }
    }
}

bool recherch(liste *tete ,int var){
liste*p;
p=tete;
while (p->suiv!=NULL)
{
    if(p->info=var) return true;
   else  p=p->suiv;
}
return false;
}

void Sorting(liste*tete){
liste*p;
liste*q;
int x;
if (tete!=NULL){
p=tete;
while (p->suiv!=NULL)
{   q=p->suiv;
    while ((q!=NULL))
    {
    if ((q->info )<(p->info))
    {x=p->info;
   p->info= q->info;
   q->info=x;
   }
   q=q->suiv;

}
p=p->suiv;
}
}
}


int main() {
    liste *head = NULL;
    int n,var;
int position;
bool t;
    printf("Enter the number of elements: ");
    scanf("%d", &n); 
    srand(time(NULL));

    create_listebid(&head, n);
    affiche_listebid(head);
    /*************************/
  printf("\n Enter the position that you need to delet: ");
    scanf("%d", &position);
    delet(&head,position,n);
    affiche_listebid(head);
    /***********************/
 printf("\n Enter the valeure that you need to recherch: ");
    scanf("%d", &var);
    t=recherch(head,var);
    printf("\n %d",t);
    /**************************/
    Sorting(head);
      affiche_listebid(head);
    return 0;
}
