#include <ncurses.h>

#include "cpu.h"
#include "terminal.h"

void term_init() {
    initscr();
}

void term_end() {
    addstr("Press any key to end...");
    refresh();
    getch();
    endwin();
}
