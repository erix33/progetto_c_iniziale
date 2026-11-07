#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"

int main(void) {
    Lista *lista = NULL; 

    // --- PRIMA LISTA (Sintassi pulita enterprise con CHECK) ---
    CHECK(create_list(3, &lista));

    CHECK(aggiungi_numero_alla_lista(lista, 10));
    CHECK(aggiungi_numero_alla_lista(lista, 20));
    CHECK(aggiungi_numero_alla_lista(lista, 30));
    CHECK(aggiungi_numero_alla_lista(lista, 40));

    CHECK(stampa_lista(lista));
    CHECK(libera_memoria_lista(&lista));

    // --- SECONDA LISTA ---
    Lista *seconda_lista = NULL; 
    
    CHECK(create_list(2, &seconda_lista)); 

    CHECK(aggiungi_numero_alla_lista(seconda_lista, 1));
    CHECK(aggiungi_numero_alla_lista(seconda_lista, 3));
    CHECK(aggiungi_numero_alla_lista(seconda_lista, 5));
    
    CHECK(stampa_lista(seconda_lista));
    CHECK(libera_memoria_lista(&seconda_lista));

    return EXIT_SUCCESS;
}