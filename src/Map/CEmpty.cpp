//
// Created by natal on 13/05/2023.
//

#include "CEmpty.h"

void CEmpty::render(WINDOW *win, int x, int y) {
    mvwprintw(win, y, x, " ");
}

void CEmpty::onEffectPacman(CGameData &data) {

}

void CEmpty::onEffectGhost(CGameData &data, std::shared_ptr<CGhost> &ghost) {

}
