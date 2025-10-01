#include "CApplication.h"
#include <ncurses.h>

void initNcurses(){
    initscr();
    start_color();
    cbreak();
    curs_set(0);
    noecho();
    init_color(COLOR_MAGENTA, 108 * 1000 / 255, 41 * 1000 / 255, 217 * 1000 / 255);
    init_color(COLOR_RED, 207 * 1000 / 255, 83 * 1000 / 255, 74 * 1000 / 255);
    init_color(COLOR_YELLOW, 191 * 1000 / 255, 189 * 1000 / 255, 63 * 1000 / 255);
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
}

int main(){
    try{
        initNcurses();
        CApplication Pacman;
        endwin();
        return 0;
    }
    catch(...){
        std::cout << "Unknown error." << std::endl;
    }
}