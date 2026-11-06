#ifndef FUNZIONI_H
#define FUNZIONI_H

#include <stddef.h>

typedef struct Lista Lista;

typedef enum {
    STATUS_OK = 0,               // tutto perfetto
    STATUS_ERR_ALLC_MEMORY,      // Errore di allocazione memoria
    STATUS_ERR_NULL_PTR          // Errore se qualcuno ci passa una lista vuota (NULL)
} Status;

Status create_list(size_t capacity, Lista **out_lista);
Status stampa_lista(const Lista *lista);
Status aggiungi_numero_alla_lista(Lista *lista, int numero);
Status libera_memoria_lista(Lista **lista_ptr);
void check_funzione_con_switch(Status stato);

#endif