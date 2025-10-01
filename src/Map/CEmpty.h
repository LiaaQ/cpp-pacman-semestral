#pragma once
#include "CMapTile.h"

/**
 * @class CEmpty
 * @brief Represents an empty map tile with no effects.
 *
 * The CEmpty class inherits from the CMapTile class and represents an empty map tile in the game.
 * It does not have any specific effects when interacted with by Pacman or ghosts.
 */
class CEmpty : public CMapTile {
public:
    /**
     * @brief Renders the empty tile on the specified window at the given coordinates.
     *
     * This function is responsible for rendering the empty tile, represented by a blank space,
     * on the specified ncurses window at the given coordinates (x, y).
     *
     * @param win A pointer to the ncurses window.
     * @param x The x-coordinate of the tile on the window.
     * @param y The y-coordinate of the tile on the window.
     */
    void render(WINDOW* win, int x, int y) override;

    /**
     * @brief Handles the effect of Pacman on the empty tile.
     *
     * This function is called when Pacman interacts with the empty tile.
     * Since the empty tile has no effect on Pacman, this function does not perform any actions.
     *
     * @param data The game data object containing essential game components and information.
     */
    void onEffectPacman(CGameData& data) override;

    /**
     * @brief Handles the effect of a ghost on the empty tile.
     *
     * This function is called when a ghost interacts with the empty tile.
     * Since the empty tile has no effect on ghosts, this function does not perform any actions.
     *
     * @param data The game data object containing essential game components and information.
     * @param ghost A shared pointer to the ghost object interacting with the tile.
     */
    void onEffectGhost(CGameData& data, std::shared_ptr<CGhost>& ghost) override;
};
