#include "function.h"

void createFileCSV()
{
    FILE *file = fopen("data.csv", "w");
    if (file == NULL) {
        printf("Errore nell'apertura del file.\n");
    }

    for (int y = 0; y < SIZE_GRID; y++) {
        for (int x = 0; x < SIZE_GRID; x++) {
            // Calcolo z come funzione di x e y
            double z = 100 * sin(0.05 * x) * cos(0.05 * y);
            fprintf(file, "%d,%d,%.2f\n", x, y, z);
        }
    }

    fclose(file);
    printf("File data.csv generato con successo!\n");
}

void readFileCSV(Point *sup)
{
    // Puntatore al file
    FILE *file = fopen("data.csv", "r");
    char buffer[1024];

    // Controllo apertura del file
    if(file==NULL){printf("Errore in apertura del file");}

    // Variabile per riempire l'array di punti con i dati del CSV
    int i=0;

    // Implementare lista dinamica
    while(fgets(buffer, 1024, file)){
        Point point;

        if (i >= MAX_POINTS) {
            printf("Attenzione: raggiunto il massimo numero di punti (%d)\n", MAX_POINTS);
            break;
        }

        // Creazione di un Point
        char *token = strtok(buffer, ",");
        point.x = atof(token);
        point.y = SIZE_W - atof(strtok(NULL, ","));
        point.z = atof(strtok(NULL, ","));

        // Aggiunta del punto in memoria - array
        sup[i]=point;
        i++;
    }

    // Implmementare lettura di una riga 
    fclose(file);
}

void printPoint(SDL_Renderer *renderer, Point point)
{

    if (point.z + DISTANCE <= 0) return;

    // Trasformazioni 
    int x = point.x*(DISTANCE/(point.z+DISTANCE))+OFFSET_X;
    int y = point.y*(DISTANCE/(point.z+DISTANCE))+OFFSET_Y;

    // Crea un rettangolo in posizione (x.y) con dimensioni definite dalla costante SIZE_POINT
    SDL_Rect rect = {x, y, SIZE_POINT, SIZE_POINT};
    // Colore del rettangolo
    SDL_SetRenderDrawColor(renderer, 255,255,255,255);
    // Disegna il rettangolo
    SDL_RenderFillRect(renderer, &rect);
}


void printPointsSuperficie(SDL_Renderer *renderer, Point *sup)
{
    for (int i=0; i < MAX_POINTS; i++){
        printPoint(renderer, sup[i]);
    }
}


// GESTIONE PIANO 2D
// Funzione per generare i punti del piano
void generatePlane(Point *plane)
{
    int half_grid = SIZE_GRID / 2;
    int index = 0;

    for (int z = -half_grid; z < half_grid; z++) {
        for (int x = -half_grid; x < half_grid; x++) {
            plane[index] = (Point){x, 0, z};
            index++;
        }
    }
}

// Funzione per la stampa dei punti del piano
void printPointsPiano(SDL_Renderer *renderer, Point *plane)
{
    for (int i=0; i < MAX_POINTS; i++){
        printPointPlane(renderer, plane[i]);
    }  
}

// Stampa singolo punto del piano
void printPointPlane(SDL_Renderer *renderer, Point point)
{
    if (point.z + DISTANCE <= 0) return;

    // Trasformazioni 
    int x = point.x*(DISTANCE/(point.z+DISTANCE))+OFFSET_X;
    int y = point.y*(DISTANCE/(point.z+DISTANCE))+OFFSET_Y;

    // Crea un rettangolo in posizione (x.y) con dimensioni definite dalla costante SIZE_POINT
    SDL_Rect rect = {x, y, SIZE_POINT, SIZE_POINT};
    // Colore del rettangolo
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    // Disegna il rettangolo
    SDL_RenderFillRect(renderer, &rect);
}


