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
    void ui_initialize_terminal(void);

    /**
     * @brief Pulisce il terminale.
     * @details Utilizza una combinazione di sequenze escape ANSI per cancellare tutto il testo presente nel terminale e
     *          riportare il cursore in alto a sinistra (0,0).
     */
    void ui_clear_terminal(void);

    /**
     * @brief Costruisce e visualizza la tabella delle richieste.
     * @details Utilizza la libreria fort per creare una tabella formattata con i dati delle richieste.
     * Se il parametro cleanupTerminal è true, pulisce il terminale prima
     * @param arr Vettore di struct Request
     * @param n Numero di elementi nel vettore arr
     * @param cleanupTerminal
     * @see Entities/Request/*
     */
    void ui_print_requests_table(const Request* arr[], size_t n, bool cleanupTerminal);

    /**
     * @brief Costruisce e visualizza la tabella dei clienti.
     * @details Utilizza la libreria fort per creare una tabella formattata con i dati dei clienti.
     * Se il parametro cleanupTerminal è true, pulisce il terminale prima
     * // TODO completare params
     * @param cleanupTerminal
     */
    void ui_print_clients_table(const char *arr[], size_t n, bool cleanupTerminal);


    /**
     * @brief Stampa un header formattato a schermo.
     * @param title Titolo da stampare
     */
    void ui_print_header(const char* title);

    /**
     * @brief Stampa un titolo di sezione formattato a schermo.
     * @param section_name Titolo da stampare
     */
    void ui_print_section_title(const char* section_name);

    /**
     * @brief Stampa un messaggio di successo formattato a schermo.
     * @param message Messaggio da stampare
     */
    void ui_print_success(const char* message);

    /**
     * @brief Stampa un messaggio di errore formattato a schermo
     * @param message Messaggio da stampare
     */
    void ui_print_error(const char* message);

    /**
     * @brief Stampa un messaggio di avviso formattato a schermo
     * @param message Messaggio da stampare
     */
    void ui_print_warning(const char* message);

    /**
     * @brief Stampa un messaggio a schermo di attesa, bloccando la ui fino a quando non viene premuto un tasto qualsiasi.
     */
    void ui_wait_for_keypress(void);


    /**
     * @brief Stampa il logo del gruppo.
     */
    void ui_print_logo(void);

    /**
    * @brief Stampa i crediti del progetto.
    */
    void ui_print_credits(void);


#endif