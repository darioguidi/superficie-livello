#include "function.h"

// GESTIONE SUPERIFICIE CURVICA
// Funzione per generare i punti della superifcie in un file CSV
void createFileCSV()
{
    FILE *file = fopen("data.csv", "w");
    if (file == NULL) {
        printf("Errore nell'apertura del file.\n");
        return;
    }

    int half_grid = SIZE_GRID / 2;

    // Possiamo variare la densità dei punti, modificando l'aumento stesso della variabile
    for (int y = -half_grid; y < half_grid; y+=5) {
        for (int x = -half_grid; x < half_grid; x+=5) {
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
        point.y = atof(strtok(NULL, ","));
        point.z = atof(strtok(NULL, ","));

        // Aggiunta del punto in memoria - array
        sup[i]=point;
        i++;
    }

    // Implmementare lettura di una riga 
    fclose(file);
}

void printPoint(SDL_Renderer *renderer, Point point, float theta, float phi)
{
    if (point.z + DISTANCE <= 0) return;

    // Applichiamo rotazione Y (theta)
    float rad_theta = theta * PI / 180.0;
    float rad_phi = phi * PI / 180.0;

    float x1 = point.x * cos(rad_theta) - point.z * sin(rad_theta);
    float z1 = point.x * sin(rad_theta) + point.z * cos(rad_theta);

    // Applichiamo rotazione X (phi)
    float y1 = point.y * cos(rad_phi) - z1 * sin(rad_phi);
    float z2 = point.y * sin(rad_phi) + z1 * cos(rad_phi);

    if (z2 + DISTANCE <= 0) return;

    // Proiezione prospettica
    int xp = x1 * (DISTANCE / (z2 + DISTANCE)) + OFFSET_X;
    int yp = y1 * (DISTANCE / (z2 + DISTANCE)) + OFFSET_Y;

    SDL_Rect rect = {xp, yp, SIZE_POINT, SIZE_POINT};

    if(yp<100){
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    }else{
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    }
    SDL_RenderFillRect(renderer, &rect);
}

void printPointsSuperficie(SDL_Renderer *renderer, Point *sup, float theta, float phi)
{
    for (int i=0; i < MAX_POINTS; i++){
        printPoint(renderer, sup[i], theta, phi);
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
            plane[index] = (Point){x, half_grid+50, z};
            index++;
        }
    }
}

// Funzione per la stampa dei punti del piano
void printPointsPiano(SDL_Renderer *renderer, Point *plane, float theta, float phi)
{
    for (int i=0; i < MAX_POINTS; i++){
        printPointPlane(renderer, plane[i], theta, phi);
    }  
}

// Stampa singolo punto del piano
void printPointPlane(SDL_Renderer *renderer, Point point, float theta, float phi)
{
    // Converti gli angoli in radianti
    float rad_theta = theta * PI / 180.0f;
    float rad_phi = phi * PI / 180.0f;

    // Rotazione attorno all'asse Y (theta)
    float x1 = point.x * cos(rad_theta) - point.z * sin(rad_theta);
    float z1 = point.x * sin(rad_theta) + point.z * cos(rad_theta);

    // Rotazione attorno all'asse X (phi)
    float y1 = point.y * cos(rad_phi) - z1 * sin(rad_phi);
    float z2 = point.y * sin(rad_phi) + z1 * cos(rad_phi);

    if (z2 + DISTANCE <= 0) return;

    // Proiezione prospettica
    int xp = x1 * (DISTANCE / (z2 + DISTANCE)) + OFFSET_X;
    int yp = y1 * (DISTANCE / (z2 + DISTANCE)) + OFFSET_Y;

    SDL_Rect rect = {xp, yp, SIZE_POINT, SIZE_POINT};
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}



