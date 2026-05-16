//
// Created by andre on 16/05/2026.
//

#ifndef PRGASSISTENZAUNI_UTIL_H
#define PRGASSISTENZAUNI_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
char* parseDoubleFloatToString (char* outBuffer, double value);

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
char* parseDateToString(char* outBuffer, struct tm date);

#endif //PRGASSISTENZAUNI_UTIL_H
