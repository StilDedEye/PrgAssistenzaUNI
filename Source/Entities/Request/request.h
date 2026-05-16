//
// Created by andre on 15/05/2026.
//

#ifndef PRGASSISTENZAUNI_REQUEST_H
#define PRGASSISTENZAUNI_REQUEST_H

#include "../Client/client.h"
#include "../../Constants/constants.h"
#include <time.h>

/**
 * @typedef Request
 * @brief Struttura dati che rappresenta una richiesta di assistenza.
 * @details La struttura contiene:
 *  - [string] requestID: identificativo univoco della richiesta, del tipo "RQ-XXX", dove XXX è un numero progressivo
 *  - [Client] client: riferimento al cliente che ha effettuato la richiesta
 *  - [Device] device: tipo di dispositivo per cui è stata effettuata la richiesta
 *  - [Priority] priority: livello di priorità assegnato alla richiesta
 *  - [RequestStatus] status: stato di avanzamento della richiesta
 *  - [string] description: descrizione dettagliata del problema segnalato nella richiesta
 *  - [double] estimatedCost: costo stimato per la richiesta
 *  - [double] finalCost: costo finale a richiesta completata (-1 se non disponibile)
 *  - [struct tm] creationDate: data di creazione della richiesta
 */
typedef struct request Request;

/**
 * @brief Crea una nuova richiesta di assistenza con i dati specificati
 * @param requestID Identificativo della richiesta
 * @param client Cliente che ha effettuato la richiesta
 * @param device Dispositivo per cui è stata effettuata la richiesta
 * @param priority Livello di priorità assegnato alla richiesta
 * @param description Descrizione della Richiesta
 * @param estimatedCost Costo stimato della richiesta
 * @param finalCost Costo finale della richiesta
 * @param creationDate Data di creazione della richiesta
 * @return
 */
Request* create_request(const char *requestID, Client *client, Device device,
                        Priority priority, const char *description, double estimatedCost,
                        double finalCost, struct tm creationDate);

/**
 * @brief Elimina una richiesta di assistenza e libera la memoria associata
 * @param request Richiesta da eliminare
 */
void destroy_request(Request *request);

/*
 * -------------------
 * Getters
 * -------------------
 */

/**
 * @brief Restituisce l'identificativo univoco della richiesta.
 * @param request Richiesta da cui ottenere l'ID
 * @return Identificativo della richiesta
 */
const char *get_request_id(const Request *request);

/**
 * @brief Restituisce il cliente associato alla richiesta.
 * @param request Richiesta da cui ottenere il cliente
 * @return Puntatore al cliente associato
 */
Client *get_request_client(const Request *request);

/**
 * @brief Restituisce il tipo di dispositivo della richiesta.
 * @param request Richiesta da cui ottenere il dispositivo
 * @return Dispositivo associato alla richiesta. 0 in caso di errore
 */
Device get_request_device(const Request *request);

/**
 * @brief Restituisce la priorità assegnata alla richiesta.
 * @param request Richiesta da cui ottenere la priorità
 * @return Priorità della richiesta. 0 in caso di errore
 */
Priority get_request_priority(const Request *request);

/**
 * @brief Restituisce lo stato corrente della richiesta.
 * @param request Richiesta da cui ottenere lo stato
 * @return Stato della richiesta. 0 in caso di errore
 */
RequestStatus get_request_status(const Request *request);

/**
 * @brief Restituisce la descrizione del problema segnalato.
 * @param request Richiesta da cui ottenere la descrizione
 * @return Descrizione della richiesta
 */
const char *get_request_description(const Request *request);

/**
 * @brief Restituisce il costo stimato della richiesta.
 * @param request Richiesta da cui ottenere il costo stimato
 * @return Costo stimato della richiesta
 */
double get_request_estimated_cost(const Request *request);

/**
 * @brief Restituisce il costo finale della richiesta.
 * @param request Richiesta da cui ottenere il costo finale
 * @return Costo finale della richiesta
 */
double get_request_final_cost(const Request *request);

/**
 * @brief Restituisce la data di creazione della richiesta.
 * @param request Richiesta da cui ottenere la data di creazione
 * @return Data di creazione della richiesta. Empty struct in caso di errore
 */
struct tm get_request_creation_date(const Request *request);


/*
 * -------------------
 * Setters
 * -------------------
 */

/**
 * @brief Imposta il cliente associato alla richiesta.
 * @param request Richiesta da aggiornare
 * @param client Nuovo cliente associato
 */
void set_request_client(Request *request, Client *client);

/**
 * @brief Imposta il tipo di dispositivo della richiesta.
 * @param request Richiesta da aggiornare
 * @param device Nuovo dispositivo associato
 */
void set_request_device(Request *request, Device device);

/**
 * @brief Imposta la priorità della richiesta.
 * @param request Richiesta da aggiornare
 * @param priority Nuovo livello di priorità
 */
void set_request_priority(Request *request, Priority priority);

/**
 * @brief Imposta lo stato corrente della richiesta.
 * @param request Richiesta da aggiornare
 * @param status Nuovo stato della richiesta
 */
void set_request_status(Request *request, RequestStatus status);

/**
 * @brief Imposta la descrizione del problema segnalato.
 * @param request Richiesta da aggiornare
 * @param description Nuova descrizione della richiesta
 */
void set_request_description(Request *request, const char *description);

/**
 * @brief Imposta il costo stimato della richiesta.
 * @param request Richiesta da aggiornare
 * @param estimatedCost Nuovo costo stimato
 */
void set_request_estimated_cost(Request *request, double estimatedCost);

/**
 * @brief Imposta il costo finale della richiesta.
 * @param request Richiesta da aggiornare
 * @param finalCost Nuovo costo finale
 */
void set_request_final_cost(Request *request, double finalCost);

/**
 * @brief Imposta la data di creazione della richiesta.
 * @param request Richiesta da aggiornare
 * @param creationDate Nuova data di creazione
 */
void set_request_creation_date(Request *request, struct tm creationDate);


#endif //PRGASSISTENZAUNI_REQUEST_H
