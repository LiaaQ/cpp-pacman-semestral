//
// Created by natal on 13/05/2023.
//

#include <queue>
#include "CInky.h"

void CInky::render(WINDOW *win) const {
    wattron(win, COLOR_PAIR(5));
    mvwaddstr(win, m_Y, m_X, "&");
    wattroff(win, COLOR_PAIR(5));
}

void CInky::renderFrightened(WINDOW *win) const {
    wattron(win, COLOR_PAIR(5));
    mvwaddstr(win, m_Y, m_X, "F");
    wattroff(win, COLOR_PAIR(5));
}

void CInky::moveChase(const std::pair<int, int> &pacPos, const std::vector<std::vector<char>> &map,
                      const std::pair<int, int> &prevPacPos) {
    std::pair<int, int> pacDirection = {prevPacPos.first - pacPos.first, prevPacPos.second - pacPos.second};
    std::pair<int, int> targetCell;
    std::pair<int, int> tmpCell;

    // Check which direction pacman moved last and expect him to move the same direction
    if(pacDirection == std::make_pair(0,0))
        targetCell = pacPos;
    else
        for(int i = 0; i < 4; i++) {
            tmpCell = {pacPos.first + pacDirection.first, pacPos.second + pacDirection.second};
            if(map[tmpCell.second][tmpCell.first]=='#' || map[tmpCell.second][tmpCell.first]=='|')
                break;
            targetCell = tmpCell;
        }

    // Create a visited matrix to keep track of visited cells during BFS
    std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), false));

    // Create a queue for BFS
    std::queue<std::pair<int, int>> q;

    // Create a matrix to store the directions (up, down, left, right)
    std::vector<std::pair<int, int>> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

    // Create a map to store the parents of each visited cell
    std::map<std::pair<int, int>, std::pair<int, int>> parents;

    std::pair<int, int> currentCell;

    // Mark the current cell as visited and enqueue it
    visited[m_Y][m_X] = true;
    q.push(std::make_pair(m_X, m_Y));

    bool targetFound = false;

    while (!q.empty() && !targetFound) {
        currentCell = q.front();
        q.pop();

        // Check if the current cell is Pacman's position
        if (currentCell == targetCell) {
            targetFound = true;
            break;
        }

        // Explore all adjacent cells
        for (const auto& direction : directions) {
            int nextX = currentCell.first + direction.first;
            int nextY = currentCell.second + direction.second;

            if (nextX >= 0 && nextX < static_cast<int>(map[0].size()) && nextY >= 0 && nextY < static_cast<int>(map.size()) &&
                map[nextY][nextX] != '#' && !visited[nextY][nextX] && map[nextY][nextX] != '|') {
                // Mark the next cell as visited and enqueue it
                visited[nextY][nextX] = true;
                parents[std::make_pair(nextX, nextY)] = currentCell;
                q.push(std::make_pair(nextX, nextY));
            }
        }
    }

    // Determine the direction to move towards Pacman and update the ghost's position
    if (targetFound) {
        // Backtrack through the parents to find the first move towards Pacman
        std::pair<int, int> currentCell = targetCell;
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
