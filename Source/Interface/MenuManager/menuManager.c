//
// Created by andre on 15/05/2026.
//

#include "menuManager.h"


static void menu_home(RequestList*);


void init_menu(RequestList* requestList)
{
    ui_initialize_terminal();
    ui_clear_terminal();
    ui_print_logo();
    ui_print_credits();
    printf(_ANSI_HIDE_CURSOR); // Nasconde cursore del terminale

    menu_home(requestList);
}


void menu_home(RequestList* requestList)
{
    int choice = 0;
    bool running = true;

    while (running)
    {
        ui_clear_terminal();
        ui_print_header("MENU PRINCIPALE");
        ui_print_section_title("MENU PRINCIPALE");
        ui_wait_for_keypress();
        int pressed_key = util_read_key();
        switch (pressed_key)
        {

        }
    }
}