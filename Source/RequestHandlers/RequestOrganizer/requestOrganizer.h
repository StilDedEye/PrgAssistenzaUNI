//
// Created by andre on 15/05/2026.
//

#ifndef PRGASSISTENZAUNI_REQUESTORGANIZER_H
#define PRGASSISTENZAUNI_REQUESTORGANIZER_H

/**
 * @brief Costante che identifica l'ordinamento crescente.
 * @details Può essere utilizzata come valore di controllo per indicare che un criterio
 *          di confronto deve seguire un ordine crescente.
 */
#define CRESCENT_SORTING 1

/**
 * @brief Costante che identifica l'ordinamento decrescente.
 * @details Può essere utilizzata come valore di controllo per indicare che un criterio
 *          di confronto deve seguire un ordine decrescente.
 */
#define DESCENT_SORTING (-1)

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
 * @param criteria Puntatore a funzione che definisce il criterio di confronto tra due richieste.
 * @param order Direzione di ordinamento: `CRESCENT_SORTING` oppure `DESCENT_SORTING`.
 * @details La funzione unisce due sottoarray già ordinati mantenendo l'ordine definito dal
 *          criterio di confronto e dalla direzione di ordinamento forniti.
 */
void merge(Request **arr, size_t left, size_t mid, size_t right,
           bool (*criteria)(Request*, Request*, int), int order);

/**
 * @brief Ordina ricorsivamente un array di richieste usando merge sort.
 * @param arr Array di puntatori a Request da ordinare.
 * @param left Indice iniziale del sottoarray da ordinare.
 * @param right Indice finale del sottoarray da ordinare.
 * @param criteria Puntatore a funzione che definisce il criterio di confronto tra due richieste.
 * @param order Direzione di ordinamento: `CRESCENT_SORTING` oppure `DESCENT_SORTING`.
 * @details Divide ricorsivamente l'array in sottoarray più piccoli, li ordina separatamente e
 *          poi li unisce tramite la funzione merge, utilizzando i criteri forniti.
 */
void merge_sort(Request **arr, size_t left, size_t right,
                bool (*criteria)(Request*, Request*, int), int order);

/**
 * @brief Ordina la lista di richieste contenuta in una RequestList.
 * @param requestList Puntatore alla lista di richieste da ordinare.
 * @param criteria Puntatore a funzione che definisce il criterio di confronto tra due richieste.
 * @param order Direzione di ordinamento: `CRESCENT_SORTING` oppure `DESCENT_SORTING`.
 * @details Applica l'algoritmo di merge sort sull'array interno della lista, se presente e
 *          se contiene più di un elemento, utilizzando i criteri di ordinamento specificati.
 */
void request_list_sort(RequestList *requestList,
                       bool (*criteria)(Request*, Request*, int), int order);

/*
 * ------------------------
 * Ordine di Ordinamento
 * ------------------------
 */

/**
 * @brief Valuta se un risultato di confronto soddisfa l'ordine richiesto.
 * @param result Risultato del confronto tra due valori.
 * @param order Direzione di ordinamento desiderata: `CRESCENT_SORTING` oppure `DESCENT_SORTING`.
 * @return true se il risultato del confronto è compatibile con l'ordine richiesto,
 *         false altrimenti.
 * @details Questa funzione interpreta il risultato di un confronto
 *          alla luce della direzione di ordinamento specificata, restituendo true se il risultato indica che il primo elemento dovrebbe precedere il secondo
 *          in base all'ordine richiesto.
 */
bool sorting_order_control(bool result, int order);

/*
 * ------------------------
 * Criteri di Ordinamento
 * ------------------------
 */

/**
 * @brief Comparatore per ordinare le richieste per nome del cliente in ordine alfabetico.
 * @param req1 Prima richiesta da confrontare.
 * @param req2 Seconda richiesta da confrontare.
 * @param order Direzione di ordinamento: `CRESCENT_SORTING` oppure `DESCENT_SORTING`.
 * @return true se il nome del cliente in `req1` deve precedere quello in `req2` secondo il criterio definito,
 *         false altrimenti.
 * @details Questa funzione confronta i nomi dei clienti associati alle due richieste in modo lessicografico,
 *          applicando la direzione di ordinamento specificata.
 */
bool sort_by_client_name(Request *req1, Request *req2, int order);

/**
 * @brief Comparatore per ordinare le richieste per costo stimato.
 * @param req1 Prima richiesta da confrontare.
 * @param req2 Seconda richiesta da confrontare.
 * @param order Direzione di ordinamento: `CRESCENT_SORTING` oppure `DESCENT_SORTING`.
 * @return true se il costo stimato di `req1` deve precedere quello di `req2` secondo il criterio definito,
 *         false altrimenti.
 * @details Questa funzione confronta i costi stimati delle due richieste in modo numerico,
 *          applicando la direzione di ordinamento specificata.
 */
bool sort_by_estimated_cost(Request *req1, Request *req2, int order);

/**
 * @brief Comparatore per ordinare le richieste per livello di priorità.
 * @param req1 Prima richiesta da confrontare.
 * @param req2 Seconda richiesta da confrontare.
 * @param order Direzione di ordinamento: `CRESCENT_SORTING` oppure `DESCENT_SORTING`.
 * @return true se la priorità di `req1` deve precedere quella di `req2` secondo il criterio definito,
 *         false altrimenti.
 * @details Questa funzione confronta i livelli di priorità associati alle due richieste in modo numerico,
 *          applicando la direzione di ordinamento specificata.
 */
bool sort_by_priority(Request *req1, Request *req2, int order);

/**
 * @brief Comparatore per ordinare le richieste per data di creazione.
 * @param req1 Prima richiesta da confrontare.
 * @param req2 Seconda richiesta da confrontare.
 * @param order Direzione di ordinamento: `CRESCENT_SORTING` oppure `DESCENT_SORTING`.
 * @return true se la data di creazione di `req1` deve precedere quella di `req2` secondo il criterio definito,
 *         false altrimenti.
 * @details Questa funzione confronta le date di creazione associate alle due richieste in modo cronologico,
 *          applicando la direzione di ordinamento specificata.
 */
bool sort_by_creation_date(Request *req1, Request *req2, int order);

/**
 * @brief Comparatore per ordinare le richieste per tipo di dispositivo.
 * @param req1 Prima richiesta da confrontare.
 * @param req2 Seconda richiesta da confrontare.
 * @param order Direzione di ordinamento: `CRESCENT_SORTING` oppure `DESCENT_SORTING`.
 * @return true se il dispositivo di `req1` deve precedere quello di `req2` secondo il criterio definito,
 *         false altrimenti.
 * @details Questa funzione confronta i tipi di dispositivo associati alle due richieste in modo numerico,
 *          applicando la direzione di ordinamento specificata.
 */
bool sort_by_device(Request *req1, Request *req2, int order);

/**
 * @brief Comparatore per ordinare le richieste per stato di avanzamento.
 * @param req1 Prima richiesta da confrontare.
 * @param req2 Seconda richiesta da confrontare.
 * @param order Direzione di ordinamento: `CRESCENT_SORTING` oppure `DESCENT_SORTING`.
 * @return true se lo stato di `req1` deve precedere quello di `req2` secondo il criterio definito,
 *         false altrimenti.
 * @details Questa funzione confronta gli stati di avanzamento associati alle due richieste in modo numerico,
 *          applicando la direzione di ordinamento specificata.
 */
bool sort_by_status(Request *req1, Request *req2, int order);


#endif //PRGASSISTENZAUNI_REQUESTORGANIZER_H