    #pragma once
    #include "CGhost.h"

    /**
     * @brief The Pinky ghost class.
     *
     * This class represents the Pinky ghost in the game.
     * It inherits from the CGhost base class.
     */
    class CPinky : public CGhost {
        /**
         * @brief Moves the Pinky ghost in the chase mode.
         *
         * This function determines the movement of the Pinky ghost in the chase mode using BFS,
         * based on the current position of Pacman and the game map.
         *
         * @param pacPos The current position of Pacman.
         * @param map The game map represented as a 2D vector of characters.
         */
        void moveChase(const std::pair<int, int> &pacPos, const std::vector<std::vector<char>> &map,
                       const std::pair<int, int> &prevPacPos) override;

        /**
         * @brief Renders the Pinky ghost.
         *
         * This function renders the Pinky ghost on the specified window.
         *
         * @param win The window to render the Pinky ghost on.
         */
        void render(WINDOW *win) const override;

        void renderFrightened(WINDOW *win) const override;
    };
