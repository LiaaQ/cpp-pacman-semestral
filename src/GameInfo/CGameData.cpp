//
// Created by natal on 27/05/2023.
//
#include "CGameData.h"

void CGameData::initGameData(std::shared_ptr<CPacman>& pacman, std::shared_ptr<bool>& vulnerableMode, std::shared_ptr<int>& remainingCoins, int width, int height) {
    m_Pacman = pacman;
    m_RemainingCoins = remainingCoins;
    m_Vulnerable = vulnerableMode;
    m_mapWidth = width;
    m_mapHeight = height;
}