#pragma once
#include <cstdio>
#include <vector>
#include <memory>
#include "CCoin.h"
#include "CWall.h"
#include "CEmpty.h"
#include "CTeleport.h"
#include "CPowerUp.h"
#include "CFruit.h"
#include "../Players/CPacman.h"
#include "../Players/CGhost.h"

/**
 * @class CMap
 * @brief Represents the game map consisting of map tiles.
 *
 * The CMap class is responsible for managing and rendering the game map.
 * It contains a two-dimensional vector of map tiles and provides functions to access and modify the tiles.
 */
class CMap {
public:
    /**
     * @brief Retrieves the map tile at the specified coordinates.
     *
     * This function returns a shared pointer to the map tile at the specified coordinates (x, y).
     *
     * @param x The x-coordinate of the tile.
     * @param y The y-coordinate of the tile.
     * @return A shared pointer to the map tile.
     */
    std::shared_ptr<CMapTile> getTile(int x, int y) const;

    /**
     * @brief Sets the map tile at the specified coordinates.
     *
     * This function sets the map tile at the specified coordinates (x, y) to the given map tile object.
     *
     * @param x The x-coordinate of the tile.
     * @param y The y-coordinate of the tile.
     * @param c A shared pointer to the map tile object.
     */
    void setTile(int x, int y, const std::shared_ptr<CMapTile>& c);

    /**
     * @brief Renders the entire map on the specified window.
     *
     * This function renders each map tile on the specified ncurses window.
     *
     * @param win A pointer to the ncurses window.
     */
    void render(WINDOW *win) const;

    /**
     * @brief Loads the map from a vector of characters.
     *
     * This function loads the game map from a vector of characters representing the map layout.
     * Each character corresponds to a specific map tile type, and the map is constructed accordingly.
     *
     * @param mapData A vector of vectors of characters representing the map layout.
     */
    void loadMap(const std::vector<std::vector<char>>& mapData);

    std::vector<std::vector<std::shared_ptr<CMapTile>>> m_Map;
    int m_Width;
    int m_Height;
};
