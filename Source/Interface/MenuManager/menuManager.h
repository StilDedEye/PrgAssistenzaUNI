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
 * @brief Puntatore a funzione che esegue un'azione su una RequestList
 *
 * @details Ogni nodo terminale del menu prende in input una lista di
 * richieste ed esegue operazioni specifiche su di esssa (es. ricerca, visualizzazione)
 *
* @note
 * - Questo tipo è usato nei vettori `MENU_HOME_ACTIONS` e simili per associare
 *   opzioni di menu a funzioni callback.
 *
 */
typedef void (*ActionFunc)(RequestList*);

// ========== PARENT NODES (SUB-TREE) and their LEAF NODES ==========
void launch_subtree_vis_res(RequestList* requestList);
    void launch_leaf_action_show_all(RequestList* requestList);

// void launch_subtree_action_man_edit(RequestList* requestList);
// void launch_subtree_action_filt_stats(RequestList* requestList);
// void launch_subtree_action_report(RequestList* requestList);
// void launch_subtree_exit(RequestList* requestList);


static const char* MENU_ROOT_SUBTREES[] = {
    "Visualizza e Cerca Richieste",
    "Gestione e Modifica Richieste",
    "Filtri e Statistiche",
    "Generazione Report",
    "Esci"
};
static const ActionFunc MENU_ROOT_ACTIONS[] = {
    launch_subtree_vis_res,
    // launch_subtree_action_man_edit,
    // launch_subtree_action_filt_stats,
    // launch_subtree_action_report,
    // launch_subtree_exit
};

static const char* MENU_VIS_RES_SUBTREES[] = {
    "Mostra Elenco Completo",
    "Cerca Richiesta tramite Codice",
    "Ordina per Costo Stimato",
    "Ordina per Criterio Personalizzato"
};
static const ActionFunc MENU_VIS_RES_ACTIONS[] = {
    launch_leaf_action_show_all
};







/**
 * //TODO completa commento
 */
void init_root_menu(RequestList* requestList);





#endif //PRGASSISTENZAUNI_MENUMANAGER_H
