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

#endif

