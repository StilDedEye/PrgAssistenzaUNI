//
// Created by andre on 15/05/2026.
//

#include "menuManager.h"

// Funzioni aggiuntive interne
void launch_menu(
    bool isSubMenu,
    const char* title,
    RequestList* requestList,
    const char** MENU_SUBTREES,
    size_t menuSubtreesLength,
    const ActionFunc* MENU_ACTIONS,
    size_t menuActionsLength
    );

void init_root_menu(RequestList* requestList)
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
        sizeof(MENU_ROOT_SUBTREES) / sizeof(char*),
        MENU_ROOT_ACTIONS,
        sizeof(MENU_ROOT_ACTIONS) / sizeof(char*)
        );
}

void launch_menu(
    bool isSubMenu,
    const char* title,
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
                if (choice-1 >= 0)
                    choice--;
                else
                    choice = menuSubtreesLength - 1;
                break;

            case UTIL_KEY_DOWN:
                if (choice+1 < menuSubtreesLength)
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
            default:
                break;
        }
    }
    ui_clear_terminal();
}

//===========================================================================
void launch_leaf_action_show_all(RequestList* requestList)
{
    ui_clear_terminal();
    ui_print_requests_table((const Request**)requestList->requests, requestList->count);

    ui_wait_for_keypress(_ANSI_STYLE_UNDERLINE"⮌ Premere enter per tornare indietro", UTIL_KEY_ENTER, UTIL_KEY_LEFT);
    ui_clear_terminal();
}


void launch_subtree_vis_res(RequestList* requestList)
{
    launch_menu(
        true,
        "Home > Visualizza e Cerca Richieste",
        requestList,
        MENU_VIS_RES_SUBTREES,
        sizeof(MENU_VIS_RES_SUBTREES) / sizeof(char*),
        MENU_VIS_RES_ACTIONS,
        sizeof(MENU_VIS_RES_ACTIONS) / sizeof(char*)
        );
}

