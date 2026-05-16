//
// Created by andre on 15/05/2026.
//

#include "menuManager.h"

#include <stdlib.h>

void init_menu()
{
    initialize_terminal();
    cleanup_terminal();
    print_logo();
    print_credits();

    // Carica da file?
}

// void mostra_menu_principale(void) {
//     int scelta;
//     do {
//
//         stampa_grafica_menu_principale();
//
//
//         scelta = prendi_input_intero(0, 4);
//
//
//         switch (scelta) {
//             case 1:
//                 mostra_sottomenu_visualizza();
//                 break;
//             case 2:
//                 mostra_sottomenu_gestione();
//                 break;
//             case 3:
//                 mostra_sottomenu_filtri();
//                 break;
//             case 4:
//                 mostra_sottomenu_report();
//                 break;
//             case 0:
//                 salva_richieste_su_file("richieste.txt");
//                 break;
//         }
//     } while (scelta != 0);
// }

// void mostra_sottomenu_visualizza(void) {
//     char scelta;
//     do {
//         stampa_grafica_sottomenu_visualizza();
//         scelta = prendi_input_carattere();
//
//         switch (scelta) {
//             case '1':
//
//                 azione_mostra_elenco_completo();
//                 break;
//             case '2':
//                 azione_cerca_tramite_codice();
//                 break;
//             case '3':
//                 azione_ordina_costo_stimato();
//                 break;
//             case '4':
//                 mostra_mini_prompt_ordinamento_personalizzato();
//                 break;
//             case 'B':
//             case 'b':
//
//                 break;
//             default:
//                 printf("Opzione non valida!\n");
//         }
//     } while (scelta != 'B' && scelta != 'b');
// }