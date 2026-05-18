//
// Created by aless on 16/05/2026.
//

#ifndef PRGASSISTENZAUNI_REQUESTLIST_H
#define PRGASSISTENZAUNI_REQUESTLIST_H

#include "../Request/request.h"

/**
 * @typedef RequestList
 * @brief Struttura che rappresenta la lista delle richieste presenti nel sistema
 * @details La struttura contiene:
 *  - [Request**] requests: array dinamico di puntatori a Request, che rappresenta le richieste presenti nel sistema
 *  - [int] count: numero di richieste attualmente presenti nella lista
 *  - [int] capacity: capacità massima dell'array di richieste
 */
typedef struct requestList {
    Request **requests;
    int count;
    int capacity;
}RequestList;

/**
 * @brief Crea una nuova lista di richieste vuota
 * @param requestList Lista da inizializzare
 */
void init_request_list(RequestList* requestList);

/**
 * @brief Rilascia le risorse associate a una lista di richieste.
 * @param requestList Puntatore alla lista da distruggere.
 */
void destroy_request_list(RequestList* requestList);

/**
 * @brief Aggiunge una nuova richiesta alla lista.
 * @param requestList Lista a cui aggiungere la richiesta.
 * @param request Richiesta da aggiungere alla lista.
 * @return 0 se l'aggiunta è avvenuta con successo, -1 in caso di errore (ad esempio, se la lista è nulla).
 */
int add_request(RequestList* requestList, Request* request);

#endif //PRGASSISTENZAUNI_REQUESTLIST_H
