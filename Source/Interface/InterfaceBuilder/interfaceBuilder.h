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
     * @param selected_column_index Indice della colonna da evidenziare (es. per indicare il criterio di ordinamento).
     * Deve essere un valore tra 0 e il numero di colonne - 1.
     * Se -1 allora non verrà evidenziata nessuna colonna
     *
     * @see Entities/Request/*
     */
    void ui_print_requests_table(const Request* arr[], size_t n, int selected_column_index);

    /**
     * @brief Stampa un riepilogo formattato di una richiesta.
     *
     * @details
     * Mostra a schermo i principali campi descrittivi di una richiesta in una
     * forma sintetica e leggibile, utile ad esempio nella schermata di dettaglio
     * di una singola pratica o in un'anteprima prima della conferma di un'azione.
     * La funzione riceve i valori già pronti come stringhe e li organizza nel
     * layout dell'interfaccia utente.
     *
     * @param request_code   Codice identificativo della richiesta.
     * @param client_name    Nome del cliente associato alla richiesta.
     * @param device_type    Tipo di dispositivo interessato dalla richiesta.
     * @param description    Descrizione del problema o dell'intervento.
     * @param priority       Priorità assegnata alla richiesta.
     * @param estimated_cost Costo stimato dell'intervento.
     * @param opening_date   Data di apertura della richiesta, già formattata come stringa.
     *
     * @note
     * - La funzione non restituisce alcun valore.
     * - I parametri stringa devono essere puntatori validi a stringhe C terminate da '\0'.
     *
     * @see ui_print_requests_table(), ui_print_header(), util_parse_double_to_string()
     */
    void ui_print_request_summary(
        const char* request_code,
        const char* client_name,
        const char* device_type,
        const char* description,
        const char* priority,
        double estimated_cost,
        const char* opening_date);


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
     * @brief Stampa a schermo il percorso di navigazione corrente, ad esempio "Home > Visualizza Richieste > Dettagli Richiesta".
     * @param path
     */
    void ui_print_menu_path(const char* path);


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
     * @brief Mostra un prompt all'utente e legge una stringa di input, memorizzandola in output_buffer.
     * @param prompt Messaggio da mostrare all'utente prima del prompt di input.
     * @param output_buffer Buffer fornito dal chiamante dove verrà scritta la stringa di input. È responsabilità del
     * chiamante assicurare che il buffer sia abbastanza grande.
     * @param buffer_size Grandezza del buffer (output_buffer) in caratteri.
     */
    void ui_get_input_string(const char* prompt, char* output_buffer, size_t buffer_size);

    /**
     * @brief Mostra un prompt di conferma all'utente con un messaggio personalizzato e due opzioni (Choice1/Choice2),
     * rispettivamente gestite come false e true.
     * L'utente può navigare tra le opzioni usando le frecce e confermare la scelta con Invio.
     * @param message Il messaggio da mostrare all'utente.
     * @param choice1 Testo dell'opzione 1 (associata a false)
     * @param choice2 Testo dell'opzione 2 (associata a true)
     * @return false = scelta 1
     * @return true = scelta 2
     */
    bool ui_prompt_confirmation(const char* message, const char* choice1, const char* choice2);


    /**
     * @brief Mostra un prompt di selezione all'utente con un messaggio personalizzato e un elenco di opzioni.
     * L'utente può navigare tra le opzioni usando le frecce su/giù e confermare la scelta con Invio.
     * @param prompt prompt da mostrare all'utente
     * @param options elenco di opzioni disponibili
     * @param options_count numero di opzioni disponibili
     * @return
     */
    int ui_prompt_selection(const char* prompt, const char* options[], size_t options_count);


    /**
     * @brief Mostra un prompt per l'inserimento di una data, con tre campi (giorno, mese, anno) navigabili con le frecce.
     * @details Effettua i controlli sugli anni bisestili e su il rapporto numero di giorni - mese.
     * @param prompt Testo da mostrare all'utente per l'inserimento.
     * @param day Ptr di ritorno contenente il giorno inserito dall'utente (0-30)
     * @param month Ptr di ritorno contenente il mese inserito dall'utente (0-11)
     * @param year Ptr di ritorno contenente l'anno inserito dall'utente.
     */
    void ui_prompt_date (const char* prompt, int* day, int* month, int* year);

    /**
     * @brief Stampa il logo del gruppo.
     */
    void ui_print_logo(void);

    /**
    * @brief Stampa i crediti del progetto.
    */
    void ui_print_credits(void);

    #define UI_INPUT_BUFFER_SIZE 1024


#endif