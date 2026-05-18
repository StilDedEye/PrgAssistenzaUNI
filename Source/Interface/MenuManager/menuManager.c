//
// Created by andre on 15/05/2026.
//

#include "menuManager.h"

#include "../../RequestHandlers/RequestFilter/requestFilter.h"
#include "../../RequestHandlers/RequestOrganizer/requestOrganizer.h"

// Funzioni aggiuntive interne
void launch_menu(
    bool isSubMenu,
    const char *title,
    RequestList *requestList,
    const char **MENU_SUBTREES,
    size_t menuSubtreesLength,
    const ActionFunc *MENU_ACTIONS,
    size_t menuActionsLength
);

void init_root_menu(RequestList *requestList)
{
    ui_initialize_terminal();
    ui_clear_terminal();
    ui_print_logo();
    ui_print_credits();
    printf(_ANSI_HIDE_CURSOR); // Nasconde cursore del terminale
    scanf("%s");
    util_clear_input_buffer();

    launch_menu(
        false,
        "Home",
        requestList,
        MENU_ROOT_SUBTREES,
        sizeof(MENU_ROOT_SUBTREES) / sizeof(char *),
        MENU_ROOT_ACTIONS,
        sizeof(MENU_ROOT_ACTIONS) / sizeof(char *)
    );
}

void launch_menu(
    bool isSubMenu,
    const char *title,
    RequestList *requestList,
    const char **MENU_SUBTREES,
    size_t menuSubtreesLength,
    const ActionFunc *MENU_ACTIONS,
    size_t menuActionsLength
)
{
    int choice = 0;
    bool running = true;

    // Pulisce tutto quello che c'era prima
    ui_clear_terminal();
    while (running)
    {
        ui_reset_cursor();
        ui_print_menu(title, isSubMenu, MENU_SUBTREES, menuSubtreesLength, choice);

        int pressed_key = util_read_key();
        switch (pressed_key)
        {
            case UTIL_KEY_UP:
                if (choice - 1 >= 0)
                    choice--;
                else
                    choice = menuSubtreesLength - 1;
                break;

            case UTIL_KEY_DOWN:
                if (choice + 1 < menuSubtreesLength)
                    choice++;
                else
                    choice = 0;
                break;

            case UTIL_KEY_ENTER:
            case UTIL_KEY_RIGHT:
                if (choice >= 0 && choice < menuActionsLength)
                    MENU_ACTIONS[choice](requestList);
                break;
            case UTIL_KEY_LEFT:
                running = false;
                break;
            default:
                break;
        }
    }
    ui_clear_terminal();
}

// SUBTREES and their LEAFS ===========================================================================

//Subtree[1] VISUALIZZA E CERCA RICHIESTE
void launch_subtree_visualization_research(RequestList *requestList)
{
    launch_menu(
        true,
        "Home > Visualizza e Cerca Richieste",
        requestList,
        MENU_VISUALIZATION_RESEARCH_SUBTREES,
        sizeof(MENU_VISUALIZATION_RESEARCH_SUBTREES) / sizeof(char *),
        MENU_VISUALIZATION_RESEARCH_ACTIONS,
        sizeof(MENU_VISUALIZATION_RESEARCH_ACTIONS) / sizeof(char *)
    );
}

// foglie di Subtree[1]
void launch_leaf_action_show_all(RequestList *requestList)
{
    ui_clear_terminal();
    ui_print_requests_table(requestList->requests, requestList->count, -1);

    ui_wait_for_keypress(_ANSI_STYLE_UNDERLINE"⮌ Premere enter per tornare indietro", UTIL_KEY_ENTER, UTIL_KEY_LEFT);
    ui_clear_terminal();
}

void launch_leaf_search_by_code(RequestList *requestList)
{
    do
    {
        ui_clear_terminal();
        ui_print_menu_path("Home > Visualizza e Cerca Richieste > Cerca Richiesta tramite Codice");

        char inputBuffer[UI_INPUT_BUFFER_SIZE];
        // Chiede all'utente di inserire un codice di richiesta da cercare, facendo gli appositi controlli
        ui_get_input_string("\nInserisci il codice della richiesta da cercare: ", inputBuffer, UI_INPUT_BUFFER_SIZE);

        // Converte la stringa in maiuscolo
        strupr(inputBuffer);
        // Ordina il vettore di richieste in modo crescente per codice, in modo da poter applicare la ricerca dicotomica
        //TODO Cambiare parametro sorting
        merge_sort(requestList->requests, 0, requestList->count - 1, sort_by_client_name, CRESCENT_SORTING);

        // Filtra le richieste, salvando in una nuova requestList locale il risultato dell'operazione
        RequestList *filteredRequestsList = search_by_request_id(requestList, inputBuffer);
        size_t filteredRequestsListLength = filteredRequestsList->count;
        Request **filteredRequests = filteredRequestsList->requests;

        ui_print_requests_table(filteredRequests, filteredRequestsListLength, 0);
        // Libera la memoria allocata
        destroy_request_list(filteredRequestsList);
    } while (!ui_prompt_confirmation("Vuoi effettuare altre ricerche?", "Si", "No"));
    ui_clear_terminal();
}

void launch_leaf_sorting(RequestList *requestList)
{
    int choice = 0;
    int order = 0;
    bool running = true;

    do {
        ui_clear_terminal();
        // Stampa il percorso attuale del sottomenu
        ui_print_menu_path("Home > Visualizza e Cerca Richieste > Ordinamento");

        printf(
            _ANSI_COLOR_PRIMARY _ANSI_STYLE_FAINT "\n[←→] Cambia Criterio   •   [↑↓] Ordine (Asc/Desc)   •  "
            _ANSI_COLOR_SUCCESS "[Enter] Conferma " _ANSI_COLOR_STYLE_RESET "\n\n");

        printf(_ANSI_DELETE_LINE);
        printf("Le richieste verranno ordinate per ");
        printf("[" _ANSI_COLOR_PRIMARY _ANSI_STYLE_ITALIC "%s" _ANSI_COLOR_STYLE_RESET "] ", SORTING_OPTIONS[choice]);
        printf("in ordine [" _ANSI_COLOR_SECONDARY _ANSI_STYLE_ITALIC "%s" _ANSI_COLOR_STYLE_RESET "] ",
               SORTING_ORDERS[order]);

        int pressed_key = util_read_key();
        switch (pressed_key)
        {
            case UTIL_KEY_UP:
                if (order == 0) order = 1;
                else order = 0;
                break;

            case UTIL_KEY_DOWN:
                if (order == 1) order = 0;
                else order = 1;
                break;

            case UTIL_KEY_LEFT:
                if (choice - 1 >= 0)
                    choice--;
                else
                    choice = sizeof(SORTING_OPTIONS) / sizeof(char *) - 1;
                break;
            case UTIL_KEY_RIGHT:
                if (choice + 1 < sizeof(SORTING_OPTIONS) / sizeof(char *))
                    choice++;
                else
                    choice = 0;
                break;

            case UTIL_KEY_ENTER:
                size_t selected_column_index = 0;
                switch (choice)
                {
                    case 0:
                        request_list_sort(requestList, sort_by_client_name,
                                          order == 0 ? DESCENT_SORTING : CRESCENT_SORTING);
                        selected_column_index = 2;
                        break;
                    case 1:
                        request_list_sort(requestList, sort_by_device, order == 0 ? DESCENT_SORTING : CRESCENT_SORTING);
                        selected_column_index = 3;
                        break;
                    case 2:
                        request_list_sort(requestList, sort_by_priority, order == 0 ? DESCENT_SORTING : CRESCENT_SORTING);
                        selected_column_index = 4;
                        break;
                    case 3:
                        request_list_sort(requestList, sort_by_status, order == 0 ? DESCENT_SORTING : CRESCENT_SORTING);
                        selected_column_index = 5;
                        break;
                    case 4:
                        request_list_sort(requestList, sort_by_estimated_cost,
                                          order == 0 ? DESCENT_SORTING : CRESCENT_SORTING);
                        selected_column_index = 7;
                        break;
                    case 5:
                        request_list_sort(requestList, sort_by_priority, order == 0 ? DESCENT_SORTING : CRESCENT_SORTING);
                        selected_column_index = 9;
                        break;
                    default:
                        break;
                }
                printf("\n");
                ui_print_requests_table(requestList->requests, requestList->count, selected_column_index);

                running = ui_prompt_confirmation("Vuoi effettuare altri ordinamenti?", "No", "Si");

                break;

            default:
                break;
        }
    } while (running);

    ui_clear_terminal();
}

// Subtree[2] GESTIONE E MODIFICA RICHIESTE
void launch_subtree_manage(RequestList *requestList)
{
    launch_menu(
        true,
        "Home > Gestione e Modifica Richieste",
        requestList,
        MENU_ROOT_SUBTREES,
        sizeof(MENU_MANAGE_SUBTREES) / sizeof(char *),
        MENU_MANAGE_ACTIONS,
        sizeof(MENU_MANAGE_ACTIONS) / sizeof(char *)
    );
}
