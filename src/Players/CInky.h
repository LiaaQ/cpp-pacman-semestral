#pragma once
#include "CGhost.h"

/**
 * @brief The Inky ghost class.
 *
 * This class represents the Inky ghost in the game.
 * It inherits from the CGhost base class.
 */
class CInky : public CGhost {
    /**
     * @brief Moves the Inky ghost in the chase mode.
     *
     * This function determines the movement of the Inky ghost in the chase mode,
     * trying to predict Pacman's moves and chase him.
     *
     * @param pacPos The current position of Pacman.
     * @param map The game map represented as a 2D vector of characters.
     */
    void moveChase(const std::pair<int, int> &pacPos, const std::vector<std::vector<char>> &map,
                   const std::pair<int, int> &prevPacPos) override;

    /**
     * @brief Renders the Inky ghost.
     *
     * This function renders the Inky ghost on the specified window.
     *
     * @param win The window to render the Inky ghost on.
     */
    void render(WINDOW *win) const override;

    void renderFrightened(WINDOW *win) const override;
};
