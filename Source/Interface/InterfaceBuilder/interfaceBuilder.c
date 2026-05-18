//
// Created by andre on 15/05/2026.
//

#include "interfaceBuilder.h"


#define FIELD_DAY 0
#define FIELD_MONTH 1
#define FIELD_YEAR 2


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

            char bufferDesc[DESCRIPTION_BUFFER_SIZE];
            // snprintf con "%.*s" prende come argomento prima il limite (max_chars = 60) e poi la stringa originaria
            // Se la stringa è più corta di max_chars, la copia tutta. Se è più lunga, la tronca.
            snprintf(bufferDesc, sizeof(bufferDesc), "%.*s...", 60, get_request_description(arr[i]));

            ft_u8write_ln(table,
                get_request_id(arr[i]),
                get_client_id(get_request_client(arr[i])),
                get_client_name(get_request_client(arr[i])),
                deviceNames[get_request_device(arr[i])],
                priorityNames[get_request_priority(arr[i])],
                requestStatusNames[get_request_status(arr[i])],
                bufferDesc,
                hasEstimatedCost ?
                    util_parse_double_to_string(bufferEstimatedCost, get_request_estimated_cost(arr[i]), "€")
                    : "N/A",
                hasFinalCost ?
                    util_parse_double_to_string(bufferFinalCost, get_request_final_cost(arr[i]), "€")
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

    printf(_ANSI_STYLE_FAINT "%s [MAX %zu caratteri]: " _ANSI_COLOR_STYLE_RESET, prompt, buffer_size - 1);

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

int ui_prompt_selection(const char* prompt, const char* options[], size_t options_count)
{
    if (prompt == NULL || options == NULL || options_count == 0) return -1;

    int current_index = 0;
    bool loop = true;

    printf(_ANSI_HIDE_CURSOR);

    while (loop)
    {
        printf(_ANSI_DELETE_LINE);

        // Stampa il prompt
        printf( _ANSI_STYLE_FAINT "%s: " _ANSI_COLOR_STYLE_RESET, prompt);

        // Stampa l'opzione attualmente selezionata con la freccia
        printf(_ANSI_STYLE_BOLD _ANSI_COLOR_PRIMARY "► %s" _ANSI_COLOR_STYLE_RESET, options[current_index]);
        fflush(stdout);

        int pressed_key = util_read_key();
        switch (pressed_key)
        {
            // Freccia SU: va all'elemento precedente (con carosello circolare se arriva a 0)
            case UTIL_KEY_UP:
                if (current_index - 1 >= 0) {
                    current_index--;
                } else {
                    current_index = (int)options_count - 1;
                }
                break;

            // Freccia GIÙ: va all'elemento successivo (ritorna a 0 se supera il limite)
            case UTIL_KEY_DOWN:
                if (current_index + 1 < (int)options_count) {
                    current_index++;
                } else {
                    current_index = 0;
                }
                break;

            // Invio: conferma e blocca il loop
            case UTIL_KEY_ENTER:
                loop = false;
                break;

            default:
                break;
        }
    }

    printf("\n");
    return current_index;
}

void ui_prompt_date (const char* prompt, int* day, int* month, int* year)
{
    if (prompt == NULL || day == NULL || month == NULL || year == NULL) return;

    bool loop = true;

    printf(_ANSI_HIDE_CURSOR);

    int selected_field = FIELD_DAY;
    int selected_day = 0;
    int selected_month = 0;
    int selected_year = 2026;


    while (loop)
    {
        printf(_ANSI_DELETE_LINE);

        // Stampa il prompt
        printf(_ANSI_STYLE_FAINT "%s: " _ANSI_COLOR_STYLE_RESET, prompt);

        // Stampa uno dei 3 campi giorno mese anno selezionati attualmente
        switch (selected_field)
        {
            case FIELD_DAY: // Focus su Giorno
                printf(_ANSI_STYLE_BOLD _ANSI_COLOR_PRIMARY "► %02d" _ANSI_COLOR_STYLE_RESET _ANSI_STYLE_FAINT "/%02d/%04d" _ANSI_COLOR_STYLE_RESET, selected_day + 1, selected_month + 1, selected_year);
                break;
            case FIELD_MONTH: // Focus su Mese
                printf("  " _ANSI_STYLE_FAINT "%02d/" _ANSI_COLOR_STYLE_RESET _ANSI_STYLE_BOLD _ANSI_COLOR_PRIMARY "► %02d" _ANSI_COLOR_STYLE_RESET _ANSI_STYLE_FAINT "/%04d" _ANSI_COLOR_STYLE_RESET, selected_day + 1, selected_month + 1, selected_year);
                break;
            case FIELD_YEAR: // Focus su Anno
                printf("  " _ANSI_STYLE_FAINT "%02d/%02d/" _ANSI_COLOR_STYLE_RESET _ANSI_STYLE_BOLD _ANSI_COLOR_PRIMARY "► %04d" _ANSI_COLOR_STYLE_RESET, selected_day + 1, selected_month + 1, selected_year);
                break;
        }
        int pressed_key = util_read_key();
        switch (pressed_key)
        {
            // Freccia SU: va all'elemento precedente (con carosello circolare se arriva a 0)
            case UTIL_KEY_DOWN:
                switch (selected_field)
                {
                    case FIELD_DAY:
                        if (selected_day - 1 >= 0) {
                            selected_day--;
                        } else {
                            selected_day = util_get_month_days(selected_month, selected_year);
                        }
                        break;
                    case FIELD_MONTH:
                        if (selected_month - 1 >= 0) {
                            selected_month--;
                        } else {
                            selected_month = 11;
                        }
                        // Aggiusta il numero di giorni del mese
                        if (selected_day > util_get_month_days(selected_month, selected_year)) {
                            selected_day = util_get_month_days(selected_month, selected_year);
                        }
                        break;
                    case FIELD_YEAR:
                        if (selected_year - 1 >= 1900)
                        {
                            selected_year--;
                        }
                        else
                            selected_year = 9999;
                        // Aggiusta il numero di giorni del mese
                        if (selected_day > util_get_month_days(selected_month, selected_year)) {
                            selected_day = util_get_month_days(selected_month, selected_year);
                        }
                        break;
                }
                break;
            // Freccia GIÙ: va all'elemento successivo (ritorna a 0 se supera il limite)
            case UTIL_KEY_UP:
                switch (selected_field)
                {
                    case FIELD_DAY:
                        if (selected_day + 1 <= util_get_month_days(selected_month, selected_year)) {
                            selected_day++;
                        } else {
                            selected_day = 0;
                        }
                        break;
                    case FIELD_MONTH:
                        if (selected_month + 1 <= 11) {
                            selected_month++;
                        } else {
                            selected_month = 0;
                        }
                        // Aggiusta il numero di giorni del mese
                        if (selected_day > util_get_month_days(selected_month, selected_year)) {
                            selected_day = util_get_month_days(selected_month, selected_year);
                        }
                        break;
                    case FIELD_YEAR:
                        if (selected_year + 1 <= 9999) {
                            selected_year++;
                        } else {
                            selected_year = 1900;
                        }
                        // Aggiusta il numero di giorni del mese
                        if (selected_day > util_get_month_days(selected_month, selected_year)) {
                            selected_day = util_get_month_days(selected_month, selected_year);
                        }
                        break;
                }
                break;

            case UTIL_KEY_RIGHT:
                if (selected_field + 1 <= FIELD_YEAR) {
                    selected_field++;
                } else {
                    selected_field = FIELD_DAY;
                }
                break;
            case UTIL_KEY_LEFT:
                if (selected_field - 1 >= 0)
                {
                    selected_field--;
                }
                else
                    selected_field = FIELD_YEAR;
                break;
            case UTIL_KEY_ENTER:
                loop = false;
                break;

            default:
                break;
        }
        fflush(stdout);
    }
    *day = selected_day;
    *month = selected_month;
    *year = selected_year;
}


void ui_print_request_summary(
    const char* request_code,
    const char* client_name,
    const char* device_type,
    const char* description,
    const char* priority,
    double estimated_cost,
    const char* opening_date)
{
    // Definisce stringhe di fallback se i dati non sono ancora stati inseriti
    const char* r_code   = (request_code != NULL && strlen(request_code) > 0) ? request_code : "...";
    const char* c_name   = (client_name != NULL && strlen(client_name) > 0)   ? client_name   : "...";
    const char* d_type   = (device_type != NULL && strlen(device_type) > 0)   ? device_type   : "...";
    const char* prio     = (priority != NULL && strlen(priority) > 0)         ? priority      : "...";
    const char* o_date   = (opening_date != NULL && strlen(opening_date) > 0) ? opening_date  : "...";

    // Buffer per il costo stimato
    char cost_buffer[UTIL_FLOAT_PARSER_BUFFER_SIZE];
    if (estimated_cost >= 0) {
        util_parse_double_to_string(cost_buffer, estimated_cost, "€");
    } else {
        strcpy(cost_buffer, "N/A");
    }

    // Buffer per la descrizione con controllo dinamico sui tre puntini
    char desc_buffer[DESCRIPTION_BUFFER_SIZE];
    if (description != NULL && strlen(description) > 0) {
        if (strlen(description) > DESCRIPTION_BUFFER_SIZE) {
            /**
             * Salva la stringa dentro il buffer, troncandola se è troppo lunga ed aggiungendo in caso i 3 puntini
             * */
            snprintf(desc_buffer, sizeof(desc_buffer), "\"%.*s...\"", DESCRIPTION_BUFFER_SIZE+6, description);
        } else {
            // La tiene integra se è corta
            snprintf(desc_buffer, sizeof(desc_buffer), "\"%s\"", description);
        }
    } else {
        strcpy(desc_buffer, "[ XXX ]");
    }

    // Stampa UI
    printf("\n");
    printf("  " _ANSI_COLOR_PRIMARY "📝 RIEPILOGO NUOVA RICHIESTA" _ANSI_COLOR_STYLE_RESET "\n");
    printf("  ├─────────────────────────────────────────────────\n");

    printf("  ├── %-20s %s\n", "Codice Richiesta:", r_code);
    printf("  ├── %-20s %s\n", "Cliente:", c_name);
    printf("  ├── %-20s %s\n", "Dispositivo:", d_type);
    printf("  ├── %-21s %s\n", "Priorità:", prio);
    printf("  ├── %-20s %s\n", "Costo Stimato:", cost_buffer);
    printf("  ├── %-20s %s\n", "Data Apertura:", o_date);
    printf("  │\n");
    printf("  ├─── " _ANSI_STYLE_FAINT "Descrizione Problema:" _ANSI_COLOR_STYLE_RESET "\n");
    printf("  └─── " _ANSI_STYLE_ITALIC "%s" _ANSI_COLOR_STYLE_RESET "\n", desc_buffer);
    fflush(stdout);
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