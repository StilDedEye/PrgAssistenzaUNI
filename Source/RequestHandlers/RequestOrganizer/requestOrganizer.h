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
 * @param criteria Puntatore a funzione che definisce il criterio di confronto tra due richieste.
 * @param control Puntatore a funzione che definisce l'ordine (crescente o decrescente) per valori interi.
 * @details La funzione unisce due sottoarray già ordinati mantenendo l'ordine definito dai
 *          criteri di confronto e controllo forniti.
 */
void merge(Request **arr, size_t left, size_t mid, size_t right,
           bool (*criteria)(Request*, Request*, bool (*)(int, int)),
           bool (*control)(int, int));

/**
 * @brief Ordina ricorsivamente un array di richieste usando merge sort.
 * @param arr Array di puntatori a Request da ordinare.
 * @param left Indice iniziale del sottoarray da ordinare.
 * @param right Indice finale del sottoarray da ordinare.
 * @param criteria Puntatore a funzione che definisce il criterio di confronto tra due richieste.
 * @param control Puntatore a funzione che definisce l'ordine (crescente o decrescente) per valori interi.
 * @details Divide ricorsivamente l'array in sottoarray più piccoli, li ordina separatamente e
 *          poi li unisce tramite la funzione merge, utilizzando i criteri forniti.
 */
void merge_sort(Request **arr, size_t left, size_t right,
                bool (*criteria)(Request*, Request*, bool (*)(int, int)),
                bool (*control)(int, int));

/**
 * @brief Ordina la lista di richieste contenuta in una RequestList.
 * @param requestList Puntatore alla lista di richieste da ordinare.
 * @param criteria Puntatore a funzione che definisce il criterio di confronto tra due richieste.
 * @param control Puntatore a funzione che definisce l'ordine (crescente o decrescente) per valori interi.
 * @details Applica l'algoritmo di merge sort sull'array interno della lista, se presente e
 *          se contiene più di un elemento, utilizzando i criteri di ordinamento specificati.
 */
void request_list_sort(RequestList *requestList,
                       bool (*criteria)(Request*, Request*, bool (*)(int, int)),
                       bool (*control)(int, int));

/*
 * ------------------------
 * Criteri di Controllo
 * ------------------------
 */

/**
 * @brief Comparatore per ordinamento crescente di valori interi.
 * @param value1 Primo valore da confrontare.
 * @param value2 Secondo valore da confrontare.
 * @return true se value1 è minore o uguale a value2 (ordine crescente),
 *         false altrimenti.
 * @details Questa funzione è un criterio di controllo utilizzato per determinare
 *          l'ordine crescente durante l'ordinamento di valori numerici interi.
 */
bool sort_crescent(int value1, int value2);

/**
 * @brief Comparatore per ordinamento decrescente di valori interi.
 * @param value1 Primo valore da confrontare.
 * @param value2 Secondo valore da confrontare.
 * @return true se value1 è maggiore o uguale a value2 (ordine decrescente),
 *         false altrimenti.
 * @details Questa funzione è un criterio di controllo utilizzato per determinare
 *          l'ordine decrescente durante l'ordinamento di valori numerici interi.
 */
bool sort_descent(int value1, int value2);


/*
 * ------------------------
 * Criteri di Ordinamento
 * ------------------------
 */

/**
 * @brief Comparatore per ordinare le richieste per nome del cliente in ordine alfabetico.
 * @param req1 Prima richiesta da confrontare.
 * @param req2 Seconda richiesta da confrontare.
 * @param control Puntatore a funzione che definisce l'ordine (crescente o decrescente) per valori interi.
 * @return true se il nome del cliente in req1 deve precedere quello in req2 secondo il criterio definito,
 *         false altrimenti.
 * @details Questa funzione è un criterio di ordinamento che confronta i nomi dei clienti
 *          associati alle due richieste in modo lessicografico, applicando la direzione
 *          (crescente o decrescente) specificata dalla funzione control.
 */
bool sort_by_client_name(Request *req1, Request *req2, bool (*control)(int, int));

#endif //PRGASSISTENZAUNI_REQUESTORGANIZER_H