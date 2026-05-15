#include <stdio.h>
#include "../ExternalLibraries/fort/fort.h"


/**
 * @brief
 * @return
 * @param riga_selezionata
 */
void mostra_tabella_interattiva(int riga_selezionata) {
    // 1. Crea la struttura della tabella
    ft_table_t *table = ft_create_table();

    // Definisci gli header (la prima riga)
    ft_set_cell_prop(table, 0, FT_ANY_COLUMN, FT_CPROP_ROW_TYPE, FT_ROW_HEADER);
    ft_write_ln(table, "  ", "ID", "NOME UTENTE", "RUOLO", "STATO");

    // 2. Inserisci i dati. Aggiungiamo un "->" visivo sulla riga selezionata
    ft_write_ln(table, (riga_selezionata == 1) ? "->" : "  ", "1", "Alessandro", "Admin", "Attivo");
    ft_write_ln(table, (riga_selezionata == 2) ? "->" : "  ", "2", "Giovanni",   "User",  "Offline");
    ft_write_ln(table, (riga_selezionata == 3) ? "->" : "  ", "3", "Maria",      "User",  "Attivo");

    // 3. TRUCCO ANTI-FLICKER: Riporta il cursore in alto a sinistra prima di stampare
    printf("\033[H");
    printf("=== GESTIONE UTENTI (Usa le frecce per scorrere) ===\n\n");

    // 4. Stampa l'estetica della tabella generata automaticamente
    printf("%s\n", ft_to_string(table));
    fflush(stdout);

    // Libera la memoria della tabella
    ft_destroy_table(table);
}

int main() {
    mostra_tabella_interattiva(1);
    int a;
    scanf("%d", &a);
}