//
// Created by andre on 16/05/2026.
//

#include "util.h"

// Usate per la funzione (util_read_key)
#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif

char* util_parse_double_to_string(char* outBuffer, double value)
{
    if (outBuffer == NULL) {
        return NULL;
    }

    // Scrive il numero nella stringa, per un massimo di UTIL_PARSE_BUFFER_SIZE-1 caratteri
    snprintf(outBuffer, UTIL_FLOAT_PARSER_BUFFER_SIZE, "%.2f", value);

    // Ritorno del ptr per uso inline
    return outBuffer;
}

char* util_parse_date_to_string(char* outBuffer, struct tm date)
{
    if (outBuffer == NULL) {
        return NULL;
    }
    strftime(outBuffer, UTIL_DATE_PARSER_BUFFER_SIZE, "%Y-%m-%d %H:%M:%S", &date);
    // Ritorno del ptr per uso inline
    return outBuffer;
}

void util_clear_input_buffer(void)
{
    int character;
    // Legge e scara tutti i caratteri fino al newline o EOF
    while ((character = getchar()) != '\n' && character != EOF);
}


int util_read_key(void)
{
#ifdef WIN32
    int ch = _getch(); // Restituisce lo Scancode del tasto premuto

    /* I caratteri speciali (frecce) inviano due codici: il primo è 0 o 224,
     * seguito dal secondo codice che identifica il tasto specifico */
    if (ch == 0 || ch == 224)
    {
        ch = _getch(); // Legge il secondo codice specifico

        if (ch == 72) return UTIL_KEY_UP;
        if (ch == 80) return UTIL_KEY_DOWN;
        if (ch == 75) return UTIL_KEY_LEFT;
        if (ch == 77) return UTIL_KEY_RIGHT;
    }

    if (ch == 13) return UTIL_KEY_ENTER; // Invio su Windows
    return UTIL_KEY_OTHER;
#else
    // TODO LINUX E MAC
    // Configurazione termios per Linux/Mac per leggere un carattere alla volta senza attendere Invio
    // struct termios oldt, newt;
    // int ch;
    // tcgetattr(STDIN_FILENO, &oldt);
    // newt = oldt;
    // newt.c_lflag &= ~(ICANON | ECHO);
    // tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    //
    // ch = getchar();
    // if (ch == 27) { // Sequenza di escape delle frecce su Unix (\x1b[A o \x1b[B)
    //     getchar(); // Salta il '['
    //     switch(getchar()) {
    //         case 'A': ch = KEY_UP; break;
    //         case 'B': ch = KEY_DOWN; break;
    //     }
    // } else if (ch == 10) {
    //     ch = KEY_ENTER; // Invio su Unix
    // }
    //
    // tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    // return ch;
#endif

}