#pragma once
#include <ncurses.h>
#include <memory>
#include "../GameInfo/CGameData.h"
#include "../Players/CGhost.h"

/**
 * @class CMapTile
 * @brief Represents a tile on the game map with specific effects and rendering capabilities.
 *
 * The CMapTile class serves as a base class for different types of map tiles in the game. It defines common interface and behavior
 * for map tiles and provides virtual functions for handling the effects of Pacman and ghosts, rendering the tile, and determining
 * if the tile is steppable.
 */
class CMapTile {
public:
    /**
     * @brief Handles the effect of Pacman on the map tile.
     *
     * This function is called when Pacman interacts with the map tile. It takes a reference to the game data object as a parameter
     * to update the relevant game information based on the tile effect.
     *
     * @param data The game data object containing essential game components and information.
     */
    virtual void onEffectPacman(CGameData &data) = 0;

    /**
     * @brief Handles the effect of a ghost on the map tile.
     *
     * This function is called when a ghost interacts with the map tile. It takes a reference to the game data object and a shared pointer
     * to the ghost object as parameters to update the relevant game information based on the tile effect.
     *
     * @param data The game data object containing essential game components and information.
     * @param ghost A shared pointer to the ghost object interacting with the tile.
     */
    virtual void onEffectGhost(CGameData &data, std::shared_ptr<CGhost> &ghost) = 0;

    /**
     * @brief Renders the map tile on the specified window.
     *
     * This function is responsible for rendering the map tile on the specified ncurses window at the given coordinates.
     *
     * @param win A pointer to the ncurses window.
     * @param x The x-coordinate of the tile on the window.
     * @param y The y-coordinate of the tile on the window.
     */
    virtual void render(WINDOW *win, int x, int y) = 0;

    /**
     * @brief Checks if the map tile is steppable.
     *
     * This function determines if the map tile is steppable, i.e., if Pacman and ghosts can move onto this tile.
     * By default, the function returns false, indicating that the tile is not steppable. Subclasses can override this function
     * to specify whether the tile is steppable or not.
     *
     * @return `true` if the tile is steppable, `false` otherwise.
     */
    virtual bool isSteppable() const;

    /**
     * @brief A default destructor for the class.
     */
    virtual ~CMapTile() = default;
};
