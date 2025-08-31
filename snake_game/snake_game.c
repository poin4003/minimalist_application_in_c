#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

void main() {
    WINDOW* wnd = initscr();
    keypad(wnd, true);
    nodelay(wnd, true);

    int posX = 0;
    int posY = 0;
    int foodX = rand() % 20;
    int foodY = rand() % 20;
    int dirX = 1;
    int dirY = 0;

    while (true) {
        int pressed = wgetch(wnd);
        if (pressed == KEY_LEFT) {
            dirX = -1;
            dirY = 0;
        }
        if (pressed == KEY_RIGHT) {
            dirX = 1;
            dirY = 0;
        }
        if (pressed == KEY_UP) {
            dirX = 0;
            dirY = -1;
        }
        if (pressed == KEY_DOWN) {
            dirX = 0;
            dirY = 1;
        }
        posX += dirX;
        posY += dirY;
        erase();
        mvaddstr(posY, posX, "*");
        mvaddstr(foodY, foodY, "&");
        usleep(100000);
    }

    endwin();
}