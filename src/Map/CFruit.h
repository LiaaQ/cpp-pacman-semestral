#pragma once
#include "CMapTile.h"
#include "../Players/CGhost.h"

/**
 * @class CFruit
 * @brief Represents a fruit map tile with specific effects.
 *
 * The CFruit class inherits from the CMapTile class and represents a fruit map tile in the game.
 */
class CFruit :public CMapTile {
    /**
     * @brief Handles the effect of Pacman on the fruit tile.
     *
     * This function is called when Pacman interacts with the fruit tile.
     * If Pacman's number of lives is not equal to 3, it increases Pacman's number of lives by 1.
     *
     * @param data The game data object containing essential game components and information.
     */
    void onEffectPacman(CGameData &data) override;

    /**
    * @brief Handles the effect of a ghost on the fruit tile.
    *
    * This function is called when a ghost interacts with the fruit tile.
    * Since the fruit tile has no effect on ghosts, this function does not perform any actions.
    *
    * @param data The game data object containing essential game components and information.
    * @param ghost A shared pointer to the ghost object interacting with the tile.
    */
    void onEffectGhost(CGameData &data, std::shared_ptr<CGhost> &ghost) override;

    /**
     * @brief Renders the fruit tile on the specified window at the given coordinates.
     *
     * This function is responsible for rendering the fruit tile, represented by the character 'o',
     * on the specified ncurses window at the given coordinates (x, y).
     *
     * @param win A pointer to the ncurses window.
     * @param x The x-coordinate of the tile on the window.
     * @param y The y-coordinate of the tile on the window.
     */
    void render(WINDOW *win, int x, int y) override;
};
