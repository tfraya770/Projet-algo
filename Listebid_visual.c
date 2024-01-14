#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "raylib.h"
#include <stdbool.h>

#define MAX_OPTIONS 5 // menu options
#define BOX_WIDTH 120 // to define the width of the box to be drawn
#define BOX_HEIGHT 80 // to define the height of the box to be drawn

// liste structure
typedef struct liste liste;
struct liste
{
    int info;
    liste *pred;
    liste *suiv;
} cellule;

  //******************//
  void create_listebid(liste **tete, int nbElmt)
{
    liste *Q = NULL;
    liste *nouv = NULL;
    *tete = NULL;

    for (int i = 0; i < nbElmt; i++)
    {
        nouv = (liste *)malloc(sizeof(liste));

        if (nouv == NULL)
        {
            printf("Memory allocation failed");
            exit(1);
        }

        nouv->pred = NULL;
        nouv->suiv = NULL;
        nouv->info = rand() % 100; // random numbers as info of nodes

        if (*tete == NULL)
        {
            *tete = nouv;
        }
        else
        {
            Q->suiv = nouv;
            nouv->pred = Q;
        }
        Q = nouv;
    }
    if (Q != NULL)
    {
        Q->suiv = NULL;
    }
}
//**************************//
/*void affiche_listebid(liste *tete)
{
    liste *p = tete;
    while (p != NULL)
    {
        printf("%d ", p->info);
        p = p->suiv;
    }
}*/


//******************//
void ajouterDebut(liste **tete, int val)
{
    liste *nouv = NULL;
    nouv = malloc(sizeof(liste));
    if (nouv == NULL)
    {
        printf("Memory allocation failed");
        exit(1);
    }
    nouv->info = val;
    nouv->pred = NULL;
    nouv->suiv = *tete;

    if (*tete != NULL)
    {
        (*tete)->pred = nouv;
    }

    *tete = nouv;
}



//*****************************//
void ajouterFin(liste **tete, int val)
{
    liste *nouv = malloc(sizeof(liste));
    liste *temp = NULL;
    nouv->info = val;
    nouv->suiv = NULL;
    nouv->pred = NULL;

    if (*tete == NULL)
    {
        *tete = nouv;
    }
    else
    {
        temp = *tete;
        while (temp->suiv != NULL)
        {
            temp = temp->suiv;
        }
        temp->suiv = nouv;
        nouv->pred = temp;
    }
}


//***************************//
void ajouterPosition(liste **tete, int val, int position)
{
    liste *nouv = NULL;
    nouv = malloc(sizeof(liste));
    nouv->info = val;
    nouv->suiv = NULL;
    nouv->pred = NULL;

    if (position <= 1)
    {
        nouv->suiv = *tete;
        (*tete)->pred = nouv;
        *tete = nouv;
    }
    else
    {
        liste *temp = *tete;
        int count = 1;
        while (count < position - 1 && temp->suiv != NULL)
        {
            temp = temp->suiv;
            count++;
        }
        if (count == position - 1)
        {
            nouv->suiv = temp->suiv;
            if (temp->suiv != NULL)
            {
                temp->suiv->pred = nouv;
            }
            temp->suiv = nouv;
            nouv->pred = temp;
        }
    }
}
//*************************//
void drawDoublyLinkedList(liste *tete)
{
    // positioning x and y to start the drawing from there
    int posX = 100;
    int posY = 200;
    int lineSpacing = BOX_WIDTH / 3; // spacing between lines
    while (tete != NULL)
    {
        DrawRectangle(posX, posY, BOX_WIDTH, BOX_HEIGHT, BLUE);// nodes drawn as boxes (rectangles)
        DrawRectangleLines(posX, posY, BOX_WIDTH, BOX_HEIGHT, BLACK);// vertical lines of the box
        DrawText(TextFormat("%d", tete->info), posX + 40, posY + 30, 25, BLACK); // dispaly info

        // vertical lines that represents the previous and the next inside the node
        DrawLine(posX + lineSpacing, posY, posX + lineSpacing, posY + BOX_HEIGHT, BLACK);
        DrawLine(posX + lineSpacing * 2, posY, posX + lineSpacing * 2, posY + BOX_HEIGHT, BLACK);

        if (tete->suiv != NULL)
        {
            // next arrows
            DrawLine(posX + BOX_WIDTH - 10, posY + BOX_HEIGHT / 2, posX + BOX_WIDTH + 20, posY + BOX_HEIGHT / 2, BLACK);
            DrawTriangle((Vector2){posX + BOX_WIDTH + 20, posY + 30},
                         (Vector2){posX + BOX_WIDTH + 20, posY + BOX_HEIGHT - 30},
                         (Vector2){posX + BOX_WIDTH + 30, posY + BOX_HEIGHT / 2}, BLACK);

            // previous arrows
            DrawLine(posX, posY + BOX_HEIGHT / 2 + 25, posX - 30, posY + BOX_HEIGHT / 2 + 25, BLACK);
            DrawTriangle((Vector2){posX + BOX_WIDTH + 20, posY + 30 + 25},
                         (Vector2){posX + BOX_WIDTH + 10, posY + BOX_HEIGHT / 2 + 25},
                         (Vector2){posX + BOX_WIDTH + 20, posY + BOX_HEIGHT - 30 + 25}, BLACK);
        }
        else
        {
            // arrows of the last node
            DrawLine(posX + BOX_WIDTH - 10, posY + BOX_HEIGHT / 2, posX + BOX_WIDTH + 30, posY + BOX_HEIGHT / 2, BLACK);
            DrawTriangle((Vector2){posX + BOX_WIDTH + 30, posY + 30},
                         (Vector2){posX + BOX_WIDTH + 30, posY + BOX_HEIGHT - 30},
                         (Vector2){posX + BOX_WIDTH + 40, posY + BOX_HEIGHT / 2}, BLACK);
            DrawLine(posX, posY + BOX_HEIGHT / 2 + 25, posX - 30, posY + BOX_HEIGHT / 2 + 25, BLACK);
        }
        posX += BOX_WIDTH + 40;

        tete = tete->suiv;
    }
}



//****************************//
void SortingWithAnimation(liste *tete)
{ // highlights the nodes that are being compared it's used instead of sort to show the animation effect
    liste *p;
    liste *q;
    int x;        // temp for values
    bool swapped; // to check if there was a swapping

    if (tete != NULL)
    {
        p = tete;
        while (p->suiv != NULL)
        {
            q = p->suiv;
            swapped = false;

            while (q != NULL)
            {
                if (q->info < p->info)
                {
                    x = p->info;
                    p->info = q->info;
                    q->info = x;
                    swapped = true;
                }
                q = q->suiv;

                // draw the list after each swap
                BeginDrawing();
                ClearBackground(RAYWHITE);
                Highlightsort(tete, p, q);
                EndDrawing();

                usleep(1000000); // delays between each swap
            }

            if (!swapped)
            {
                break; // If no elements were swapped, the list is already sorted
            }

            p = p->suiv;
        }
    }
}




//*************************//
void Highlightsort(liste *tete, liste *p, liste *q)
{ // highlighting the boxes to show the sorting actions
    int posX = 100;
    int posY = 200;
    int lineSpacing = BOX_WIDTH / 3;
    while (tete != NULL)
    {
        if (tete == p || tete == q)
        {
            DrawRectangle(posX, posY, BOX_WIDTH, BOX_HEIGHT, YELLOW); // Highlight the nodes being compared to (p and q) with yellow
        }
        else
        {
            DrawRectangle(posX, posY, BOX_WIDTH, BOX_HEIGHT, BLUE);
        }

        DrawRectangleLines(posX, posY, BOX_WIDTH, BOX_HEIGHT, BLACK);
        DrawText(TextFormat("%d", tete->info), posX + 40, posY + 30, 25, BLACK); // Display info

        DrawLine(posX + lineSpacing, posY, posX + lineSpacing, posY + BOX_HEIGHT, BLACK);
        DrawLine(posX + lineSpacing * 2, posY, posX + lineSpacing * 2, posY + BOX_HEIGHT, BLACK);

        if (tete->suiv != NULL)
        {
            {
                DrawLine(posX + BOX_WIDTH - 10, posY + BOX_HEIGHT / 2, posX + BOX_WIDTH + 20, posY + BOX_HEIGHT / 2, BLACK);
                DrawTriangle((Vector2){posX + BOX_WIDTH + 20, posY + 30},
                             (Vector2){posX + BOX_WIDTH + 20, posY + BOX_HEIGHT - 30},
                             (Vector2){posX + BOX_WIDTH + 30, posY + BOX_HEIGHT / 2}, BLACK);
            }
        }
        else
        {
            DrawLine(posX + BOX_WIDTH - 10, posY + BOX_HEIGHT / 2, posX + BOX_WIDTH + 30, posY + BOX_HEIGHT / 2, BLACK);
            DrawTriangle((Vector2){posX + BOX_WIDTH + 30, posY + 30},
                         (Vector2){posX + BOX_WIDTH + 30, posY + BOX_HEIGHT - 30},
                         (Vector2){posX + BOX_WIDTH + 40, posY + BOX_HEIGHT / 2}, BLACK);
        }

        posX += BOX_WIDTH + 40;
        tete = tete->suiv;
    }
}




//****************************//
void delet(liste **tete, int pos)
{
    liste *p;
    p = *tete;
    if (pos == 1)
    {

        *tete = p->suiv;
        if (p->suiv != NULL)
        {
            p->suiv->pred = NULL;
        }
        free(p);
    }
    else
    {
        while (p != NULL && pos != 1)
        {
            p = p->suiv;
            pos = pos - 1;
        }
        if (pos == 1)
        {
            (p->pred)->suiv = p->suiv;
            (p->suiv)->pred = p->pred;
            free(p);
        }
    }
}




/********SEARCH*****************/
bool recherch(liste *tete, int var)
{
    liste *p = tete;
    while (p != NULL)
    {
        if (p->info == var)
        {
            return true;
        }
        else
        {
            p = p->suiv;
        }
    }
    return false;
}




/**********SORTING***********************/
/*void Sorting(liste *tete)
{
    liste *p;
    liste *q;
    int x;
    if (tete != NULL)
    {
        p = tete;
        while ((p->suiv) != NULL)
        {
            q = p->suiv;
            while ((q != NULL))
            {
                if ((q->info) < (p->info))
                {
                    x = p->info;
                    p->info = q->info;
                    q->info = x;
                }
                q = q->suiv;
            }
            p = p->suiv;
        }
    }
}*/




 //*********************************MAIN*******************************//


int main(void)
{
    // window dimensions
    const int screenWidth = 1600;
    const int screenHeight = 850;
    liste *head = NULL;
    InitWindow(screenWidth, screenHeight, "doubly linked list"); // window title

    SetTargetFPS(60);
    const char *options[MAX_OPTIONS] = {"Create", "Search", "Insert", "Delete", "Sort"}; // display main menu
    
    //int variables
    int selectedOption = 0;
    int numberOfElements = 0;
    int newValue;
    int deletePosition = 0;
    int searchValue = 0;
    // bool variables (flags)
    bool displayMenu = true;
    bool displayList = false;
    bool returnToMenu = false;
    bool displayinsert = false;
    bool displayText = false;
    bool keyPressed = false;
    bool numberAllowed = false;
    bool displaydelet = false;
    bool displaysearch = false;
    bool valueFound;
    bool displaySearchResult = false;
    bool displaySort = false;


//*********************************//
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (displayMenu)
        {
            for (int i = 0; i < MAX_OPTIONS; i++)
            {
                if (i == selectedOption)
                { 
                    //highlighting the selected option in red
                    DrawText(TextFormat("> %s", options[i]), screenWidth / 2 - MeasureText(options[i], 30) / 2,
                             screenHeight / 2 - 50 + 40 * i, 30, RED);
                }
                else
                { // the non-selected options are in black
                    DrawText(options[i], screenWidth / 2 - MeasureText(options[i], 30) / 2,
                             screenHeight / 2 - 50 + 40 * i, 30, BLACK);
                }
            }
            // navigating through menu options by keyboard
            if (IsKeyPressed(KEY_DOWN))
            {
                selectedOption++;
                if (selectedOption >= MAX_OPTIONS)
                    selectedOption = 0;
            }
            else if (IsKeyPressed(KEY_UP))
            {
                selectedOption--;
                if (selectedOption < 0)
                    selectedOption = MAX_OPTIONS - 1;
            }
            // if the user presses ENTER to slect an option
            if (IsKeyPressed(KEY_ENTER))
            {
                if (selectedOption == 0)
                { // create
                    displayMenu = false;
                    displayList = true;
                    returnToMenu = true;
                    displayText = true;
                }
                if (selectedOption == 1)
                { // search
                    displayMenu = false;
                    displayList = true;
                    returnToMenu = true;
                    displayText = true;
                    displaysearch = true;
                }
                if (selectedOption == 2)
                { // insert
                    displayMenu = false;
                    displayList = true;
                    returnToMenu = true;
                    displayinsert = true;
                    displayText = true;
                }
                if (selectedOption == 3)
                { // delete
                    displayMenu = false;
                    displayList = true;
                    returnToMenu = true;
                    displaydelet = true;
                    displayText = true;
                }
                if (selectedOption == 4)
                { // sort
                    displayMenu = false;
                    displayList = true;
                    returnToMenu = true;
                    displayText = true;
                    displaySort = true;
                }

                else if (selectedOption == 5)
                {
                    CloseWindow();
                    return 0;
                }
            }
        }

        //*******************// flags conditions
        else if (displayList)
        {
            displayText = true; // the enter text appear

            if (!returnToMenu)
            {
                DrawText("Press 'M' to return", screenWidth - 240, 20, 20, BLACK);
            }
            //inputs from 1 to 9 from keyboard
            for (int key = KEY_ONE; key <= KEY_NINE; key++)
            {
                if (IsKeyPressed(key))
                {
                    numberOfElements = key - KEY_ZERO;
                    keyPressed = true;
                    break;
                }
            }

            if (keyPressed && numberOfElements > 0)
            {
                if (head != NULL)
                {
                    free(head);
                    head = NULL;
                }
                create_listebid(&head, numberOfElements);//creating the list with number pressed by keyboard
                displayList = false;
            }
           // returningto menu if "m"or "M" is pressed
            if (returnToMenu && IsKeyPressed(KEY_M))
            {
                displayMenu = true;
                keyPressed = false;
                returnToMenu = true;
                displayText = false;
                displayinsert = false;
                displaysearch = false;
                displaydelet = false;
                displaySort = false;
            }
        }

        if (!displayMenu && !displayList)
        {
            drawDoublyLinkedList(head);
        }

        if (displayText)
        { // drawing text "enter number of elmnts" in all the options selected

            numberAllowed = false;

            DrawText("Enter the number of elements (1-9):", 50, 50, 20, BLACK);
            DrawText(TextFormat("Number of elements: %d", numberOfElements), 50, 100, 20, BLACK);
            if (returnToMenu)
            {
                DrawText("Press 'M' to return", screenWidth - 240, 20, 20, BLACK);
            }
        }
        if (displayinsert)
        {
            returnToMenu = true;
            if (!numberAllowed)
            { //inserting option 
                DrawText("Where do you want to insert?", 50, 300, 20, BLACK);
                DrawText("Press 'A' for the beginning", 50, 330, 20, BLACK);
                DrawText("Press 'B' for the end", 50, 360, 20, BLACK);
                DrawText("Press 'C' for a random position", 50, 390, 20, BLACK);

                DrawText("Enter the number to insert (0-9999999):", 50, 440, 20, BLACK);
                DrawRectangle(50, 470, 60, 40, LIGHTGRAY);
                DrawText(TextFormat("%d", newValue), 60, 480, 30, BLACK);
                int digitCount = 0;
                //iputs from keyboard
                for (int key = KEY_ZERO; key <= KEY_NINE; key++)
                {
                    if (IsKeyPressed(key))
                    {
                        int keyPressedValue = key - KEY_ZERO;
                        if (digitCount < 7)
                        { // Allowing up to 7 digits (0 to 9999999)
                            newValue = newValue * 10 + keyPressedValue;
                            digitCount++;
                        }
                        break;
                    }
                    if (IsKeyPressed(KEY_BACKSPACE))
                    { // THE ABILITY TO DELETE A WRONG NUMBER PRESSED

                        if (newValue > 0)
                        {
                            newValue = newValue / 10;
                        }
                    }
                }
            }
            // implementing insterting options depending on the key pressed 
            if (IsKeyPressed(KEY_A))
            {
                numberAllowed = true;
                ajouterDebut(&head, newValue);
            }
            else if (IsKeyPressed(KEY_B))
            {
                numberAllowed = true;

                ajouterFin(&head, newValue);
            }
            else if (IsKeyPressed(KEY_C))
            {

                numberAllowed = true;

                ajouterPosition(&head, newValue, rand() %9 + 1); // random position from 1 to 9
            }
        }

        if (displaydelet)
        {

            if (!numberAllowed)
            {

                DrawText("Delete a node at a specific position:", 50, 300, 20, BLACK);
                DrawText("Enter the position to delete:", 50, 330, 20, RED);
                DrawRectangle(50, 500, 60, 40, LIGHTGRAY);
                DrawText(TextFormat("%d", deletePosition), 60, 520, 30, BLACK);
//input the position for keyboard
                for (int key = KEY_ZERO; key <= KEY_NINE; key++)
                {
                    if (IsKeyPressed(key))
                    {
                        deletePosition = deletePosition * 10 + (key - KEY_ZERO);
                        break;
                    }
                }

                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    if (deletePosition > 0)
                    {
                        deletePosition = deletePosition / 10;
                    }
                }
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                numberAllowed = true;
                delet(&head, deletePosition);
            }
        }
        if (displaysearch)
        {

            if (!numberAllowed) //entering the value
            {
                DrawText("Search for a value:", 50, 300, 30, BLACK);
                DrawText("Enter the value to search:", 50, 330, 20, BLACK);
                DrawRectangle(50, 360, 60, 40, LIGHTGRAY);
                DrawText(TextFormat("%d", searchValue), 60, 370, 30, BLACK);

                for (int key = KEY_ZERO; key <= KEY_NINE; key++)
                {
                    if (IsKeyPressed(key))
                    {
                        searchValue = searchValue * 10 + (key - KEY_ZERO);
                        break;
                    }
                }

                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    if (searchValue > 0)
                    {
                        searchValue = searchValue / 10;
                    }
                }
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                numberAllowed = true;
                valueFound = recherch(head, searchValue);
                displaySearchResult = true;
            }
        }
        if (displaySearchResult)
        {// displaying if the value was found on the list or not
            if (valueFound == true)
            {
                DrawText(TextFormat("Value %d found in the list!\n", searchValue), 50, 500, 50, GREEN);
            }
            else
            {
                DrawText(TextFormat("Value %d not found in the list.\n", searchValue), 50, 500, 50, RED);
            }
        }

        if (displaySort)
        {
            if (!numberAllowed)
            {
                DrawText("Sort the doubly linked list:", 50, 400, 30, BLACK);
            }

            if (IsKeyPressed(KEY_ENTER))
            {
                numberAllowed = true;
                SortingWithAnimation(head);// calling the sorting fonction that does the animation
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}