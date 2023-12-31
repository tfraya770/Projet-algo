#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "raylib.h"
#define MAX_OPTIONS 5
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

int main(void) {
   
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "doubly linked list");

    const char* options[MAX_OPTIONS] = { "Create", "Search", "Insert", "Delete", "Sort" };
    int selectedOption = 0;
    bool displayMenu = true;

    int inputNumber = 0;
    bool enteringNumber = false;

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
                    enteringNumber = true;
                }
            }
        }

        if (enteringNumber) {
            const int boxSize = 100;
            const int boxX = screenWidth / 2 - boxSize / 2;
            const int boxY = screenHeight / 2 - boxSize / 2;
            const int textSize = 20;

            
            DrawText("Enter the number of elements:", screenWidth / 2 - MeasureText("Enter the number of elements:", textSize) / 2,
                     boxY - 30, textSize, BLACK);

            DrawRectangle(boxX, boxY, boxSize, boxSize, BLUE);

           
            int key = GetKeyPressed();
            if (key >= KEY_ZERO && key <= KEY_NINE) {
                inputNumber = inputNumber * 10 + (key - KEY_ZERO);
            }

            
            DrawText(TextFormat("%d", inputNumber), boxX + boxSize / 2 - MeasureText(TextFormat("%d", inputNumber), 40) / 2,
                     boxY + boxSize / 2 - 20, 40, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
