#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
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
void delet(liste** tete,int pos){
liste*p;
p=*tete;
    if(pos==1){

 *tete=p->suiv;
    if(p->suiv!=NULL){
    p->suiv->pred=NULL;}
    free(p);
    }
      else{
         while (p!=NULL&&pos!=1){
               p=p->suiv;
              pos=pos-1;
           }
             if(pos==1){
                (p->pred)->suiv=p->suiv;
                (p->suiv)->pred=p->pred;
                free(p);
              }
        }
    }


int main(){
     liste *head = NULL;
    int n;
    int position;

    printf("Enter the number of elements: "); 
     scanf("%d", &n);
     srand(time(NULL));
    create_listebid(&head, n);
   affiche_listebid(head);

   printf("donne le position ");
   scanf("%d",&position);
   delet(&head,position);
   return 0;
}