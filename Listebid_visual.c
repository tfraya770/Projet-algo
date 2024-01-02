#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include<stdbool.h>
#include "raylib.h"
#define MAX_OPTIONS 6
#define BOX_WIDTH 60
#define BOX_HEIGHT 40
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
void drawDoublyLinkedList(liste *tete) {
    int posX = 100;
    int posY = 200;
    while (tete != NULL) {
        DrawRectangle(posX, posY, BOX_WIDTH, BOX_HEIGHT, PINK);
        DrawRectangleLines(posX, posY, BOX_WIDTH, BOX_HEIGHT, BLACK);
        DrawText(TextFormat("%d", tete->info), posX + 10, posY + 10, 20, BLACK);
        if (tete->suiv != NULL) {
            DrawLine(posX + BOX_WIDTH, posY + BOX_HEIGHT / 2, posX + BOX_WIDTH + 20, posY + BOX_HEIGHT / 2, BLACK);
            DrawTriangle((Vector2){posX + BOX_WIDTH + 20, posY + 5},
                         (Vector2){posX + BOX_WIDTH + 20, posY + BOX_HEIGHT - 5},
                         (Vector2){posX + BOX_WIDTH + 30, posY + BOX_HEIGHT / 2}, BLACK);
        }
        posX += BOX_WIDTH + 40; // Adjust for spacing between boxes

        tete = tete->suiv;
    }
}
/***************8*/
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
/*****************/
int main(void) {
   
    const int screenWidth = 1200;
    const int screenHeight = 650;
liste *head = NULL;
    InitWindow(screenWidth, screenHeight, "doubly linked list");
 SetTargetFPS(60);
    const char* options[MAX_OPTIONS] = { "Create", "Search", "Insert", "Delete", "Sort" };
    int selectedOption = 0;
    bool displayMenu = true;
    bool displayList = false;
     bool returnToMenu = false;

    int  numberOfElements= 0;
   bool keyPressed = false;
/*****************/
bool search;
int vaSearch;
/******************/
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
                /**********************/
                else if (selectedOption == 1) {
                    displayMenu = false;
                    displayList = true;
                    returnToMenu = true;
                     printf("Enter the value to search: ");
                     scanf("%d", &vaSearch);
                    search=recherch(head ,vaSearch);
                }
                /*************************/
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
            
            

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
