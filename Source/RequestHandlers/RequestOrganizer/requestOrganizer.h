//
// Created by andre on 15/05/2026.
//

#ifndef PRGASSISTENZAUNI_REQUESTORGANIZER_H
#define PRGASSISTENZAUNI_REQUESTORGANIZER_H

#include "../../Entities/Request/request.h"
#include "../../Entities/Client/client.h"
#include "../../Entities/RequestList/requestList.h"
#include <stdbool.h>

/**
 * @brief Unisce due sottoarray ordinati di richieste in un unico array ordinato.
 * @param arr Array di puntatori a Request da ordinare.
 * @param left Indice iniziale della prima metà.
 * @param mid Indice finale della prima metà / punto di separazione.
 * @param right Indice finale della seconda metà.
 * @details La funzione confronta le richieste in base al costo stimato e ricompone
 *          l'array originale mantenendo l'ordine crescente.
 */
void merge(Request **arr, size_t left, size_t mid, size_t right, bool (*criteria)(Request*, Request*));

/**
 * @brief Ordina ricorsivamente un array di richieste usando merge sort.
 * @param arr Array di puntatori a Request da ordinare.
 * @param left Indice iniziale del sottoarray da ordinare.
 * @param right Indice finale del sottoarray da ordinare.
 * @details Divide l'array in sottoarray più piccoli, li ordina separatamente e
 *          poi li unisce tramite merge.
 */
void merge_sort(Request **arr, size_t left, size_t right, bool (*criteria)(Request*, Request*));

/**
 * @brief Ordina la lista di richieste contenuta in una RequestList.
 * @param requestList Lista di richieste da ordinare.
 * @details Usa merge sort sull'array interno della lista, se presente, per
 *          ordinare le richieste secondo il criterio definito dal modulo.
 */
void request_list_sort(RequestList *requestList, bool (*criteria)(Request*, Request*));

/*
 * ------------------------
 * Criteri di Ordinamento
 * ------------------------
 */

/**
 * @brief Comparatore per ordinare le richieste per nome del cliente in ordine alfabetico.
 * @param req1 Prima richiesta da confrontare.
 * @param req2 Seconda richiesta da confrontare.
 * @return true se il nome del cliente in req1 deve precedere quello in req2 (ordine alfabetico),
 *         false altrimenti.
 * @details Questa funzione è pensata per essere usata come criterio di ordinamento
 *          passato alle funzioni merge_sort e request_list_sort. Confronta i nomi
 *          dei clienti associati alle richieste in modo lessicografico.
 */
bool sort_by_client_name(Request *req1, Request *req2);

#endif //PRGASSISTENZAUNI_REQUESTORGANIZER_H