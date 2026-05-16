//
// Created by andre on 15/05/2026.
//

#ifndef PRGASSISTENZAUNI_CONSTANTS_H
#define PRGASSISTENZAUNI_CONSTANTS_H

/**
 *
 * @brief Enum di tipi di dispositivi supportati per le richieste di assistenza.
 *
 */
typedef enum {
    LAPTOP,
    SMARTPHONE,
    TABLET,
    DESKTOP,
    CONSOLE,
    PRINTER,
    MORE
} Device;

static const char* deviceNames[] = {"Laptop", "Smartphone", "Tablet", "Desktop", "Console", "Stampante", "Altro"};


/**
 *
 * @brief Enum di tipi di priorità assegnabili alle richieste di assistenza.
 *
 */
typedef enum {
    HIGHEST,
    HIGH,
    MEDIUM,
    LOW,
    LOWEST
} Priority;

static const char* priorityNames[] = {"Massima", "Alta", "Media", "Bassa", "Minima"};


/**
 *
 * @brief Enum di stati di avanzamento associabili alle richieste di assistenza.
 *
 */
typedef enum {
    PENDING,
    IN_PROGRESS,
    COMPLETED,
    CANCELLED
} RequestStatus;

static const char* requestStatusNames[] = {"In Attesa", "In Lavorazione", "Completata", "Cancellata"};

#endif //PRGASSISTENZAUNI_CONSTANTS_H
