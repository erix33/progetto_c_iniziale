#include <stdio.h>
#include <stdlib.h>
#include "funzioni.h"

int main(){

    Lista *lista = NULL; 
    Status esito;

    // --- CREAZIONE DELLA LISTA CON CONTROLLO PROFESSIONALE ---
    esito = create_list(3, &lista);

    check_funzione_con_switch(esito);

    // --- INSERIMENTO DATI ---
    // Gestiamo il primo inserimento per vedere la logica dello switch su un'operazione normale
    esito = aggiungi_numero_alla_lista(lista, 10);
    
    check_funzione_con_switch(esito);

    // Nelle operazioni successive, a lavoro si fa spesso una "macro" o una funzione 
    // di supporto per non riscrivere lo switch 100 volte, ma la logica base rimane questa:
    aggiungi_numero_alla_lista(lista, 20);
    aggiungi_numero_alla_lista(lista, 30);
    aggiungi_numero_alla_lista(lista, 40);

    stampa_lista(lista);
    libera_memoria_lista(lista);

    // --- SECONDA LISTA ---
    Lista *seconda_lista = NULL; 
    
    esito = create_list(2, &seconda_lista); 
    
    check_funzione_con_switch(esito);

    aggiungi_numero_alla_lista(seconda_lista, 1);
    aggiungi_numero_alla_lista(seconda_lista, 3);
    aggiungi_numero_alla_lista(seconda_lista, 5);
    
    stampa_lista(seconda_lista);
    libera_memoria_lista(seconda_lista);

    return EXIT_SUCCESS;
}