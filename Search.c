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
bool recherch(liste *tete ,int var){
liste*p=tete;
while (p!=NULL)
{
    if(p->info=var) {return true;}
   else  {p=p->suiv;}
}
return false;
}
int main(){
     liste *head = NULL;
    int n;
    int val;
bool t;
    

    printf("Enter the number of elements: "); 
     scanf("%d", &n);
     srand(time(NULL));
    create_listebid(&head, n);
   affiche_listebid(head);

   printf("donne la valeur qui tu recherch: ");
   scanf("%d",&val);
  recharch(head,val);
   return 0;
}