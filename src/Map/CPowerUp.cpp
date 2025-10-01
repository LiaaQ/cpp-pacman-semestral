//
// Created by natal on 13/05/2023.
//

#include "CPowerUp.h"
#include "../Players/CGhost.h"

void CPowerUp::render(WINDOW *win, int x, int y) {
    wattron(win, COLOR_PAIR(4));
    mvwprintw(win, y, x, "O");
    wattroff(win, COLOR_PAIR(4));
}

void CPowerUp::onEffectPacman(CGameData &data) {
    *(data.m_Vulnerable) = true;
    data.m_Pacman->m_Score += 50;
}

void CPowerUp::onEffectGhost(CGameData &data, std::shared_ptr<CGhost> &ghost) {

}
