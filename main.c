#include "function.h"

int main(int argc, char *argv[])
{
    // Inizializzazione del SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        printf("Errore nella apertura di sdl stream \n");
        return 1;
    }

    // Creazione della finestra (window) SDL
    SDL_Window *window = SDL_CreateWindow(
        "Superficie a Livelli Terreni Vinicoli",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SIZE_W,
        SIZE_W,
        SDL_WINDOW_SHOWN
    );

    // Controllo sulla finestra
    if (window == NULL){
        printf("Errore in apertura della finestra \n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Creazione dell'oggetto di render
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // Controllo sull'oggetto
    if(renderer == NULL){
        printf("Errore nella creazione del oggetto di render \n");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Creazione dei dati nel file CSV
    // createFileCSV();

    // Alloco lo spazio necessario per poter rappresentare i punti della superficie di livello 400x400
    int number_points = MAX_POINTS;
    Point *sup = malloc(number_points*sizeof(Point));
    Point *plane = malloc(number_points*sizeof(Point));

    // Leggo / Riempio l'array con i dati necessari per descrivere i punti
    readFileCSV(sup);

    // Creazione di un evento in ambiente SDL
    SDL_Event event;

    // Condizione ciclo while
    int running = 1;


    // Ciclo per mostrare la finestra
    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                printf("Chiusura del programma \n");
                running = 0;
            }
        }

        // Impostato il colore di sfondo
        SDL_SetRenderDrawColor(renderer, 0,0,0,255);

        // Comando utile ad pulire il BUFFER dal frame passato 
        SDL_RenderClear(renderer);

        // Presente il BUFFER aggiornato con il nuovo frame
        SDL_RenderPresent(renderer);
    }

    // "Distruzione" della finestra e del oggetto render
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    // Deallocamento memoria array
    free(sup);
    return 0;
}