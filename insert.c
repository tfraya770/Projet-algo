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

void ajouterDebut(liste **tete, int val) {
     liste *nouv = NULL;
    nouv = malloc(sizeof(liste));
    if (nouv == NULL) {
        printf("Memory allocation failed");
        exit(1);
    }
    nouv->info = val;
    nouv->pred = NULL;
    nouv->suiv = *tete;

    if (*tete != NULL) {
        (*tete)->pred = nouv; 
    }

    *tete = nouv; 
}
void ajouterFin(liste **tete, int val) {
    liste *nouv = malloc(sizeof(liste));
    liste *temp=NULL;
    nouv->info = val;
    nouv->suiv = NULL;
    nouv->pred = NULL;

    if (*tete == NULL) {
        *tete = nouv;
    } else {
        temp = *tete;
        while (temp->suiv != NULL) {
            temp = temp->suiv;
        }
        temp->suiv = nouv;
        nouv->pred = temp;
    }
}
void ajouterPosition(liste **tete, int val, int position) {
    liste *nouv= NULL;
    nouv = malloc(sizeof(liste));
    nouv->info = val;
    nouv->suiv = NULL;
    nouv->pred = NULL;

    
    if (position <= 1) {
        nouv->suiv = *tete;
        (*tete)->pred = nouv;
        *tete = nouv;
    } else {
        liste *temp = *tete;
        int count = 1;
        while (count < position - 1 && temp->suiv != NULL) {
            temp = temp->suiv;
            count++;
        }
        if (count == position - 1) {
            nouv->suiv = temp->suiv;
            if (temp->suiv != NULL) {
                temp->suiv->pred = nouv;
            }
            temp->suiv = nouv;
            nouv->pred = temp;
        }
        
    }
}


int main() {
    liste *head = NULL;
    int n;
    int valeur;

    int position;

    printf("Enter the number of elements: "); 
     scanf("%d", &n);
     srand(time(NULL));
    create_listebid(&head, n);
   affiche_listebid(head);
    
    printf("\n Enter a value to add at the beginning: ");
    scanf("%d", &valeur);
    ajouterDebut(&head,valeur);
    printf("\n List after adding at the beginning :");
    affiche_listebid(head);



    printf("\nEnter a value to add at a postion: ");
    scanf("%d", &valeur);
    printf("\n Enter the position to add at: ");
    scanf("%d", &position);
    ajouterPosition(&head,valeur,position);

    printf("\n List after adding at %d : ",position,"position");
    affiche_listebid(head);


    printf("\nEnter a value to add at the end: ");
    scanf("%d", &valeur);
    ajouterFin(&head, valeur);
    printf("\n List after adding at the end: ");
    affiche_listebid(head);


    return 0;
}
