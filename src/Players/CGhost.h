#pragma once
#include <ncurses.h>
#include <vector>
#include <map>
#include <math.h>

class CGhost {
public:
    /**
     * @brief Moves the ghost in chase mode.
     *
     * This pure virtual function is responsible for moving the ghost in chase mode.
     * The implementation should determine the next position of the ghost based on Pacman's position and the map.
     *
     * @param pacPos The position of Pacman.
     * @param map The game map represented as a 2D vector of characters.
     */
    virtual void moveChase(const std::pair<int, int> &pacPos, const std::vector<std::vector<char>> &map,
                           const std::pair<int, int> &prevPacPos) = 0;
    /**
     * @brief Renders the ghost.
     *
     * This pure virtual function is responsible for rendering the ghost on the specified window.
     *
     * @param win The window to render the ghost on.
     */
    virtual void render(WINDOW *win) const = 0;

    /**
     * @brief Renders the ghost in a frightened mode.
     *
     * This pure virtual function is responsible for rendering the ghost on the specified window when it's vulnerable.
     *
     * @param win The window to render the ghost on.
     */
    virtual void renderFrightened(WINDOW *win) const = 0;

    /**
     * @brief Moves the ghost in flee mode.
     *
     * This function is responsible for moving the ghost in flee mode.
     * The implementation determines ghost's next move using the Manhattan distance.
     */
    void moveFlee(const std::pair<int, int> &pacPos, const std::vector<std::vector<char>> &map);

    /**
     * @brief Respawns the ghost.
     *
     * This function respawns the ghost at its starting position.
     */
    void respawn();

    /**
     * @brief A default destructor for the CGhost class.
     */
    virtual ~CGhost() = default;

    int m_X;
    int m_Y;
    std::pair<int, int> m_startPos;
};
