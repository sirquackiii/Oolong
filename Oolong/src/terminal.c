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

// write a function that prints the first x numbers of the fibonacci sequence
void print_fibonacci(int n) {
    int i;
    int a = 0;
    int b = 1;
    int c;
    for (i = 0; i < n; i++) {
        c = a + b;
        a = b;
        b = c;
        printf("%d\n", c);
    }
}
