//
// Created by natal on 13/05/2023.
//

#include "CGhost.h"

void CGhost::moveFlee(const std::pair<int, int> &pacPos, const std::vector<std::vector<char>> &map) {
        // Create a matrix to store the directions (up, down, left, right)
        std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
        int shortestDistance = 0;
        std::pair<int, int> newPos;

        for (const auto& direction : directions) {
            int nextX = m_X + direction.first;
            int nextY = m_Y + direction.second;

            // Check if the next cell is valid
            if (nextX >= 0 && nextX < static_cast<int>(map[0].size()) && nextY >= 0 && nextY < static_cast<int>(map.size()) &&
                map[nextY][nextX] != '#' && map[nextY][nextX] != '|' ) {

                int distance = abs(nextX - pacPos.first) + abs(nextY - pacPos.second);
                if(shortestDistance < distance) {
                    newPos = {nextX, nextY};
                    shortestDistance = distance;
                }
            }
        }
        m_X = newPos.first;
        m_Y = newPos.second;
}

void CGhost::respawn() {
    m_X = m_startPos.first;
    m_Y = m_startPos.second;
}