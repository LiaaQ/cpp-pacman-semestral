//
// Created by natal on 13/05/2023.
//

#include "CCoin.h"

struct SGameData;

void CCoin::render(WINDOW *win, int x, int y) {
    wattron(win, COLOR_PAIR(2));
    mvwprintw(win, y, x, ".");
    wattroff(win, COLOR_PAIR(2));
}

void CCoin::onEffectPacman(CGameData &data) {
    *(data.m_RemainingCoins)-=1;
    data.m_Pacman->m_Score+=10;
}

void CCoin::onEffectGhost(CGameData &data, std::shared_ptr<CGhost> &ghost) {

}
