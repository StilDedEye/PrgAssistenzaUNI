//
// Created by andre on 15/05/2026.
//

#ifndef PRGASSISTENZAUNI_CONSTANTS_H
#define PRGASSISTENZAUNI_CONSTANTS_H

/**
 *
 * @brief Enum di tipi di dispositivi supportati per le richieste di assistenza.
 * @details DEVICE_COUNT rappresenta il numero di valori dell'enum
 *
 */
typedef enum {
    LAPTOP,
    SMARTPHONE,
    TABLET,
    DESKTOP,
    CONSOLE,
    PRINTER,
    MORE,
    DEVICE_COUNT
} Device;

static const char* deviceNames[] = {"Laptop", "Smartphone", "Tablet", "Desktop", "Console", "Stampante", "Altro"};


/**
 *
 * @brief Enum di tipi di priorità assegnabili alle richieste di assistenza.ù
 * @details PRIORITY_COUNT rappresenta il numero di valori dell'enum
 */
typedef enum {
    HIGHEST,
    HIGH,
    MEDIUM,
    LOW,
    LOWEST,
    PRIORITY_COUNT
} Priority;

static const char* priorityNames[] = {"Massima", "Alta", "Media", "Bassa", "Minima"};


/**
 *
 * @brief Enum di stati di avanzamento associabili alle richieste di assistenza.
 * @details STATUS_COUNT rappresenta il numero di valori dell'enum
 */
typedef enum {
    PENDING,
    IN_PROGRESS,
    COMPLETED,
    CANCELLED,
    STATUS_COUNT
} RequestStatus;

static const char* requestStatusNames[] = {"In Attesa", "In Lavorazione", "Completata", "Cancellata"};

#endif //PRGASSISTENZAUNI_CONSTANTS_H
