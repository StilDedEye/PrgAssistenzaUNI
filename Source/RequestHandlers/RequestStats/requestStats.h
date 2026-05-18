//
// Created by andre on 15/05/2026.
//

#ifndef PRGASSISTENZAUNI_REQUESTSTATS_H
#define PRGASSISTENZAUNI_REQUESTSTATS_H
#include "../../Entities/Request/request.h"
#include "../../Entities/RequestList/requestList.h"
#include "../../Interface/InterfaceBuilder/interfaceBuilder.h"
#include "../../RequestHandlers/RequestOrganizer/requestOrganizer.h"

/**
 * @typedef statsCriteria
 * @brief Firma di una funzione di filtro utilizzata per le statistiche.
 * @param request Puntatore alla Request da valutare.
 * @param filterValue Puntatore ai dati del filtro (tipo e formato dipendono dal criterio).
 * @return true se la request soddisfa il criterio, false altrimenti.
 * @details Le funzioni che seguono questa firma devono trattare il parametro filterValue in modo
 *          coerente con il criterio (ad esempio, un int per priority, una string per client name, ecc.).
 */
typedef bool (*statsCriteria)(Request *request, void* filterValue);


/**
 * @brief Calcola il costo medio delle richieste raggruppato per tipologia.
 * @param requestList Puntatore alla lista di richieste da analizzare.
 * @param avgByType Array di output in cui salvare i costi medi per ciascuna tipologia.
 * @param typesNumber Numero di tipologie/categorie da considerare (dimensione logica di `avgByType`).
 * @param statsCriteria Funzione criterio usata per includere/escludere richieste dal calcolo statistico.
 * @details
 * La funzione scorre le richieste presenti in `requestList`, applica il criterio `statsCriteria`
 * e aggiorna l'array `avgByType` con i valori medi per ogni tipo.
 * La media viene calcolata sul costo finale se disponibile, altrimenti su quello stimato.
 * Il chiamante deve garantire che `avgByType` sia allocato con almeno `typesNumber` elementi.
 * In caso di input non validi (ad esempio `requestList == NULL`, `avgByType == NULL`, `typesNumber == 0`),
 * l'implementazione dovrebbe terminare senza modificare i dati.
 */
void get_average_cost(RequestList *requestList, double avgByType[], size_t typesNumber, statsCriteria statsCriteria);

/**
 * @brief Calcola il costo massimo delle richieste raggruppato per tipologia.
 * @param requestList Puntatore alla lista di richieste da analizzare.
 * @param maxByType Array di output in cui salvare il costo massimo per ciascuna tipologia.
 * @param typesNumber Numero di tipologie/categorie da considerare (dimensione logica di `maxByType`).
 * @param statsCriteria Funzione criterio usata per includere/escludere richieste dal calcolo statistico.
 * @details
 * La funzione scorre le richieste presenti in `requestList`, applica il criterio `statsCriteria`
 * e aggiorna `maxByType` con il valore massimo rilevato per ogni tipo.
 * Il chiamante deve garantire che `maxByType` sia allocato con almeno `typesNumber` elementi.
 * Il massimo viene calcolato sul costo finale se disponibile, altrimenti su quello stimato.
 * In caso di input non validi (ad esempio `requestList == NULL`, `maxByType == NULL`, `typesNumber == 0`),
 * l'implementazione dovrebbe terminare senza modificare i dati.
 */
void get_max_cost(RequestList *requestList, double maxByType[], size_t typesNumber, statsCriteria statsCriteria);

/**
 * @brief Calcola il costo minimo delle richieste raggruppato per tipologia.
 * @param requestList Puntatore alla lista di richieste da analizzare.
 * @param minByType Array di output in cui salvare il costo minimo per ciascuna tipologia.
 * @param typesNumber Numero di tipologie/categorie da considerare (dimensione logica di `minByType`).
 * @param statsCriteria Funzione criterio usata per includere/escludere richieste dal calcolo statistico.
 * @details
 * La funzione scorre le richieste presenti in `requestList`, applica il criterio `statsCriteria`
 * e aggiorna `minByType` con il valore minimo rilevato per ogni tipo.
 * Il chiamante deve garantire che `minByType` sia allocato con almeno `typesNumber` elementi.
 * Il minimo viene calcolato sul costo finale se disponibile, altrimenti su quello stimato.
 * In caso di input non validi (ad esempio `requestList == NULL`, `minByType == NULL`, `typesNumber == 0`),
 * l'implementazione dovrebbe terminare senza modificare i dati.
 */
void get_min_cost(RequestList *requestList, double minByType[], size_t typesNumber, statsCriteria statsCriteria);

#endif //PRGASSISTENZAUNI_REQUESTSTATS_H
