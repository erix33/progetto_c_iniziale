#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"

int main(void) {

    Lista *lista = NULL; 

    CHECK(create_list(3, &lista));

    CHECK(aggiungi_numero_alla_lista(lista, 10));
    CHECK(aggiungi_numero_alla_lista(lista, 20));
    CHECK(aggiungi_numero_alla_lista(lista, 30));
    CHECK(aggiungi_numero_alla_lista(lista, 40));

    CHECK(stampa_lista(lista));
    CHECK(libera_memoria_lista(&lista));


    Lista *seconda_lista = NULL; 
    
    CHECK(create_list(2, &seconda_lista)); 

    CHECK(aggiungi_numero_alla_lista(seconda_lista, 1));
    CHECK(aggiungi_numero_alla_lista(seconda_lista, 3));
    CHECK(aggiungi_numero_alla_lista(seconda_lista, 5));
    
    CHECK(stampa_lista(seconda_lista));
    CHECK(libera_memoria_lista(&seconda_lista));

    CHECK(aggiungi_numero_alla_lista(seconda_lista, 10)); //questo farà scattare l'errore del puntatore a NULL con nome file e numero riga grazie alla macro

    return EXIT_SUCCESS;
}