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

void build_requests_table(bool cleanupTerminal)
{
    //TODO Rimpiazza questo vettore con quello nell'header della struct
    const char *vettore[] = {"TEMP1", "TEMP2", "TEMP3", "awd"};

    cleanupTerminal ? cleanup_terminal() : printf("\n");

    // Alloca mem dinamica per la struttura della tabella, ritornando un puntatore
    ft_table_t *table = ft_create_table();

    // Imposta lo stile dei bordi
    ft_set_border_style(table, FT_SOLID_ROUND_STYLE);

    // Imposta proprietà celle in posizione [0][*]: il tipo di riga è un header
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);

    // Scrive i nomi delle colonne
    ft_row_write_ln( table, sizeof(vettore) / sizeof(char*), vettore);

    // Scrive le righe della tabella
    for (size_t i = 0; i < 3; i++)
    {
        ft_u8write_ln(table, "1", "Server Web", "45 MB");
    }
    // Imposta proprietà celle in posizione [*][*]: allinea al centro il contenuto
    ft_set_cell_prop(table, FT_ANY_ROW, FT_ANY_ROW, FT_CPROP_TEXT_ALIGN, FT_ALIGNED_CENTER);

    // TODO Colora riga x
    //ft_set_cell_prop(table, riga_selezionata, FT_ANY_COLUMN, FT_CPROP_CONT_FG_COLOR, FT_COLOR_GREEN);

    // Stampa della tabella
    printf("%s\n", ft_to_string(table));
    fflush(stdout);

    // Dealloca la memoria usata dalla tabella
    ft_destroy_table(table);
}