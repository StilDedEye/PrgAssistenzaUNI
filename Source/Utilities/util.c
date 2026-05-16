//
// Created by andre on 16/05/2026.
//

#include "util.h"


char* parseDoubleFloatToString(char* outBuffer, double value)
{
    if (outBuffer == NULL) {
        return NULL;
    }

    // Scrive il numero nella stringa, per un massimo di UTIL_PARSE_BUFFER_SIZE-1 caratteri
    snprintf(outBuffer, UTIL_FLOAT_PARSER_BUFFER_SIZE, "%.2f", value);

    // Ritorno del ptr per uso inline
    return outBuffer;
}

char* parseDateToString(char* outBuffer, struct tm date)
{
    if (outBuffer == NULL) {
        return NULL;
    }
    strftime(outBuffer, UTIL_DATE_PARSER_BUFFER_SIZE, "%Y-%m-%d %H:%M:%S", &date);
    // Ritorno del ptr per uso inline
    return outBuffer;
}