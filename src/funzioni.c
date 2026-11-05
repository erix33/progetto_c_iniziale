#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"

// le macro rendono il codice più mantenibile nel tempo

#define DIMENSIONE_MINIMA_LISTA 4 
#define NUMERO_ELEMENTI_AGGIUNTI 5

/* il preprocessore sostituisce tutte le occorrenze di SLEEP_MS
e in base al sistema operativo sostituisce il valore (il * 1000 è necessario perchè
 la funzione usleep lavora in microsecondi)
*/

#ifdef _WIN32
    #include <Windows.h>
    #define SLEEP_MS(ms) Sleep((DWORD)(ms))
#else
    #include <unistd.h>
    #define SLEEP_MS(ms) usleep((ms) * 1000)
#endif


struct Lista {
    int *data;
    size_t size;
    size_t capacity;
};


Status create_list(size_t capacity, Lista **lista){

    if(lista == NULL) return STATUS_ERR_NULL_PTR;

    Lista *nuova_lista = malloc(sizeof(Lista));

    if(nuova_lista == NULL){
        return STATUS_ERR_ALLC_MEMORY; // perchè è una funzione di tipo Lista*
    }

    /*se la capacita digitata dall'utente dovesse risultare 0 la nostra
    lista avrà una capacità di 4 elementi operatore ternario
    se invece è maggiore di 0 il valore di cap iniziale rimane quello del parametro della 
    funzione
    */

    size_t cap_iniziale = (capacity > 0) ? capacity : DIMENSIONE_MINIMA_LISTA;

    nuova_lista->data = malloc(sizeof(int) * cap_iniziale);

    if(nuova_lista->data == NULL){
        free(nuova_lista);
        return STATUS_ERR_ALLC_MEMORY;
    }

    nuova_lista->capacity = cap_iniziale;
    nuova_lista->size = 0;

    *lista = nuova_lista;

    return STATUS_OK;
}

Status aggiungi_numero_alla_lista(Lista *lista, int numero){

    if(lista == NULL) return STATUS_ERR_NULL_PTR;

    if(lista->capacity == lista->size){
        SLEEP_MS(2000);
        size_t new_capacity = lista->capacity + NUMERO_ELEMENTI_AGGIUNTI;
        int *tmp = realloc(lista->data, sizeof(int) * new_capacity);

        if(tmp == NULL){
            return STATUS_ERR_ALLC_MEMORY;
        }

        lista->data = tmp;
        lista->capacity = new_capacity;
    }

    lista->data[lista->size] = numero;
    lista->size++;

    return STATUS_OK;
}

Status stampa_lista(const Lista *lista){

    if(lista == NULL) return STATUS_ERR_NULL_PTR;

    printf("    ---CONTENUTO DELLA LISTA---\n\n");
    for(size_t i = 0; i < lista->size; i++){
        printf("[%d]\t", lista->data[i]);
    }
    printf("\n\n");

    return STATUS_OK;

}


Status libera_memoria_lista(Lista *lista){

    if(lista == NULL) return STATUS_ERR_NULL_PTR;

    SLEEP_MS(1000);

    free(lista->data);
    lista->data = NULL;

    lista->capacity = 0;
    lista->size = 0;

    free(lista);

    return STATUS_OK;
}


void check_funzione_con_switch(Status stato){

    switch(stato){

        case STATUS_OK:
            break; 

        case STATUS_ERR_ALLC_MEMORY:
            fprintf(stderr, "[CRITICO] Impossibile avviare il programma: RAM esaurita durante la creazione della lista.\n");
            exit(EXIT_FAILURE);

        case STATUS_ERR_NULL_PTR:
            fprintf(stderr, "[BUG] Errore interno: hai passato un doppio puntatore NULL a create_list.\n");
            exit(EXIT_FAILURE);
            
        default:
            fprintf(stderr, "[SCONOSCIUTO] Errore non previsto durante la creazione.\n");
            exit(EXIT_FAILURE);
    }  
}
