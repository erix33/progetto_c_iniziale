#ifndef FUNZIONI_H
#define FUNZIONI_H

#include <stddef.h>

typedef struct Lista Lista;

typedef enum {
    STATUS_OK = 0,
    STATUS_ERR_ALLC_MEMORY,
    STATUS_ERR_NULL_PTR
} Status;

Status create_list(size_t capacity, Lista **out_lista);
Status stampa_lista(const Lista *lista);
Status aggiungi_numero_alla_lista(Lista *lista, int numero);
Status libera_memoria_lista(Lista **lista_ptr);

// Funzione interna di log con file e riga
void check_funzione_interna(Status stato, const char *file, int line);

// MACRO PROFESSIONALE: cattura in automatico file e riga dove viene invocata
#define CHECK(chiamata) check_funzione_interna((chiamata), __FILE__, __LINE__)

#endif