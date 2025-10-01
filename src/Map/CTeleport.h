#pragma once
#include "CMapTile.h"

/**
 * @class CTeleport
 * @brief Represents a teleport map tile with specific effects.
 *
 * The CTeleport class inherits from the CMapTile class and represents a teleport map tile in the game.
 * It has specific effects when interacted with by Pacman or ghosts.
 */
class CTeleport : public CMapTile {
public:
    /**
     * @brief Renders the teleport tile on the specified window at the given coordinates.
     *
     * This function is responsible for rendering the teleport tile, represented by a vertical bar,
     * on the specified ncurses window at the given coordinates (x, y).
     *
     * @param win A pointer to the ncurses window.
     * @param x The x-coordinate of the tile on the window.
     * @param y The y-coordinate of the tile on the window.
     */
    void render(WINDOW* win, int x, int y) override;

    /**
     * @brief Handles the effect of Pacman on the teleport tile.
     *
     * This function is called when Pacman interacts with the teleport tile.
     * It teleports Pacman to the opposite side of the map based on its current position.
     *
     * @param data The game data object containing essential game components and information.
     */
    void onEffectPacman(CGameData& data) override;

    /**
     * @brief Handles the effect of a ghost on the teleport tile.
     *
     * This function is called when a ghost interacts with the teleport tile.
     * It teleports the ghost to the opposite side of the map based on its current position.
     *
     * @param data The game data object containing essential game components and information.
     * @param ghost A shared pointer to the ghost object interacting with the tile.
     */
    void onEffectGhost(CGameData& data, std::shared_ptr<CGhost>& ghost) override;
};
