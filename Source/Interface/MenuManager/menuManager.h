//
// Created by andre on 15/05/2026.
//

#ifndef PRGASSISTENZAUNI_MENUMANAGER_H
    #define PRGASSISTENZAUNI_MENUMANAGER_H

    #include <stdlib.h>
    #include "../InterfaceBuilder/interfaceBuilder.h"
    #include "../../Entities/RequestList/requestList.h"
    #include "../../Entities/Client/client.h"
    #include "../../Entities/Request/request.h"

//TODO COMMENTARE TUTTO

/**
 * @brief Puntatore a funzione che esegue un'azione su una RequestList.
 *
 * @details Ogni nodo terminale del menu prende in input una lista di
 * richieste ed esegue operazioni specifiche su di essa (es. ricerca, visualizzazione)
 *
* @note
 * - Questo tipo è usato nei vettori come `MENU_ROOT_ACTIONS` e simili per associare
 *   opzioni di menu a funzioni callback, seguendo uno strategy pattern.
 */
typedef void (*ActionFunc)(RequestList*);


// ========== PARENT NODES (SUB-TREE) and their LEAF NODES ==========
// SUBTREE VISUALIZATION_RESEARCH
void launch_subtree_visualization_research(RequestList* requestList);
    void launch_leaf_action_show_all(RequestList* requestList);
    void launch_leaf_search_by_code(RequestList* requestList);
    void launch_leaf_sorting(RequestList* requestList);

static const char* MENU_VISUALIZATION_RESEARCH_SUBTREES[] = {
    "Mostra Elenco Completo",
    "Cerca Richiesta tramite Codice",
    "Ordinamento",
};
static const ActionFunc MENU_VISUALIZATION_RESEARCH_ACTIONS[] = {
    launch_leaf_action_show_all,
    launch_leaf_search_by_code,
    launch_leaf_sorting
};
// SORTING
static const char* SORTING_OPTIONS[] = {
    "Nome Cliente",
    "Dispositivo",
    "Priorita",
    "Stato",
    "Costo Stimato",
    "Data di Creazione"
};
static const char* SORTING_ORDERS[] = {
    "Decrescente",
    "Crescente"
};


// SUBTREE GESTIONE E MODIFICA RICHIESTE
void launch_subtree_manage(RequestList* requestList);


static const char* MENU_MANAGE_SUBTREES[] = {
    "Inserisci Nuova Richiesta",
    "Modifica Richiesta Esistente",
    "Chiudi Richiesta Completata",
};
static const ActionFunc MENU_MANAGE_ACTIONS[] = {
    //TODO
};





// void launch_subtree_action_filt_stats(RequestList* requestList);
// void launch_subtree_action_report(RequestList* requestList);
// void launch_subtree_exit(RequestList* requestList);





// ROOT
static const char* MENU_ROOT_SUBTREES[] = {
    "Visualizza e Cerca Richieste",
    "Gestione e Modifica Richieste",
    "Filtri e Statistiche",
    "Generazione Report",
    "Esci"
};
static const ActionFunc MENU_ROOT_ACTIONS[] = {
    launch_subtree_visualization_research,
    launch_subtree_manage
    // launch_subtree_action_filt_stats,
    // launch_subtree_action_report,
    // launch_subtree_exit
};









/**
 * @brief Funzione di lancio del menu principale, da cui è possibile accedere a tutte le funzionalità del programma.
 * @param requestList La lista di richieste su cui il menu opererà. Viene passata come parametro a tutte le funzioni callback associate alle opzioni di menu
 */
void init_root_menu(RequestList* requestList);





#endif //PRGASSISTENZAUNI_MENUMANAGER_H
