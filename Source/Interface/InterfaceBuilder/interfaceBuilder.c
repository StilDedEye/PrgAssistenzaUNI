//
// Created by andre on 15/05/2026.
//

#include "interfaceBuilder.h"

/**
 * @brief Stampa un messaggio di istruzioni per l'utente, invitandolo a premere il tasto ENTER per continuare.
 */
static void ui_print_menu_instructions(void);

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

void ui_reset_cursor()
{
    printf(_ANSI_RESET_CURSOR);
}

void ui_print_requests_table(const Request* arr[], size_t n, int selected_column_index)
{
    // Calcola numero header della tabella
    size_t cols_number = sizeof(requestFieldNames) / sizeof(char*);

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
    ft_set_cell_prop(table, 0, 0, FT_CPROP_CONT_FG_COLOR, FT_COLOR_YELLOW);


    // Imposta proprietà celle in posizione [1][*]: il tipo di riga è un header
    ft_set_cell_prop(table, 1, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    // Scrive i nomi delle colonne (header)
    ft_row_write_ln(table, cols_number, requestFieldNames);
    // Evidenzia colonna selezionata, se parametro diverso da -1
    if (selected_column_index != -1 && selected_column_index < cols_number)
        ft_set_cell_prop(table, 1, selected_column_index, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_GREEN);


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
            // Gestione casting estimated cost
            char bufferEstimatedCost[UTIL_FLOAT_PARSER_BUFFER_SIZE];
            bool hasEstimatedCost = false;
            if (get_request_estimated_cost(arr[i]) != VAL_UNDEFINED)
                hasEstimatedCost = true;

            // Gestione casting final cost
            char bufferFinalCost[UTIL_FLOAT_PARSER_BUFFER_SIZE];
            bool hasFinalCost = false;
            if (get_request_final_cost(arr[i]) != VAL_UNDEFINED)
                hasFinalCost = true;

            // buffer per data, usato nel parsing
            char bufferDate[UTIL_DATE_PARSER_BUFFER_SIZE];

            char bufferDesc[64];
            // snprintf con "%.*s" prende come argomento prima il limite (max_chars = 20) e poi la stringa originaria
            // Se la stringa è più corta di max_chars, la copia tutta. Se è più lunga, la tronca.
            snprintf(bufferDesc, sizeof(bufferDesc), "%.*s...", 20, get_request_description(arr[i]));

            ft_u8write_ln(table,
                get_request_id(arr[i]),
                get_client_id(get_request_client(arr[i])),
                get_client_name(get_request_client(arr[i])),
                deviceNames[get_request_device(arr[i])],
                priorityNames[get_request_priority(arr[i])],
                requestStatusNames[get_request_status(arr[i])],
                bufferDesc,
                hasEstimatedCost ?
                    util_parse_double_to_string(bufferEstimatedCost, get_request_estimated_cost(arr[i]))
                    : "N/A",
                hasFinalCost ?
                    util_parse_double_to_string(bufferFinalCost, get_request_final_cost(arr[i]))
                    : "N/A",
                util_parse_date_to_string(bufferDate, get_request_creation_date(arr[i]))
                );
            // Evidenzia elementi della colonna selezionata, se parametro diverso da -1
            if (selected_column_index != -1 && selected_column_index < cols_number)
                ft_set_cell_prop(table, i+2, selected_column_index, FT_CPROP_CONT_FG_COLOR, FT_COLOR_LIGHT_GREEN);

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
    printf(_ANSI_COLOR_PRIMARY);

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
    printf("╝");

    // Resetta il colore per i testi successivi
    printf(_ANSI_COLOR_STYLE_RESET "\n");
}

void ui_print_section_title(const char* section_name)
{
    if (section_name == NULL) return;

    // Lunghezza del sottomenu
    const int SECTION_WIDTH = 100;

    printf(_ANSI_COLOR_SECONDARY);

    // Bordo superiore del sottomenu
    printf("┌─[ 🗁  %s ]", section_name);

    /* Calcola quanti trattini mancano per completare la linea fino a SECTION_WIDTH
        Sottrae i caratteri fissi: '┌', '─', '[', ' ', ' ', ' ', ']', '┐' (8 caratteri)
        e i 2 caratteri dell'icona */
    int written_chars = (int)strlen(section_name) + 10;
    int remaining_dashes = SECTION_WIDTH - written_chars;

    // Fallback se il nome è troppo lungo
    if (remaining_dashes > 0) {
        for (int i = 0; i < remaining_dashes; i++) {
            printf("─");
        }
    }
    printf("┐\n");

    printf(_ANSI_COLOR_STYLE_RESET);
}

void ui_print_menu_path(const char* path)
{
    printf(_ANSI_COLOR_SECONDARY);

    // Bordo superiore del sottomenu
    printf("┌─[ 🗁  %s ]\n", path);
    printf(_ANSI_COLOR_STYLE_RESET);
}

static void ui_print_menu_item(const char* item_name, bool selected)
{
    if (item_name == NULL) return;
    if (selected)
    {
        char* str = malloc(strlen(item_name) + 1);
        strcpy(str, item_name);
        printf(_ANSI_COLOR_PRIMARY);
        // strupr applica un uppercase su tutta la stringa
        printf("\n➤  %s", strupr(str));
        printf(_ANSI_COLOR_STYLE_RESET);
        free(str);
        str = NULL;
    }
    else printf(_ANSI_COLOR_TERTIARY "\n⬝  %s" _ANSI_COLOR_STYLE_RESET, item_name);
}

void ui_print_menu(const char* title, bool isSubMenu, const char* options[], size_t n_options, size_t selected_option)
{
    if (options == NULL || n_options == 0) return;

    if (title != NULL)
        if (isSubMenu)
            ui_print_section_title(title);
        else
            ui_print_header(title);


    for (size_t i = 0; i < n_options; i++)
    {
        ui_print_menu_item(options[i], i == selected_option);
    }
    ui_print_menu_instructions();
}


void ui_print_success(const char* message)
{
    printf("\n" _ANSI_COLOR_SUCCESS "[✓] %s" _ANSI_COLOR_STYLE_RESET "\n", message);
}

void ui_print_error(const char* message)
{
    printf("\n" _ANSI_COLOR_ERROR "[ERRORE] %s" _ANSI_COLOR_STYLE_RESET "\n", message);
}

void ui_print_warning(const char* message)
{
    printf("\n" _ANSI_COLOR_PRIMARY "[ATTENZIONE] %s" _ANSI_COLOR_STYLE_RESET "\n", message);
}

void ui_wait_for_keypress(const char* message, int keypress1, int keypress2)
{
    printf("\n " _ANSI_COLOR_TERTIARY "%s" _ANSI_COLOR_STYLE_RESET, message);
    if (keypress2 == UTIL_KEY_UNDEFINED)
        keypress2 = keypress1; // Se non è definito un secondo tasto

    while (util_read_key() != keypress1 && util_read_key() != keypress2);
}

static void ui_print_menu_instructions(void)
{
    printf("\n\n" _ANSI_STYLE_FAINT
           "  [↑↓] Naviga   •   [→ / Enter] Conferma   •   [←] Torna indietro\x1b[K\n"
           _ANSI_COLOR_STYLE_RESET);
}

void ui_get_input_string(const char* prompt, char* output_buffer, size_t buffer_size)
{
    if (prompt == NULL || output_buffer == NULL || buffer_size == 0) return;

    // Mostra il prompt in uno stile secondario/sbiadito per non appesantire la TUI
    printf("  " _ANSI_STYLE_FAINT "%s " _ANSI_COLOR_STYLE_RESET, prompt);

    // Mostra temporaneamente il cursore per far capire all'utente dove scrive
    printf(_ANSI_SHOW_CURSOR);

    // Legge la stringa
    if (fgets(output_buffer, (int)buffer_size, stdin) != NULL)
    {
        // Rimuove il '\n' alla fine della stringa se presente
        size_t len = strlen(output_buffer);
        if (len > 0 && output_buffer[len - 1] == '\n') {
            output_buffer[len - 1] = '\0';
        }
    }

    printf(_ANSI_HIDE_CURSOR);
}

bool ui_prompt_confirmation(const char* message, const char* choice1, const char* choice2)
{
    if (message == NULL) return false;

    bool choice = false;
    bool loop = true;

    printf(_ANSI_HIDE_CURSOR);

    while (loop)
    {
        printf(_ANSI_DELETE_LINE);

        // Stampa il messaggio
        printf("  " _ANSI_STYLE_FAINT "%s " _ANSI_COLOR_STYLE_RESET, message);

        // Se choice è false, evidenzia [Choice1] in grassetto/colore, altrimenti lo lascia standard
        if (choice == false) {
            printf(_ANSI_STYLE_BOLD _ANSI_COLOR_PRIMARY "► %s" _ANSI_COLOR_STYLE_RESET "   %s  ", choice1, choice2);
        } else {
            printf("  %s   " _ANSI_STYLE_BOLD _ANSI_COLOR_PRIMARY "► %s" _ANSI_COLOR_STYLE_RESET "  ", choice1, choice2);
        }
        fflush(stdout); // forza il buffer a svuotarsi, mandando in output il testo

        int pressed_key = util_read_key();
        switch (pressed_key)
        {
            // Con le frecce Destra/Sinistra/Su/Giù si inverte la selezione
            case UTIL_KEY_LEFT:
            case UTIL_KEY_RIGHT:
            case UTIL_KEY_UP:
            case UTIL_KEY_DOWN:
                choice = !choice; // Inverte choice1 e choice2
                break;

            // Invio conferma la scelta attuale
            case UTIL_KEY_ENTER:
                loop = false;
                break;

            default:
                break;
        }
    }
    printf("\n");
    return choice;
}






void ui_print_logo(void)
{
    printf(_ANSI_COLOR_PRIMARY);

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

    printf(_ANSI_COLOR_STYLE_RESET); // RESET del colore
    printf("\n");
}

void ui_print_credits(void) {

    printf("%s.------------------------------------------------------------.%s\n", _ANSI_COLOR_PRIMARY, _ANSI_COLOR_STYLE_RESET);

    // Riga: Made by
    printf("%s| %s%-10s%s%-49s%s|%s\n",
           _ANSI_COLOR_PRIMARY, _ANSI_COLOR_PRIMARY, "Made by:", _ANSI_COLOR_SECONDARY, "Andrea Silvani, Alessandro Zaccagnino", _ANSI_COLOR_PRIMARY, _ANSI_COLOR_STYLE_RESET);

    // Riga: Corso
    printf("%s| %s%-10s%s%-49s%s|%s\n",
           _ANSI_COLOR_PRIMARY, _ANSI_COLOR_PRIMARY, "Corso:", _ANSI_COLOR_SECONDARY, "Laboratorio di Informatica | Primo Appello", _ANSI_COLOR_PRIMARY, _ANSI_COLOR_STYLE_RESET);

    // Riga: Anno
    printf("%s| %s%-10s%s%-49s%s|%s\n",
           _ANSI_COLOR_PRIMARY, _ANSI_COLOR_PRIMARY, "Anno:", _ANSI_COLOR_SECONDARY, "2025/2026", _ANSI_COLOR_PRIMARY, _ANSI_COLOR_STYLE_RESET);

    // Riga: System
    printf("%s| %s%-10s%s%-49s%s|%s\n",
           _ANSI_COLOR_PRIMARY, _ANSI_COLOR_PRIMARY, "Progetto:", _ANSI_COLOR_SECONDARY, "Gestione Richieste di Assistenza Tecnica - v1.0", _ANSI_COLOR_PRIMARY, _ANSI_COLOR_STYLE_RESET);

    printf("%s'------------------------------------------------------------'%s\n", _ANSI_COLOR_PRIMARY, _ANSI_COLOR_STYLE_RESET);
    printf("\n");
}