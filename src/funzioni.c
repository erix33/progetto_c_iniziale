#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"

#define DIMENSIONE_MINIMA_LISTA 4 
#define NUMERO_ELEMENTI_AGGIUNTI 5

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

Status create_list(size_t capacity, Lista **lista) {
    if (lista == NULL) return STATUS_ERR_NULL_PTR;

    Lista *nuova_lista = malloc(sizeof(Lista));
    if (nuova_lista == NULL) {
        return STATUS_ERR_ALLC_MEMORY;
    }

    size_t cap_iniziale = (capacity > 0) ? capacity : DIMENSIONE_MINIMA_LISTA;
    nuova_lista->data = malloc(sizeof(int) * cap_iniziale);

    if (nuova_lista->data == NULL) {
        free(nuova_lista);
        return STATUS_ERR_ALLC_MEMORY;
    }

    nuova_lista->capacity = cap_iniziale;
    nuova_lista->size = 0;

    *lista = nuova_lista;
    return STATUS_OK;
}

Status aggiungi_numero_alla_lista(Lista *lista, int numero) {
    if (lista == NULL) return STATUS_ERR_NULL_PTR;

    if (lista->capacity == lista->size) {
        SLEEP_MS(500);
        size_t new_capacity = lista->capacity + NUMERO_ELEMENTI_AGGIUNTI;
        int *tmp = realloc(lista->data, sizeof(int) * new_capacity);

        if (tmp == NULL) {
            return STATUS_ERR_ALLC_MEMORY;
        }

        lista->data = tmp;
        lista->capacity = new_capacity;
    }

    lista->data[lista->size] = numero;
    lista->size++;

    return STATUS_OK;
}

Status stampa_lista(const Lista *lista) {
    if (lista == NULL) return STATUS_ERR_NULL_PTR;

    printf("    --- CONTENUTO DELLA LISTA ---\n\n");
    for (size_t i = 0; i < lista->size; i++) {
        printf("[%d]\t", lista->data[i]);
    }
    printf("\n\n");

    return STATUS_OK;
}

Status libera_memoria_lista(Lista **lista_ptr) {
    if (lista_ptr == NULL || *lista_ptr == NULL) return STATUS_ERR_NULL_PTR;

    Lista *lista = *lista_ptr; 
    SLEEP_MS(500);

    if (lista->data != NULL) {
        free(lista->data);
        lista->data = NULL;
    }
    lista->capacity = 0;
    lista->size = 0;

    free(lista);
    *lista_ptr = NULL; 

    return STATUS_OK;
}

void check_funzione_interna(Status stato, const char *file, int line) {
    switch (stato) {
        case STATUS_OK:
            break; 

        case STATUS_ERR_ALLC_MEMORY:
            fprintf(stderr, "[CRITICO] [%s:%d] RAM esaurita durante l'allocazione.\n", file, line);
            exit(EXIT_FAILURE);

        case STATUS_ERR_NULL_PTR:
            fprintf(stderr, "[BUG] [%s:%d] Puntatore NULL non valido passato alla funzione.\n", file, line);
            exit(EXIT_FAILURE);
            
        default:
            fprintf(stderr, "[ERRORE] [%s:%d] Errore non previsto (Codice: %d).\n", file, line, stato);
            exit(EXIT_FAILURE);
    }  
}