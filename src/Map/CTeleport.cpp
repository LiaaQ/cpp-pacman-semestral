//
// Created by natal on 13/05/2023.
//

#include "CTeleport.h"

void CTeleport::render(WINDOW *win, int x, int y) {
    wattron(win, COLOR_PAIR(4));
    mvwprintw(win, y, x, "|");
    wattroff(win, COLOR_PAIR(4));
}

void CTeleport::onEffectPacman(CGameData &data) {
    if(data.m_Pacman->m_X == data.m_mapWidth-1)
        data.m_Pacman->m_X = 1;
    else
        data.m_Pacman->m_X = data.m_mapWidth-2;
}

void CTeleport::onEffectGhost(CGameData &data, std::shared_ptr<CGhost> &ghost) {
    if(ghost->m_X == data.m_mapWidth-1)
        ghost->m_X = 1;
    else
        ghost->m_X = data.m_mapWidth-2;
}
