//
// Created by natal on 13/05/2023.
//

#include "CFruit.h"

void CFruit::render(WINDOW *win, int x, int y) {
    wattron(win, COLOR_PAIR(3));
    mvwprintw(win, y, x, "o");
    wattroff(win, COLOR_PAIR(3));
}

void CFruit::onEffectPacman(CGameData &data) {
    if(data.m_Pacman->m_Lives!=3)
        data.m_Pacman->m_Lives+=1;
}

void CFruit::onEffectGhost(CGameData &data, std::shared_ptr<CGhost> &ghost) {

}
