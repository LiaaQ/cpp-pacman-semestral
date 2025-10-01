#pragma once
#include "CMapTile.h"
#include "../Players/CGhost.h"

/**
 * @class CPowerUp
 * @brief Represents a power-up map tile with specific effects.
 *
 * The CPowerUp class inherits from the CMapTile class and represents a power-up map tile in the game.
 * It has specific effects when interacted with by Pacman or ghosts.
 */
class CPowerUp : public CMapTile {
public:
    /**
     * @brief Renders the power-up tile on the specified window at the given coordinates.
     *
     * This function is responsible for rendering the power-up tile, represented by the letter 'O',
     * on the specified ncurses window at the given coordinates (x, y).
     *
     * @param win A pointer to the ncurses window.
     * @param x The x-coordinate of the tile on the window.
     * @param y The y-coordinate of the tile on the window.
     */
    void render(WINDOW* win, int x, int y) override;

    /**
     * @brief Handles the effect of Pacman on the power-up tile.
     *
     * This function is called when Pacman interacts with the power-up tile.
     * It sets the vulnerable mode of the game, increases Pacman's score, and activates the power-up effect.
     *
     * @param data The game data object containing essential game components and information.
     */
    void onEffectPacman(CGameData& data) override;

    /**
     * @brief Handles the effect of a ghost on the power-up tile.
     *
     * This function is called when a ghost interacts with the power-up tile.
     * Power-ups have no effect on ghosts, so this function does nothing.
     *
     * @param data The game data object containing essential game components and information.
     * @param ghost A shared pointer to the ghost object interacting with the tile.
     */
    void onEffectGhost(CGameData& data, std::shared_ptr<CGhost>& ghost) override;
};
