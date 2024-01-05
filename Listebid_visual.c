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
/*******SEARCH********8*/
bool recherch(liste *tete ,int var){
liste*p=tete;
while (p!=NULL)
{
    if(p->info=var) {return true;}
   else  {p=p->suiv;}
}
return false;
}
/*******DELET**********/
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


/********SORT***************/
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
/*************************/
int main(void) {
   
    const int screenWidth = 1200;
    const int screenHeight = 650;
liste *head = NULL;
    InitWindow(screenWidth, screenHeight, "doubly linked list");
 SetTargetFPS(60);
      const char* options[MAX_OPTIONS] = { "Create", "Search", "Insert", "Delete", "Sort" };//display main menu 
    int selectedOption = 0;
    int  numberOfElements= 0;
    int newValue; 
     
     // bool variables (flags)
     bool displayMenu = true;
    bool displayList = false;
     bool returnToMenu = false;
     bool displayinsert=false;
     bool displayText=false;
     bool keyPressed = false;
    bool numberAllowed=false;
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
                    displayText = true;
                  }

                 else if (selectedOption == 1) {
                    // Search option
                   DrawText("Search for a value:", 50, 200, 30, RED);
                DrawText("Enter the value to search:", 50, 250, 20, BLACK);
                DrawRectangle(50, 280, 60, 40, LIGHTGRAY);
                DrawText(TextFormat("%d", newValue), 60, 290, 30, BLACK);

                for (int key = KEY_ZERO; key <= KEY_NINE; key++) {
                    if (IsKeyPressed(key)) {
                        newValue = newValue * 10 + (key - KEY_ZERO);
                        break;
                    }
                }

                if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (newValue > 0) {
                        newValue = newValue / 10;
                    }
                }

                DrawText("Press 'Enter' to search", screenWidth - 240, 20, 20, BLACK);
                DrawText("Press 'M' to return to menu", screenWidth - 240, 50, 20, BLACK);

                numberAllowed = true;

                if (IsKeyPressed(KEY_ENTER) && numberAllowed) {
                    bool valueFound = recherch(head, newValue);

                    if (valueFound) {
                        printf("Value %d found in the list!\n", newValue);
                       }
                     else {
                        printf("Value %d not found in the list.\n", newValue);
                       }

                    displayList = false;
                    displayText = false;
                    displayMenu = true;
                    returnToMenu = true;
                    numberAllowed = false;
                   }
             }
                 else if (selectedOption == 2) {
                    // Insert option
                     displayMenu=false;
                    displayList=true;
                    returnToMenu = true;
                    displayinsert=true;
                    displayText=true;
                }
                 else if (selectedOption == 3) {
                    // Delete option
                    DrawText("Delete a node at a specific position:", 50, 200, 30, BLACK);
                DrawText("Enter the position to delete:", 50, 250, 20, RED);
                DrawRectangle(50, 280, 60, 40, LIGHTGRAY);
                DrawText(TextFormat("%d", newValue), 60, 290, 30, BLACK);

                for (int key = KEY_ZERO; key <= KEY_NINE; key++) {
                    if (IsKeyPressed(key)) {
                        newValue = newValue * 10 + (key - KEY_ZERO);
                        break;
                    }
                }

                if (IsKeyPressed(KEY_BACKSPACE)) {
                    if (newValue > 0) {
                        newValue = newValue / 10;
                    }
                }

                DrawText("Press 'Enter' to delete", screenWidth - 240, 20, 20, BLACK);
                DrawText("Press 'M' to return to menu", screenWidth - 240, 50, 20, BLACK);

                numberAllowed = true;

                if (IsKeyPressed(KEY_ENTER) && numberAllowed) {
                    delet(&head, newValue);

                    displayList = false;
                    displayText = false;
                    displayMenu = true;
                    returnToMenu = true;
                    numberAllowed = false;
                }
          }
                 else if (selectedOption == 4) {
                    // Sort option
                     DrawText("Sort the doubly linked list:", 50, 200, 30, BLACK);
                DrawText("Press 'Enter' to sort", screenWidth - 240, 20, 20, BLACK);
                DrawText("Press 'M' to return to menu", screenWidth - 240, 50, 20, BLACK);

                if (IsKeyPressed(KEY_ENTER)) {
                    Sorting(head);
                    displayList = false;
                    displayText = false;
                    displayMenu = true;
                    returnToMenu = true;
                }
            }
            else if (selectedOption == 5) {
                    CloseWindow();
                    return 0;
                }
            }
        
        //*******************// flags conditions
else if (displayList) {
           displayText=true; //the enter text appear
           
 if (!returnToMenu) {
                           DrawText("Press 'M' to return", screenWidth - 240, 20, 20, BLACK);
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
            displayText=false;
            displayinsert=false;
            }
        }

        if (!displayMenu && !displayList) {
            drawDoublyLinkedList(head);
        }
        


        if (displayText) {//drawing text "enter number of elmnts"

        numberAllowed=false;
            
                DrawText("Enter the number of elements (1-9):", 50, 50, 20, BLACK);
                DrawText(TextFormat("Number of elements: %d", numberOfElements), 50, 100, 20, BLACK);
                if (returnToMenu) {
                    DrawText("Press 'M' to return", screenWidth - 240, 20, 20, BLACK);
                }
            
        }
        
      if (displayinsert ) {
        returnToMenu=true;
       if (!numberAllowed){
        DrawText("Where do you want to insert?", 50, 300, 20, BLACK);
    DrawText("Press 'A' for the beginning", 50, 330, 20, BLACK);
    DrawText("Press 'B' for the end", 50, 360, 20, BLACK);
    DrawText("Press 'C' for a random position", 50, 390, 20, BLACK);
    
    DrawText("Enter the number to insert (0-9999999):", 50, 440, 20, BLACK);
    DrawRectangle(50, 470, 60, 40, LIGHTGRAY);
    DrawText(TextFormat("%d",newValue), 60, 480, 30, BLACK);
    int digitCount = 0;
    for (int key = KEY_ZERO; key <= KEY_NINE; key++) {
                if (IsKeyPressed(key)) {
                    int keyPressedValue = key - KEY_ZERO;
                    if (digitCount < 7) { // Allowing up to 7 digits (0 to 9999999)
                        newValue= newValue * 10 + keyPressedValue;
                        digitCount++;
                    }
                    break;
                }
                if (IsKeyPressed(KEY_BACKSPACE)) {// THE ABILITY TO DELETE A WRONG NUMBER PRESSE
    
    if (newValue > 0) {
        newValue = newValue / 10;
    }
}
            }
       }
     
    
if (IsKeyPressed(KEY_A)) {
       numberAllowed=true;
        ajouterDebut(&head,newValue );
        
    } else if (IsKeyPressed(KEY_B)) {
        numberAllowed=true;
       
        
        ajouterFin(&head, newValue);
        
    } else if (IsKeyPressed(KEY_C)) {
      
         numberAllowed=true;
        
        
        ajouterPosition(&head, newValue, rand() % 8 + 2);// random position from 2 to 9
        
    }


      }   

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

