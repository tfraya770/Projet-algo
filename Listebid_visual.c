#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "raylib.h"
#define MAX_OPTIONS 5
#define BOX_WIDTH 120
#define BOX_HEIGHT 80
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
void drawSingleNode(int posX, int posY, int val) {
    DrawRectangle(posX, posY, BOX_WIDTH, BOX_HEIGHT, PINK);
    DrawRectangleLines(posX, posY, BOX_WIDTH, BOX_HEIGHT, BLACK);
    DrawText(TextFormat("%d", val), posX + 40, posY + 30, 25, BLACK);

    DrawLine(posX + BOX_WIDTH / 3, posY, posX + BOX_WIDTH / 3, posY + BOX_HEIGHT, BLACK);
    DrawLine(posX + BOX_WIDTH / 3 * 2, posY, posX + BOX_WIDTH / 3 * 2, posY + BOX_HEIGHT, BLACK);
}
void drawDoublyLinkedList(liste *tete) {
    int posX = 100;
    int posY = 200;
    int lineSpacing = BOX_WIDTH / 3;
    while (tete != NULL) {
        DrawRectangle(posX, posY, BOX_WIDTH, BOX_HEIGHT, PINK);
        DrawRectangleLines(posX, posY, BOX_WIDTH, BOX_HEIGHT, BLACK);
        DrawText(TextFormat("%d", tete->info), posX + 40, posY + 30, 25, BLACK);

        DrawLine(posX + lineSpacing, posY, posX + lineSpacing, posY + BOX_HEIGHT, BLACK);
        DrawLine(posX + lineSpacing * 2, posY, posX + lineSpacing * 2, posY + BOX_HEIGHT, BLACK);
        if (tete->suiv != NULL) {
            DrawLine(posX + BOX_WIDTH - 10, posY + BOX_HEIGHT / 2, posX + BOX_WIDTH + 20, posY + BOX_HEIGHT / 2, BLACK);
            DrawTriangle((Vector2){posX + BOX_WIDTH + 20, posY + 30},
                         (Vector2){posX + BOX_WIDTH + 20, posY + BOX_HEIGHT - 30},
                         (Vector2){posX + BOX_WIDTH + 30, posY + BOX_HEIGHT / 2}, BLACK);
        
             DrawLine(posX, posY + BOX_HEIGHT / 2 + 25, posX - 30, posY + BOX_HEIGHT / 2 + 25, BLACK);
     DrawTriangle((Vector2){posX + BOX_WIDTH + 20, posY + 30+25},
             (Vector2){posX + BOX_WIDTH + 10, posY + BOX_HEIGHT / 2 +25},
             (Vector2){posX + BOX_WIDTH + 20, posY + BOX_HEIGHT - 30 +25}, BLACK);
        }
         else {
            
            DrawLine(posX + BOX_WIDTH -10, posY + BOX_HEIGHT / 2, posX + BOX_WIDTH + 30, posY + BOX_HEIGHT / 2, BLACK);
            DrawTriangle((Vector2){posX + BOX_WIDTH + 30, posY + 30},
                         (Vector2){posX + BOX_WIDTH + 30, posY + BOX_HEIGHT - 30},
                         (Vector2){posX + BOX_WIDTH + 40, posY + BOX_HEIGHT / 2}, BLACK);
                         DrawLine(posX, posY + BOX_HEIGHT / 2 + 25, posX - 30, posY + BOX_HEIGHT / 2 + 25, BLACK);
        
         
        
         
        }
        posX += BOX_WIDTH + 40; 

        tete = tete->suiv;
    }
}

int main(void) {
   
    const int screenWidth = 1600;
    const int screenHeight = 850;
liste *head = NULL;
    InitWindow(screenWidth, screenHeight, "doubly linked list");
 SetTargetFPS(60);
    const char* options[MAX_OPTIONS] = { "Create", "Search", "Insert", "Delete", "Sort" };
    int selectedOption = 0;
    bool displayMenu = true;
    bool displayList = false;
     bool returnToMenu = false;
     bool displayinsert=false;
 
    int  numberOfElements= 0;
   bool keyPressed = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (displayMenu) { 
            for (int i = 0; i < MAX_OPTIONS; i++) {
                if (i == selectedOption) {
                    DrawText(TextFormat("> %s", options[i]), screenWidth / 2 - MeasureText(options[i], 30) / 2,
                        screenHeight / 2 - 50 + 40 * i, 30, RED);
                }
                else {
                    DrawText(options[i], screenWidth / 2 - MeasureText(options[i], 30) / 2,
                        screenHeight / 2 - 50 + 40 * i, 30, BLACK);
                }
            }

            if (IsKeyPressed(KEY_DOWN)) {
                selectedOption++;
                if (selectedOption >= MAX_OPTIONS) selectedOption = 0;
            }
            else if (IsKeyPressed(KEY_UP)) {
                selectedOption--;
                if (selectedOption < 0) selectedOption = MAX_OPTIONS - 1;
            }

            if (IsKeyPressed(KEY_ENTER)) {
                if (selectedOption == 0) {
                    displayMenu = false;
                    displayList = true;
                    returnToMenu = true;
                }
                if (selectedOption==1){
                    displayMenu=false;
                    displayList=true;
                    returnToMenu = true;
                   

                }
                if (selectedOption==2){
                    displayMenu=false;
                    displayList=true;
                    returnToMenu = true;
                    displayinsert=true;
                     

                }
                if (selectedOption==3){
                    displayMenu=false;
                    displayList=true;
                    returnToMenu = true;

                }
                if (selectedOption==4){
                    displayMenu=false;
                    displayList=true;
                    returnToMenu = true;

                }
                 else if (selectedOption == 5) {
                    CloseWindow();
                    return 0;
                }
            }
        }
else if (displayList) {
            if (!keyPressed) {
                DrawText("Enter the number of elements (1-9):", 50, 50, 20, BLACK);
                DrawText(TextFormat("Number of elements: %d", numberOfElements), 50, 100, 20, BLACK);
                if (returnToMenu) {
                    DrawText("Press 'M' to return", screenWidth - 240, 20, 20, BLACK);
                }
            }


            for (int key = KEY_ONE; key <= KEY_NINE; key++) {
                if (IsKeyPressed(key)) {
                    numberOfElements = key - KEY_ZERO;
                    keyPressed = true;
                    break;
                }
            }

            if (keyPressed && numberOfElements > 0) {
                if (head != NULL) {
                    free(head);
                    head = NULL;
                }
                create_listebid(&head, numberOfElements);
                displayList = false;
            }

            if (returnToMenu && IsKeyPressed(KEY_M)) {
                displayMenu = true;
                keyPressed = false;
                returnToMenu = true;
            }
        }

        if (!displayMenu && !displayList) {
            drawDoublyLinkedList(head);
        }
        
      if (displayinsert ) {
       
      displayList=true;
      drawDoublyLinkedList(head);
        if (!keyPressed) {
                DrawText("where do you want to insert", screenWidth /4, screenHeight /4, 20, BLACK);
                
                
                DrawText("Press 'A' to add a node to the end of the list", screenWidth / 4 +20, screenHeight / 4+20, 20, BLACK);

        
        if (IsKeyPressed(KEY_A)) {
            ajouterFin(&head, rand() % 100); 
        }
            }
      }   

      

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
