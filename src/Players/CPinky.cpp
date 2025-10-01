//
// Created by natal on 13/05/2023.
//

#include <queue>
#include "CPinky.h"

void CPinky::render(WINDOW *win) const {
    wattron(win, COLOR_PAIR(3));
    mvwaddstr(win, m_Y, m_X, "&");
    wattroff(win, COLOR_PAIR(3));
}

void CPinky::renderFrightened(WINDOW *win) const {
    wattron(win, COLOR_PAIR(3));
    mvwaddstr(win, m_Y, m_X, "F");
    wattroff(win, COLOR_PAIR(3));
}


void CPinky::moveChase(const std::pair<int, int> &pacPos, const std::vector<std::vector<char>> &map,
                       const std::pair<int, int> &prevPacPos) {
    if(std::make_pair(m_X, m_Y) == pacPos)
        return;

    // Create a visited matrix to keep track of visited cells during BFS
    std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), false));

    // Create a queue for BFS
    std::queue<std::pair<int, int>> q;

    // Create a matrix to store the directions (up, down, left, right)
    std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    // Create a map to store the parents of each visited cell
    std::map<std::pair<int, int>, std::pair<int, int>> parents;

    // Mark the current cell as visited and enqueue it
    visited[m_Y][m_X] = true;
    q.push(std::make_pair(m_X, m_Y));

    bool pacmanFound = false;

    while (!q.empty() && !pacmanFound) {
        std::pair<int, int> currentCell = q.front();
        q.pop();

        // Check if the current cell is Pacman's position
        if (currentCell == pacPos) {
            pacmanFound = true;
            break;
        }

        // Explore all adjacent cells
        for (const auto& direction : directions) {
            int nextX = currentCell.first + direction.first;
            int nextY = currentCell.second + direction.second;

            if (nextX >= 0 && nextX < static_cast<int>(map[0].size()) && nextY >= 0 && nextY < static_cast<int>(map.size()) &&
                map[nextY][nextX] != '#' && !visited[nextY][nextX]) {

                // Mark the next cell as visited and enqueue it
                visited[nextY][nextX] = true;

                if(map[nextY][nextX] == '|')
                {
                    auto oldCell = std::make_pair(nextX, nextY);
                    parents[std::make_pair(nextX, nextY)] = currentCell;

                    if(nextX == static_cast<int>(map[0].size())-2) nextX = 0;
                    else nextX = map[0].size()-2;

                    // Mark the next cell as visited and enqueue it
                    visited[nextY][nextX] = true;
                    // Set the current cell as the parent of the next cell
                    parents[std::make_pair(nextX, nextY)] = oldCell;
                }
                else {parents[std::make_pair(nextX, nextY)] = currentCell;}
                q.push(std::make_pair(nextX, nextY));
                }
            }
    }

    // Determine the direction to move towards Pacman and update the ghost's position
    if (pacmanFound) {
        // Backtrack through the parents to find the first move towards Pacman
        std::pair<int, int> currentCell = pacPos;
        std::pair<int, int> parentCell = parents[currentCell];

        while (parentCell != std::make_pair(m_X, m_Y)) {
            currentCell = parentCell;
            parentCell = parents[currentCell];
        }

        // Update the ghost's position based on the new direction
        m_X = currentCell.first;
        m_Y = currentCell.second;
    }
}
