//
// Created by aless on 15/05/2026.
//

// // Macro ANSI per gestire il terminale
// #define ANSI_RESET_CURSORE "\033[H"  // Porta il cursore in alto a sinistra (0,0)
// #define ANSI_CANCELLA_LINEA "\033[K" // Cancella la riga corrente dal cursore in poi
//
// void stampa_elenco(int evidenziato) {
//     // 1. Invece di pulire lo schermo, resettiamo solo la posizione del cursore
//     printf(ANSI_RESET_CURSORE);
//
//     printf("--- ELENCO UTENTI DINAMICO ---\n");
//
//     // 2. Stampiamo le righe sovrascrivendo quelle vecchie
//     // Usiamo ANSI_CANCELLA_LINEA per evitare che scritte vecchie più lunghe rimangano visibili
//     printf("%s%s 1. Alessandro (Admin)\n", ANSI_CANCELLA_LINEA, (evidenziato == 1) ? "-> " : "   ");
//     printf("%s%s 2. Giovanni (User)\n",   ANSI_CANCELLA_LINEA, (evidenziato == 2) ? "-> " : "   ");
//     printf("%s%s 3. Maria (User)\n",      ANSI_CANCELLA_LINEA, (evidenziato == 3) ? "-> " : "   ");
//     printf("%s%s 4. Lucia (Guest)\n",     ANSI_CANCELLA_LINEA, (evidenziato == 4) ? "-> " : "   ");
//
//     printf("------------------------------\n");
//
//     // Forza il terminale a mostrare l'output immediatamente senza fare buffering
//     fflush(stdout);
// }
//
// int main() {
//     // Pulisce lo schermo solo all'AVVIO del programma per pulire la vecchia shell
//     printf("\033[2J");
//
//     // Simuliamo il movimento del cursore sull'elenco senza input
//     for (int i = 1; i <= 4; i++) {
//         stampa_elenco(i);
//         usleep(500000); // Aspetta mezzo secondo
//     }
//
//     return 0;
// }