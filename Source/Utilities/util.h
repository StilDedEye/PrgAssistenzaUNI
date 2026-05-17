//
// Created by andre on 16/05/2026.
//

#ifndef PRGASSISTENZAUNI_UTIL_H
#define PRGASSISTENZAUNI_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


/**
 * @name Codici Tasti di Navigazione
 * Costanti interne utilizzate per gestire l'input da tastiera senza
 * generare conflitti con la tabella ASCII o gli scancode standard. Per questo con valori alti.
 * @{
 */

/** @brief Usato nei casi in cui non si vuole specificare un tasto in particolare */
#define UTIL_KEY_UNDEFINED 1000

/** @brief Restituito quando viene premuto un tasto non rilevante per la navigazione dei menu. */
#define UTIL_KEY_OTHER 1001

/** @brief Codice univoco associato alla pressione della freccia SU. */
#define UTIL_KEY_UP    1002

/** @brief Codice univoco associato alla pressione della freccia GIÙ. */
#define UTIL_KEY_DOWN  1003

/** @brief Codice univoco associato alla pressione della freccia SINISTRA. */
#define UTIL_KEY_LEFT  1004

/** @brief Codice univoco associato alla pressione della freccia DESTRA. */
#define UTIL_KEY_RIGHT  1005

/** @brief Codice unificato per il tasto INVIO, indipendente dal sistema operativo in uso. */
#define UTIL_KEY_ENTER 1006

/** @} */



/**
 * @brief Dimensione del buffer usato per convertire un double in stringa
 */
#define UTIL_FLOAT_PARSER_BUFFER_SIZE 15

/**
 * @brief Dimensione del buffer usato per convertire una data {time.h --> struct tm} in stringa
 */
#define UTIL_DATE_PARSER_BUFFER_SIZE 20

/**
 * @brief Converte un valore double in una rappresentazione testuale.
 *
 * @details
 * Scrive nella memoria puntata da `outBuffer` la rappresentazione in stringa del
 * valore double `value`. La funzione non alloca memoria.
 *
 * @param outBuffer Buffer fornito dal chiamante dove verrà scritta la stringa.
 *                  È responsabilità del chiamante assicurare che il buffer sia
 *                  grande almeno quanto `UTIL_PARSER_BUFFER_SIZE`.
 * @param value     Valore double/float da convertire in stringa.
 *
 * @return Ritorna il puntatore passato in `outBuffer`.
 * @code
 * char buf[UTIL_PARSER_BUFFER_SIZE];
 * parseDoubleFloatToString(buf, 3.14159);
 * printf("valore: %s\n", buf);
 */
char* util_parse_double_to_string (char* outBuffer, double value);

/**
 * @brief Converte una data del tipo {time.h --> struct tm} in una rappresentazione testuale.
 *
 * @details
 * Scrive nella memoria puntata da `outBuffer` la rappresentazione in stringa del
 * valore data `date`. La funzione non alloca memoria.
 *
 * @param outBuffer Buffer fornito dal chiamante dove verrà scritta la stringa.
 *                  È responsabilità del chiamante assicurare che il buffer sia
 *                  grande almeno quanto `UTIL_DATE_PARSER_BUFFER_SIZE`.
 * @param date     Valore struct tm da convertire in stringa.
 *
 * @return Ritorna il puntatore passato in `outBuffer`.
 * @code
 * char buf[UTIL_DATE_PARSER_BUFFER_SIZE];
 * parseDateToString(buf, date);
 * printf("valore: %s\n", buf);
 */
char* util_parse_date_to_string(char* outBuffer, struct tm date);


/**
*   @brief Rimuove tutti i caratteri rimasti nel buffer di input (stdin), incluso il
 * carattere di nuova riga '\n'.
 */
void util_clear_input_buffer(void);

/**
 * @brief Legge un tasto premuto dall'utente e restituisce un codice univoco.
 *
 * @details
 * Cattura l'input da tastiera e restituisce un codice intero che rappresenta il tasto
 * premuto. La funzione traduce i tasti speciali (frecce di navigazione, invio)
 * in costanti standardizzate definite in questo header, evitando conflitti con
 * i codici ASCII standard.
 *
 * @return
 * - `UTIL_KEY_UP` se è stata premuta la freccia SU
 * - `UTIL_KEY_DOWN` se è stata premuta la freccia GIÙ
 * - `UTIL_KEY_ENTER` se è stato premuto il tasto INVIO
 * - `UTIL_KEY_OTHER` per qualsiasi altro tasto
 * @see UTIL_KEY_UP, UTIL_KEY_DOWN, UTIL_KEY_ENTER, UTIL_KEY_OTHER
 */
int util_read_key(void);


#endif //PRGASSISTENZAUNI_UTIL_H
