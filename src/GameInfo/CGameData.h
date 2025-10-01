//
// Created by natal on 27/05/2023.
//
#pragma once
#include "../Players/CPacman.h"
#include <memory>
#include <vector>

/**
 * @class CGameData
 * @brief Represents the game data and provides functionality to initialize and manage various game-related information.
 *
 * The CGameData class serves as a container for essential game components such as Pacman, the number of remaining coins,
 * the vulnerable mode indicator, and the dimensions of the game map.
 */
class CGameData {
public:
    /**
     * @brief Initializes the game data.
     *
     * This function initializes the game data with the provided values for Pacman, vulnerable mode,
     * remaining coins, map width, and map height.
     *
     * @param pacman A shared pointer to the Pacman object.
     * @param vulnerableMode A shared pointer to the vulnerable mode indicator.
     * @param remainingCoins A shared pointer to the number of remaining coins.
     * @param width The width of the game map.
     * @param height The height of the game map.
     */
    void initGameData(std::shared_ptr<CPacman>& pacman, std::shared_ptr<bool>& vulnerableMode,
                      std::shared_ptr<int>& remainingCoins, int width, int height);
    std::shared_ptr<CPacman> m_Pacman;
    std::shared_ptr<int> m_RemainingCoins;
    std::shared_ptr<bool> m_Vulnerable;
    int m_mapWidth;
    int m_mapHeight;
};