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
    int n;
  
    printf("Enter the number of elements: "); 
     scanf("%d", &n);
     srand(time(NULL));
    create_listebid(&head, n);
   affiche_listebid(head);

Sorting(head);
    affiche_listebid(head)

    return 0;
}