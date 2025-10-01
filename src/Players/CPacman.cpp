//
// Created by natal on 13/05/2023.
//

#include "CPacman.h"

void CPacman::init(int xPac, int yPac) {
    m_X = xPac;
    m_Y = yPac;
    m_startPos = {xPac, yPac};
}

void CPacman::makeMove() {
    int input = getch();

    switch(input){
        case KEY_UP:
            m_Y--;
            break;
        case KEY_DOWN:
            m_Y++;
            break;
        case KEY_LEFT:
            m_X--;
            break;
        case KEY_RIGHT:
            m_X++;
            break;
        default:
            break;
    }
}

void CPacman::render(WINDOW *win) const {
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, m_Y, m_X, "C");
    wattroff(win, COLOR_PAIR(2));
}

void CPacman::respawn() {
    m_X = m_startPos.first;
    m_Y = m_startPos.second;
}

