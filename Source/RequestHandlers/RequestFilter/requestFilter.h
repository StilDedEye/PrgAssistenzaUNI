//
// Created by andre on 15/05/2026.
//

#ifndef PRGASSISTENZAUNI_REQUESTFILTER_H
#define PRGASSISTENZAUNI_REQUESTFILTER_H

#include "../../Entities/RequestList/requestList.h"
#include "../../Entities/Request/request.h"
#include "../../Entities/Client/client.h"
#include <stdlib.h>
#include <stdbool.h>

/**
 * @typedef filterCriteria
 * @brief Firma di una funzione di filtro.
 * @param request Puntatore alla Request da valutare.
 * @param filterValue Puntatore ai dati del filtro (tipo e formato dipendono dal criterio).
 * @return true se la request soddisfa il criterio, false altrimenti.
 * @details Le funzioni che seguono questa firma devono trattare il parametro filterValue in modo
 *          coerente con il criterio (ad esempio, un int per priority, una string per client name, ecc.).
 */
typedef bool (*filterCriteria)(Request *request, void *filterValue);

/**
 * @brief Filtra una RequestList secondo un criterio fornito.
 * @param requestList Lista di input; non viene modificata.
 * @param criteria Funzione criterio da applicare a ogni Request.
 * @param filterValue Valore del filtro passato al criterio (interpretazione specifica del criterio).
 * @return Nuova RequestList contenente solo le Request che soddisfano il criterio,
 *         oppure NULL in caso di errore (ad esempio allocazione fallita).
 * @details Il chiamante è responsabile di liberare la RequestList restituita. Se requestList è NULL
 *          o criteria è NULL la funzione dovrebbe restituire NULL.
 */
RequestList *filter_requests(RequestList *requestList, filterCriteria criteria, void *filterValue);

/*
 * ------------------------
 * Ricerca richiesta per ID
 * ------------------------
 */

RequestList* search_by_request_id(RequestList* requestList, char* requestID);

/*
 * ------------------------
 * Criteri di Filtraggio
 * ------------------------
 */

/**
 * @brief Criterio: seleziona le richieste che hanno uno specifico stato.
 * @param request Puntatore alla Request da controllare.
 * @param filterValue Puntatore a un valore intero (RequestStatus) da confrontare.
 * @return true se lo stato della request corrisponde a * (RequestStatus*)filterValue, false altrimenti.
 * @details Se request è NULL o filterValue è NULL, la funzione dovrebbe restituire false.
 */
bool filter_by_status(Request *request, void *filterValue);

/**
 * @brief Criterio: seleziona le richieste che hanno una specifica priorità.
 * @param request Puntatore alla Request da controllare.
 * @param filterValue Puntatore a un valore intero (Priority) da confrontare.
 * @return true se la priorità della request corrisponde a * (Priority*)filterValue, false altrimenti.
 * @details Se request è NULL o filterValue è NULL, la funzione dovrebbe restituire false.
 */
bool filter_by_priority(Request *request, void *filterValue);

/**
 * @brief Criterio: seleziona le richieste il cui nome cliente corrisponde (parziale o esatto).
 * @param request Puntatore alla Request da controllare.
 * @param filterValue Puntatore a una stringa (const char*) contenente il nome o la sottostringa da cercare.
 * @return true se il nome del cliente corrisponde al filtro, false altrimenti.
 * @details Il comportamento di matching (case-sensitive, case-insensitive, substring, ecc.) deve essere
 *          definito dall'implementazione. Se request è NULL, o il cliente è NULL, o filterValue è NULL,
 *          restituisce false.
 */
bool filter_by_client_name(Request *request, void *filterValue);

/**
 * @brief Criterio: seleziona le richieste il cui clientID corrisponde al filtro.
 * @param request Puntatore alla Request da controllare.
 * @param filterValue Puntatore a una stringa (const char*) contenente l'ID cliente da cercare.
 * @return true se l'ID cliente della request corrisponde esattamente al filtro, false altrimenti.
 * @details Se request è NULL, o il cliente è NULL, o filterValue è NULL, restituisce false.
 */
bool filter_by_client_id(Request *request, void *filterValue);

/**
 *
 *
 * @brief Criterio di ricerca per identificativo della richiesta.
 * @param request Puntatore alla Request da controllare.
 * @param filterValue Puntatore a una stringa (const char*) contenente l'ID richiesta da cercare.
 * @return true se l'ID della request corrisponde (esatto o secondo la logica di ricerca) al filtro, false altrimenti.
 * @deprecated Questo criterio è più adatto per una ricerca binaria o lineare specifica, non per un filtro generico.
 *             Considerare l'uso di search_by_request_id() per questo scopo.
 */
bool filter_by_request_id(Request *request, void *filterValue);

#endif //PRGASSISTENZAUNI_REQUESTFILTER_H
