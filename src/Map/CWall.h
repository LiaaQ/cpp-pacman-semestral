#pragma once
#include "CMapTile.h"

/**
 * @class CWall
 * @brief Represents a wall map tile with specific effects.
 *
 * The CWall class inherits from the CMapTile class and represents a wall map tile in the game.
 * It has specific effects when interacted with by Pacman or ghosts.
 */
class CWall : public CMapTile {
public:
    /**
     * @brief Checks if the wall tile is steppable.
     *
     * This function checks whether the wall tile is steppable by Pacman or ghosts.
     * Walls are not steppable, so this function always returns false.
     *
     * @return `false` indicating that the wall tile is not steppable.
     */
    bool isSteppable() const override;

    /**
     * @brief Renders the wall tile on the specified window at the given coordinates.
     *
     * This function is responsible for rendering the wall tile, represented by a hash symbol,
     * on the specified ncurses window at the given coordinates (x, y).
     *
     * @param win A pointer to the ncurses window.
     * @param x The x-coordinate of the tile on the window.
     * @param y The y-coordinate of the tile on the window.
     */
    void render(WINDOW* win, int x, int y) override;

    /**
     * @brief Handles the effect of Pacman on the wall tile.
     *
     * This function is called when Pacman interacts with the wall tile.
     * Walls have no effect on Pacman, so this function does nothing.
     *
     * @param data The game data object containing essential game components and information.
     */
    void onEffectPacman(CGameData& data) override;

    /**
     * @brief Handles the effect of a ghost on the wall tile.
     *
     * This function is called when a ghost interacts with the wall tile.
     * Walls have no effect on ghosts, so this function does nothing.
     *
     * @param data The game data object containing essential game components and information.
     * @param ghost A shared pointer to the ghost object interacting with the tile.
     */
    void onEffectGhost(CGameData& data, std::shared_ptr<CGhost>& ghost) override;
};
