//
// Created by andre on 15/05/2026.
//

#ifndef PRGASSISTENZAUNI_INTERFACEBUILDER_H
    #define PRGASSISTENZAUNI_INTERFACEBUILDER_H

    #include <stdio.h>
    #include "../../../ExternalLibraries/fort/fort.h"
    #include "../interfaceConstants.h"
    #include <string.h>

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
     * @brief Riporta il cursore del terminale nella posizione iniziale (0,0).
     * @details Utilizza la sequenza di escape ANSI per spostare il cursore in alto a sinistra senza cancellare
     * il contenuto del terminale.
     */
    void ui_reset_cursor(void);

    /**
     * @brief Costruisce e visualizza la tabella delle richieste.
     * @details Utilizza la libreria fort per creare una tabella formattata con i dati delle richieste.
     * @param arr Vettore di struct Request
     * @param n Numero di elementi nel vettore arr
     * @see Entities/Request/*
     */
    void ui_print_requests_table(const Request* arr[], size_t n);

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
     * @brief Stampa un elemento di menu formattato a schermo, evidenziando se è selezionato o meno.
     * @param item_name Il nome dell'elemento
     * @param selected Boolean per indicare se l'elemento è selezionato o meno.
     */
    static void ui_print_menu_item(const char* item_name, bool selected);


    /**
     * @brief Stampa un menu formattato a schermo, evidenziando l'opzione attualmente selezionata.
     * @param title Titolo del menu. Se NULL non stampa il section_title associato.
     * @param isSubMenu Boolean che indica se il menu è un sottomenu o meno. Se true, il menu avrà un aspetto più compatto.
     * @param options Tutte le opzioni del menu, in un array di stringhe. Non deve essere NULL.
     * @param n_options Numero di opzioni presenti.
     * @param selected_option Indice dell'opzione attualmente selezionata in options.
     */
    void ui_print_menu(const char* title, bool isSubMenu, const char* options[], size_t n_options, size_t selected_option);

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
     * @brief Stampa un messaggio a schermo di attesa, bloccando la ui fino a quando
     * non viene premuto uno dei tasti passati. Keypress deve essere un valore tra quelli
     * definiti in Util.h, altrimenti la funzione entrerà in loop.
     * @param message Messaggio da stampare
     * @param keypress1 Codice del tasto che deve essere premuto per sbloccare la UI.
     * Deve essere un valore tra quelli definiti in Util.h (es. UTIL_KEY_ENTER, UTIL_KEY_UP, etc.)
     * @param keypress2 Codice del secondo tasto che può essere premuto per sbloccare la UI.
     * Se non si vuole un secondo tasto, passare UTIL_KEY_UNDEFINED.
     */
    void ui_wait_for_keypress(const char* message, int keypress1, int keypress2);


    /**
     * @brief Stampa il logo del gruppo.
     */
    void ui_print_logo(void);

    /**
    * @brief Stampa i crediti del progetto.
    */
    void ui_print_credits(void);


#endif