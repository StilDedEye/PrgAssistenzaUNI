//
// Created by andre on 15/05/2026.
//

#ifndef PRGASSISTENZAUNI_CLIENT_H
#define PRGASSISTENZAUNI_CLIENT_H

/**
 * @brief Struttura dati che rappresenta un cliente
 * @details La struttura contiene:
 *  - [string] clientID: identificativo univoco del cliente, del tipo "CL-XXX" dove XXX è un numero progressivo
 *  - [string] name: nome del cliente
 */
typedef struct client Client;
static const char* clientFieldNames[] = {"ID Cliente", "Nome Cliente"};

/**
 * @brief Crea un nuovo cliente con l'identificativo e il nome specificati
 * @param clientID ID cliente
 * @param name Nome cliente
 * @return Il nuovo cliente creato
 */
Client* create_client(const char *clientID, const char *name);

/**
 * @brief Elimina un cliente e libera la memoria associata
 * @param client Cliente da eliminare
 */
void destroy_client(Client *client);

/*
 * -------------------
 * Getters
 * -------------------
 */

/**
 * @brief Restituisce l'identificativo del cliente
 * @param client Cliente di cui ottenere l'ID
 * @return Identificativo del cliente
 */
const char *get_client_id(Client *client);

/**
 * @brief Restituisce il nome del cliente
 * @param client Cliente di cui ottenere il nome
 * @return Nome del cliente
 */
const char *get_client_name(Client *client);

/*
* -------------------
 * Setters
 * -------------------
 */

/**
 * @brief Imposta il nome del cliente
 * @param client Cliente di cui impostare il nome
 * @param name Nuovo nome del cliente
 */
void set_client_name(Client *client, const char *name);

#endif //PRGASSISTENZAUNI_CLIENT_H
