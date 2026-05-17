//
// Created by andre on 15/05/2026.
//

#ifndef PRGASSISTENZAUNI_INTERFACECONSTANTS_H
     #define PRGASSISTENZAUNI_INTERFACECONSTANTS_H



     // Operazioni su Terminale
     /**
      * @brief Riporta il cursore del terminale nella posizione iniziale (0,0).
      * @details Utilizza la sequenza di escape ANSI per spostare il cursore in alto
      *          a sinistra senza cancellare il contenuto del terminale.
      * @code
      * printf("%s Utente n. %d", _ANSI_RESET_CURSOR, 1);
      * @endcode
      */
     #define _ANSI_RESET_CURSOR "\033[H"

     /**
      * @brief Cancella il testo della riga corrente nel terminale.
      * @details Utilizza la sequenza di escape ANSI per cancellare tutti i caratteri a partire dalla posizione attuale del cursore
      *          fino alla fine della riga. Il cursore non viene spostato.
      * @code
      * printf("%s Utente n° %d", _ANSI_DELETE_LINE, 1);
      * @endcode
      */
     #define _ANSI_DELETE_LINE "\033[K"

     /**
      * @brief Cancella tutto il testo a partire dalla posizione attuale del cursore fino alla fine dello schermo.
      * @details Utilizza la sequenza di escape ANSI per cancellare tutto il testo a partire dalla posizione del cursore
      *          fino alla fine dello schermo. Il cursore non viene spostato
      * @code
      * printf("%s Utente n° %d", _ANSI_DELETE_REMAINING, 1);
      * @endcode
      */
     #define _ANSI_DELETE_REMAINING "\033[J"

     /**
      * @brief Pulisce completamente il terminale
      * @details Utilizza la sequenza di escape ANSI per cancellare tutto il testo presente nel terminale
      * e riportare il cursore in alto a sinistra (0,0).
      * @code
      * printf("%s", _ANSI_CLEAR_SCREEN);
      * @endcode
      */
     #define _ANSI_CLEAR_SCREEN "\033[2J"

    /**
      * @brief Nasconde il cursore del terminale tramite sequenza di escape ANSI.
      * @code
      * printf("%s", _ANSI_HIDE_CURSOR);
      * @endcode
      */
     #define _ANSI_HIDE_CURSOR "\x1b[?25l"

    /**
      * @brief Mostra il cursore del terminale tramite sequenza di escape ANSI.
      * @code
      * printf("%s", _ANSI_HIDE_CURSOR);
      * @endcode
      */
     #define _ANSI_SHOW_CURSOR "\x1b[?25h"

    // Codici Colore ANSI
    #define ANSI_COLOR_RESET   "\x1b[0m"
    #define ANSI_COLOR_PRIMARY  "\x1b[1;33m" // Primario | Giallo
    #define ANSI_COLOR_SECONDARY    "\x1b[1;36m" // Secondario | Ciano
    #define ANSI_COLOR_SUCCESS   "\x1b[1;32m" // Successo | Verde
    #define ANSI_COLOR_ERROR     "\x1b[1;31m" // Errore | Rosso
    #define ANSI_COLOR_TERTIARY    "\x1b[90m"   // Neutro | Grigio
    #define ANSI_BG_SELECTED "\x1b[30;43m"  // Per testo selezionato

#endif

