#pragma once
#include "CMapTile.h"
#include "../Players/CGhost.h"

/**
 * @class CCoin
 * @brief Represents a coin map tile with specific effects.
 *
 * The CCoin class inherits from the CMapTile class and represents a coin map tile in the game.
 * It has specific effects when interacted with by Pacman or ghosts.
 */
class CCoin : public CMapTile {
public:
    /**
     * @brief Renders the coin tile on the specified window at the given coordinates.
     *
     * This function is responsible for rendering the coin tile, represented by a dot,
     * on the specified ncurses window at the given coordinates (x, y).
     *
     * @param win A pointer to the ncurses window.
     * @param x The x-coordinate of the tile on the window.
     * @param y The y-coordinate of the tile on the window.
     */
    void render(WINDOW* win, int x, int y) override;

    /**
     * @brief Handles the effect of Pacman on the coin tile.
     *
     * This function is called when Pacman interacts with the coin tile.
     * It reduces the remaining coin count, increments Pacman's score, and updates the game data accordingly.
     *
     * @param data The game data object containing essential game components and information.
     */
    void onEffectPacman(CGameData& data) override;

    /**
     * @brief Handles the effect of a ghost on the coin tile.
     *
     * This function is called when a ghost interacts with the coin tile.
     * Since the coin tile has no effect on ghosts, this function does not perform any actions.
     *
     * @param data The game data object containing essential game components and information.
     * @param ghost A shared pointer to the ghost object interacting with the tile.
     */
    void onEffectGhost(CGameData& data, std::shared_ptr<CGhost>& ghost) override;
};
