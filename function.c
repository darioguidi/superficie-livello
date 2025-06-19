#include "function.h"

void readFileCSV()
{
    // Puntatore al file
    FILE *file = fopen("data.csv", "r");
    char buffer[1024];

    if(file==NULL){printf("Errore in apertura del file"); return 1;}

    // Puntatore di testa
    Point *head = malloc(sizeof(Point));

    // Implementare lista dinamica
    while(fgets(buffer, 1024, file)){
        Point point;

        // Creazione di un Point
        char *token = strtok(buffer, ",");
        point.x = *token;
        point.y = *(strtok(NULL, ","));
        point.y = *(strtok(NULL, ","));
    }

    // Implmementare lettura di una riga 
    fclose(file);

    // Ritorna testa della lista
    return head;
}

void addPoint(Point *point)
{

}
