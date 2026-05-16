//
// Created by andre on 15/05/2026.
//

#ifndef PRGASSISTENZAUNI_INTERFACEBUILDER_H
    #define PRGASSISTENZAUNI_INTERFACEBUILDER_H

    #include <stdio.h>
    #include "../../../ExternalLibraries/fort/fort.h"
    #include "../interfaceConstants.h"
    #include <stdbool.h>

    #ifdef _WIN32
        #include <windows.h> // Serve per configurare il terminale su Windows
    #endif


    #include "../../Entities/Request/request.h"
    #include "../../Entities/Client/client.h"
    #include "../../Utilities/util.h"

    /**
     * @brief Inizializza l'interfaccia del terminale.
     * @details Configura il terminale per supportare i caratteri UTF-8, garantendo la corretta visualizzazione di
     *          simboli e caratteri speciali.
     * @details Se il sistema operativo è Windows, viene impostato il terminale in Utf-8. Su altri sistemi operativi
     *          (Linux, macOS) questo viene fatto già di default.
     */
    void initialize_terminal(void);

    /**
     * @brief Pulisce il terminale.
     * @details Utilizza una combinazione di sequenze escape ANSI per cancellare tutto il testo presente nel terminale e
     *          riportare il cursore in alto a sinistra (0,0).
     */
    void cleanup_terminal(void);

    /**
     * @brief Costruisce e visualizza la tabella delle richieste.
     * @details Utilizza la libreria fort per creare una tabella formattata con i dati delle richieste.
     * Se il parametro cleanupTerminal è true, pulisce il terminale prima
     * @param arr Vettore di struct Request
     * @param n Numero di elementi nel vettore arr
     * @param cleanupTerminal
     * @see Entities/Request/*
     */
    void build_requests_table(const Request* arr[], size_t n, bool cleanupTerminal);

    /**
     * @brief Costruisce e visualizza la tabella dei clienti.
     * @details Utilizza la libreria fort per creare una tabella formattata con i dati dei clienti.
     * Se il parametro cleanupTerminal è true, pulisce il terminale prima
     * // TODO completare params
     * @param cleanupTerminal
     */
    void build_clients_table(const char *vettore[], size_t n, bool cleanupTerminal);


    /**
     * @brief Stampa il logo del gruppo.
     */
    void print_logo(void);

    /**
    * @brief Stampa i crediti del progetto.
    */
    void print_credits(void);


#endif