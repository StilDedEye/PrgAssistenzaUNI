//
// Created by andre on 15/05/2026.
//

#include "interfaceBuilder.h"

/*
 *  Controlla la presenza della macro _WIN32 definita dal compiler se se il sistema è windows
 *  ed in caso imposta la codifica utf-8
*/
void initialize_terminal()
{
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
    #endif
}

void cleanup_terminal()
{
    printf(_ANSI_RESET_CURSOR);
    printf(_ANSI_DELETE_REMAINING);
}

void build_requests_table(const Request* arr[], size_t n, bool cleanupTerminal)
{
    // Calcola numero header della tabella
    size_t cols_number = sizeof(requestFieldNames) / sizeof(char*);

    cleanupTerminal ? cleanup_terminal() : printf("\n");

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
                    parseDoubleFloatToString(bufferEstimatedCost, get_request_estimated_cost(arr[i]))
                    : "N/A",
                hasFinalCost ?
                    parseDoubleFloatToString(bufferFinalCost, get_request_final_cost(arr[i]))
                    : "N/A",
                parseDateToString(bufferDate, get_request_creation_date(arr[i]))
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




void print_logo(void) {
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

void print_credits(void) {
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