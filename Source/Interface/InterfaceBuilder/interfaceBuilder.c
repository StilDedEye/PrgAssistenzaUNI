//
// Created by andre on 15/05/2026.
//

#include "interfaceBuilder.h"

/*
 *  Controlla la presenza della macro _WIN32 definita dal compiler se se il sistema è windows
 *  ed in caso imposta la codifica utf-8
*/
void ui_initialize_terminal()
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
}

void ui_clear_terminal()
{
    printf(_ANSI_RESET_CURSOR);
    printf(_ANSI_DELETE_REMAINING);
}

void ui_print_requests_table(const Request* arr[], size_t n, bool cleanupTerminal)
{
    // Calcola numero header della tabella
    size_t cols_number = sizeof(requestFieldNames) / sizeof(char*);

    cleanupTerminal ? ui_clear_terminal() : printf("\n");

    // Alloca mem dinamica per la struttura della tabella, ritornando un puntatore
    ft_table_t *table = ft_create_table();

    // Imposta lo stile dei bordi
    ft_set_border_style(table, FT_SOLID_ROUND_STYLE);

    // Scrive titolo della tabella
    ft_u8write_ln(table, "ELENCO RICHIESTE DI ASSISTENZA");

    // Imposta proprietà celle in posizione [0][0]: imposta cell span
    ft_set_cell_span(table, 0, 0, cols_number);
    // Imposta proprietà celle in posizione [0][0]: imposta colore e allineamento
    ft_set_cell_prop(table, 0, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    ft_set_cell_prop(table, 0, 0, FT_CPROP_CONT_FG_COLOR, FT_COLOR_RED);


    // Imposta proprietà celle in posizione [0][*]: il tipo di riga è un header
    ft_set_cell_prop(table, 1, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    // Scrive i nomi delle colonne (header)
    ft_row_write_ln( table, cols_number, requestFieldNames);

    // Scrive le righe della tabella
    if (n == 0)
    {
        ft_u8write_ln(table, "Nessuna richiesta trovata");
        // Imposta proprietà celle in posizione [1][0]: imposta cell span
        ft_set_cell_span(table, 2, 0, cols_number);
        // Imposta proprietà celle in posizione [1][0]: allinea al centro il contenuto
        ft_set_cell_prop(table, 2, 0, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
        ft_set_cell_prop(table, 2, 0, FT_CPROP_CONT_FG_COLOR, FT_COLOR_RED);
    }
    else
    {
        for (size_t i = 0; i < n; i++)
        {
            char bufferEstimatedCost[UTIL_FLOAT_PARSER_BUFFER_SIZE];
            bool hasEstimatedCost = false;
            if (get_request_estimated_cost(arr[i]) != VAL_UNDEFINED)
                hasEstimatedCost = true;

            char bufferFinalCost[UTIL_FLOAT_PARSER_BUFFER_SIZE];
            bool hasFinalCost = false;
            if (get_request_final_cost(arr[i]) != VAL_UNDEFINED)
                hasFinalCost = true;

            char bufferDate[UTIL_DATE_PARSER_BUFFER_SIZE];

            ft_u8write_ln(table,
                get_request_id(arr[i]),
                get_client_id(get_request_client(arr[i])),
                get_client_name(get_request_client(arr[i])),
                deviceNames[get_request_device(arr[i])],
                priorityNames[get_request_priority(arr[i])],
                requestStatusNames[get_request_status(arr[i])],
                get_request_description(arr[i]),
                hasEstimatedCost ?
                    util_parse_double_to_string(bufferEstimatedCost, get_request_estimated_cost(arr[i]))
                    : "N/A",
                hasFinalCost ?
                    util_parse_double_to_string(bufferFinalCost, get_request_final_cost(arr[i]))
                    : "N/A",
                util_parse_date_to_string(bufferDate, get_request_creation_date(arr[i]))
                );
        }
        // Imposta proprietà celle in posizione [*][*]: allinea al centro il contenuto
        ft_set_cell_prop(table, FT_ANY_ROW, FT_ANY_ROW, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);
    }

    // Stampa della tabella
    printf("%s\n", ft_to_string(table));
    fflush(stdout);

    // Dealloca la memoria usata dalla tabella
    ft_destroy_table(table);
}

void ui_print_header(const char* title)
{
    // Lunghezza costante del menu
    const int TOTAL_WIDTH = 68;
    int title_len = (int)strlen(title);

    // Spazio interno disponibile per il testo, considerando un padding destro e sinistro di 2 caratteri ciascuno
    int inner_width = TOTAL_WIDTH - 4;

    // Attiva colore primario
    printf(ANSI_COLOR_PRIMARY);

    // Stampa il bordo superiore, del tipo "╔═════════╗"
    printf("╔");
    for (int i = 0; i < TOTAL_WIDTH - 2; i++) {
        printf("═");
    }
    printf("╗\n");

    // Stampa l'header, centrato, del tipo "║   TITOLO   ║"
    printf("║ ");
    if (title_len <= inner_width) {
        // Calcola quanto padding interno serve a destra e a sinistra
        int space_left = (inner_width - title_len) / 2;
        int space_right = inner_width - title_len - space_left;

        // Aggiunge padding a sinistra
        for (int i = 0; i < space_left; i++) {
            printf(" ");
        }

        // Aggiunge il titolo
        printf("%s", title);

        // Aggiunge padding a sinistra
        for (int i = 0; i < space_right; i++) {
            printf(" ");
        }
    } else {
        /*
         * Se viene passato un titolo più lungo di TOTAL_WIDTH, viene tagliato
         * per non compromettere il terminale
         */
        printf("%.*s...", inner_width - 3, title);
    }
    printf(" ║\n");

    // Stampa il bordo inferiore, del tipo "╚═════════╝"
    printf("╚");
    for (int i = 0; i < TOTAL_WIDTH - 2; i++) {
        printf("═");
    }
    printf("╝\n");

    // Resetta il colore per i testi successivi
    printf(ANSI_COLOR_RESET "\n");
}

void ui_print_section_title(const char* section_name) {
    printf(ANSI_COLOR_SECONDARY "--- %s ---\n" ANSI_COLOR_RESET "\n", section_name);
}

void ui_print_success(const char* message) {
    printf("\n" ANSI_COLOR_SUCCESS "[✓] %s" ANSI_COLOR_RESET "\n", message);
}

void ui_print_error(const char* message) {
    printf("\n" ANSI_COLOR_ERROR "[ERRORE] %s" ANSI_COLOR_RESET "\n", message);
}

void ui_print_warning(const char* message) {
    printf("\n" ANSI_COLOR_PRIMARY "[ATTENZIONE] %s" ANSI_COLOR_RESET "\n", message);
}

void ui_wait_for_keypress(void) {
    printf("\n" ANSI_COLOR_TERTIARY "Press ENTER to continue..." ANSI_COLOR_RESET);
    getchar();
}




void ui_print_logo(void) {
    // \033[1;33m ANSI per attivare il colore giallo/arancione
    printf("\033[1;33m");

    printf(".------------------------------------------------------------.\n");
    printf("|   ██████╗ ██████╗ ██╗███╗   ███╗                           |\n");
    printf("|   ██╔══██╗██╔══██╗██║████╗ ████║                           |\n");
    printf("|   ██║  ██║██████╔╝██║██╔████╔██║                           |\n");
    printf("|   ██║  ██║██╔══██╗██║██║╚██╔╝██║                           |\n");
    printf("|   ██████╔╝██║  ██║██║██║ ╚═╝ ██║                           |\n");
    printf("|   ╚═════╝ ╚═╝  ╚═╝╚═╝╚═╝     ╚═╝                           |\n");
    printf("|                                                            |\n");
    printf("|   ███████╗████████╗██╗   ██╗██████╗ ██╗ ██████╗ ███████╗   |\n");
    printf("|   ██╔════╝╚══██╔══╝██║   ██║██╔══██╗██║██╔═══██╗██╔════╝   |\n");
    printf("|   ███████╗   ██║   ██║   ██║██║  ██║██║██║   ██║███████╗   |\n");
    printf("|   ╚════██║   ██║   ██║   ██║██║  ██║██║██║   ██║╚════██║   |\n");
    printf("|   ███████║   ██║   ╚██████╔╝██████╔╝██║╚██████╔╝███████║   |\n");
    printf("|   ╚══════╝   ╚═╝    ╚═════╝ ╚═════╝ ╚═╝ ╚═════╝ ╚══════╝   |\n");
    printf("'------------------------------------------------------------'\n");

    printf("\033[0m"); // RESET del colore
    printf("\n");
}

void ui_print_credits(void) {
    const char *YELLOW = "\033[1;33m";
    const char *WHITE = "\033[1;37m";
    const char *RESET = "\033[0m";

    printf("%s.------------------------------------------------------------.%s\n", YELLOW, RESET);

    // Riga: Made by
    printf("%s| %s%-10s%s%-49s%s|%s\n",
           YELLOW, YELLOW, "Made by:", WHITE, "Andrea Silvani, Alessandro Zaccagnino", YELLOW, RESET);

    // Riga: Corso
    printf("%s| %s%-10s%s%-49s%s|%s\n",
           YELLOW, YELLOW, "Corso:", WHITE, "Laboratorio di Informatica | Primo Appello", YELLOW, RESET);

    // Riga: Anno
    printf("%s| %s%-10s%s%-49s%s|%s\n",
           YELLOW, YELLOW, "Anno:", WHITE, "2025/2026", YELLOW, RESET);

    // Riga: System
    printf("%s| %s%-10s%s%-49s%s|%s\n",
           YELLOW, YELLOW, "Progetto:", WHITE, "Gestione Richieste di Assistenza Tecnica - v1.0", YELLOW, RESET);

    printf("%s'------------------------------------------------------------'%s\n", YELLOW, RESET);
    printf("\n");
}