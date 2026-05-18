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
        ui_get_input_string("\nInserisci il codice della richiesta da cercare", inputBuffer, UI_INPUT_BUFFER_SIZE);

        // Converte la stringa in maiuscolo
        strupr(inputBuffer);
        // Ordina il vettore di richieste in modo crescente per codice, in modo da poter applicare la ricerca dicotomica

        merge_sort(requestList->requests, 0, requestList->count - 1, sort_by_request_id, CRESCENT_SORTING);

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
                        request_list_sort(requestList, sort_by_creation_date, order == 0 ? DESCENT_SORTING : CRESCENT_SORTING);
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
        MENU_MANAGE_SUBTREES,
        sizeof(MENU_MANAGE_SUBTREES) / sizeof(char *),
        MENU_MANAGE_ACTIONS,
        sizeof(MENU_MANAGE_ACTIONS) / sizeof(char *)
    );
}
void launch_leaf_insert_request(RequestList* requestList)
{
    ui_clear_terminal();

    char name_buffer[NAME_BUFFER_SIZE];
    char desc_buffer[DESCRIPTION_BUFFER_SIZE];
    char buffer_date[UTIL_DATE_PARSER_BUFFER_SIZE];
    int index_of_selected_device = 0;
    int index_of_selected_priority = 0;
    double estimated_cost = -1.0;
    int day = 0, month = 0, year = 0;
    struct tm request_date = {0};


    ui_print_menu_path("Home > Gestione e Modifica Richieste > Inserisci nuova richiesta");

    // TODO Mettere numero stimato prossima richiesta IN AUTOMATICO
    // TODO SISTEMARE INSERIMENTO SOTTO CON IL CODICE GIUSTO
    ui_print_request_summary("RQ-* TODO",NULL,NULL,NULL,NULL,VAL_UNDEFINED,NULL);


    // Prende il nome del cliente dall'utente
    ui_get_input_string("\nInserisci il nome del cliente", name_buffer, NAME_BUFFER_SIZE);
    ui_clear_terminal();
    ui_print_menu_path("Home > Gestione e Modifica Richieste > Inserisci nuova richiesta");
    ui_print_request_summary("RQ-* TODO",name_buffer,NULL,NULL,NULL,VAL_UNDEFINED,NULL);

    printf("\n");
    // Prende il tipo di device
    printf("" _ANSI_STYLE_FAINT _ANSI_COLOR_PRIMARY "([↑↓] Scorri • [Enter] Conferma) " _ANSI_COLOR_STYLE_RESET "\n\n");
    index_of_selected_device = ui_prompt_selection("Seleziona il tipo di dispositivo", deviceNames, sizeof(deviceNames) / sizeof(char *));
    ui_clear_terminal();
    ui_print_menu_path("Home > Gestione e Modifica Richieste > Inserisci nuova richiesta");
    ui_print_request_summary("RQ-* TODO",name_buffer,deviceNames[index_of_selected_device],NULL,NULL,VAL_UNDEFINED,NULL);

    printf("\n");
    // Prende la descrizione
    ui_get_input_string("Inserisci la descrizione della richiesta", desc_buffer, DESCRIPTION_BUFFER_SIZE);
    ui_clear_terminal();
    ui_print_menu_path("Home > Gestione e Modifica Richieste > Inserisci nuova richiesta");
    ui_print_request_summary("RQ-* TODO",name_buffer,deviceNames[index_of_selected_device],desc_buffer,NULL,VAL_UNDEFINED,NULL);

    printf("\n");
    // Prende la priorita'
    printf("" _ANSI_STYLE_FAINT _ANSI_COLOR_PRIMARY "([↑↓] Scorri • [Enter] Conferma) " _ANSI_COLOR_STYLE_RESET "\n\n");
    index_of_selected_priority = ui_prompt_selection("Seleziona la priorita' della richiesta", priorityNames, sizeof(priorityNames) / sizeof(char *));
    ui_clear_terminal();
    ui_print_menu_path("Home > Gestione e Modifica Richieste > Inserisci nuova richiesta");
    ui_print_request_summary("RQ-* TODO",name_buffer,deviceNames[index_of_selected_device],desc_buffer,priorityNames[index_of_selected_priority],VAL_UNDEFINED,NULL);

    // Prende il costo stimato
    do
    {
        printf("\n");
        printf(_ANSI_STYLE_FAINT "%s: " _ANSI_COLOR_STYLE_RESET, "Inserisci il costo stimato in € ");
        scanf("%lf", &estimated_cost);
        if (estimated_cost < 0)
        {
            ui_print_error("Il costo stimato DEVE essere numerico e positivo. Riprova.");
            util_clear_input_buffer();
            printf("\n");
        }
    } while (estimated_cost < 0);
    ui_clear_terminal();
    ui_print_menu_path("Home > Gestione e Modifica Richieste > Inserisci nuova richiesta");
    ui_print_request_summary("RQ-* TODO",name_buffer,deviceNames[index_of_selected_device],desc_buffer,priorityNames[index_of_selected_priority], estimated_cost,NULL);

    printf("\n");
    // Prende la data
    printf(_ANSI_STYLE_FAINT "%s: " _ANSI_COLOR_STYLE_RESET, "([↑↓ / ←→] Cambia / Seleziona • [Enter] Conferma)");
    ui_prompt_date ("Inserici la data di apertura: ", &day, &month, &year);
    request_date =  build_date(++day, month, year);
    ui_clear_terminal();
    ui_print_menu_path("Home > Gestione e Modifica Richieste > Inserisci nuova richiesta");
    ui_print_request_summary("RQ-* TODO",name_buffer,deviceNames[index_of_selected_device],desc_buffer,priorityNames[index_of_selected_priority], estimated_cost,util_parse_date_to_string(buffer_date, request_date));

    // Inserisce nuova richiesta nel vettore
    Client* new_client = create_client("CL-*", name_buffer);
    Request* new_request = create_request("RQ-4", new_client, index_of_selected_device, index_of_selected_priority, desc_buffer, estimated_cost, VAL_UNDEFINED, request_date);
    if (add_request(requestList, new_request) == 0)
        ui_print_success("Richiesta inserita con successo!");
    else
        ui_print_error("Si è verificato un errore durante l'inserimento della richiesta. Riprova.");

    // Pulisce il terminale
    ui_wait_for_keypress(_ANSI_STYLE_UNDERLINE"\n⮌ Premere enter per tornare indietro", UTIL_KEY_ENTER, UTIL_KEY_LEFT);
    ui_clear_terminal();
    util_clear_input_buffer();


}
