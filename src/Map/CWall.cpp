//
// Created by natal on 13/05/2023.
//

#include "CWall.h"

bool CWall::isSteppable() const { return false; }

void CWall::render(WINDOW *win, int x, int y) {
    wattron(win, COLOR_PAIR(4));
    mvwprintw(win, y, x, "#");
    wattroff(win, COLOR_PAIR(4));
}

void CWall::onEffectPacman(CGameData &data) {

}

void CWall::onEffectGhost(CGameData &data, std::shared_ptr<CGhost> &ghost) {

}
