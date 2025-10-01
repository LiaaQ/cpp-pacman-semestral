#include <iostream>
#include "CGame.h"
#include <ncurses.h>
#include <algorithm>

CGame::CGame(){
    m_mapWin = newwin(1, 1, 1, 1);
    m_statsWin = newwin(1, 1, 1, 1);
    m_resultWin = newwin(1, 1, 1, 1);
}

void CGame::runGame() {

    bool lose = false;

    for (int i = 0; i < 3; i++) {
        gameInit();
        m_HuntRoundsLeft = 0;
        while (true) {
            if (m_HuntRoundsLeft == 0) *m_Vulnerable = false;

            // Second move for Pacman when ghosts are vulnerable
            // and the level is not the final level
            if (*m_Vulnerable && m_Level != 3) {
                pacmanMove();
                checkCollision();
                allRender();
            }
            pacmanMove();
            ghostMove();

            // Pacman landed on a Power Up
            if (*m_Vulnerable && m_HuntRoundsLeft == 0) {
                m_HuntRoundsLeft = m_Config.m_HuntingRounds;
            }

            checkCollision();

            if (m_HuntRoundsLeft != 0) m_HuntRoundsLeft--;
            m_Rounds--;

            allRender();

            // Quitting conditions
            if ((*m_RemainingCoins) == 0)
                break;

            if (m_Pacman->m_Lives == 0 || m_Rounds == 0) {
                lose = true;
                break;
            }
        }

        m_playerEntry.s_Rounds += m_Rounds;

        if (lose)
            break;

        m_Level++;
        if (m_Config.m_Mode == "Predefined") {
            if (m_Level == 2)
                m_Config.mediumConf();
            if (m_Level == 3)
                m_Config.hardConf();
        } else {
            if (m_Level == 2)
                m_Config.mediumCustConf();
            if (m_Level == 3)
                m_Config.hardCustConf();
        }
    }
    if (lose)
        Lose();
    else
        Win();
}

void CGame::gameInit() {
    // Reset vectors and initialize game elements
    m_Ghosts.clear();
    m_GameMap.m_Map.clear();
    (*m_Pacman).init(m_Config.m_PacPos.first, m_Config.m_PacPos.second);
    m_GameMap.loadMap(m_Config.m_Map);
    if (m_Config.m_Mode == "Predefined") {
        m_Rounds = m_Config.m_Rounds;
    } else {
        m_Config.easyCustConf();
        m_Rounds = m_Config.m_Rounds;
    }
    (*m_RemainingCoins) = m_Config.m_CoinsSum;
    (*m_Vulnerable) = false;

    // Enable keys input for ncurses
    keypad(stdscr, true);
    setlocale(LC_ALL, "");

    // Create ghosts in the given positions
    for (size_t i = 0; i < m_Config.m_Ghosts.size(); i++) {
        std::shared_ptr<CGhost> Ghost;
        if (m_Config.m_Ghosts[i].GhostType == '1')
            Ghost = std::make_shared<CPinky>();
        else if (m_Config.m_Ghosts[i].GhostType == '2')
            Ghost = std::make_shared<CClyde>();
        else if (m_Config.m_Ghosts[i].GhostType == '3')
            Ghost = std::make_shared<CInky>();
        m_Ghosts.push_back(Ghost);
        m_Ghosts[i]->m_X = m_Config.m_Ghosts[i].x;
        m_Ghosts[i]->m_Y = m_Config.m_Ghosts[i].y;
        m_Ghosts[i]->m_startPos = {m_Config.m_Ghosts[i].x, m_Config.m_Ghosts[i].y};
    }

    // Initialize Game data and the ncurses windows
    m_GameData.initGameData(m_Pacman, m_Vulnerable, m_RemainingCoins, m_Config.m_mapWidth, m_Config.m_mapHeight);
    m_mapWin = newwin(m_Config.m_mapHeight + 1, m_Config.m_mapWidth, 1, 1);
    m_statsWin = newwin(m_Config.m_mapHeight + 6, 30, 1, 1);
    m_resultWin = newwin(50, 50, 1, 1);
    m_GameMap.m_Width = m_Config.m_mapWidth;
    m_GameMap.m_Height = m_Config.m_mapHeight;

    // Pre-render gamemap and pacman
    m_GameMap.render(m_mapWin);
    m_Pacman->render(m_mapWin);
    mvwprintw(m_statsWin, m_Config.m_mapHeight, 1, "Press a button to start!");
    wrefresh(m_mapWin);
    wrefresh(m_statsWin);
}

void CGame::pacmanMove() {
    // Save the old coordinates in case we step on a non-steppable tile
    std::pair<int, int> oldCoord = {m_Pacman->m_X, m_Pacman->m_Y};
    m_Pacman->m_prevPos = {m_Pacman->m_X, m_Pacman->m_Y};
    (*m_Pacman).makeMove();

    // Perform the OnEffect function on the current maptile, go back to old coordinates
    // if stepped on a non-steppable tile, perform OnEffect again if stepped on a tile
    // that manipulates Pacman's position
    if (m_GameMap.getTile(m_Pacman->m_X, m_Pacman->m_Y)->isSteppable()) {
        oldCoord = {m_Pacman->m_X, m_Pacman->m_Y};
        m_GameMap.getTile(m_Pacman->m_X, m_Pacman->m_Y)->onEffectPacman(m_GameData);
        std::pair<int, int> newCoord = {m_Pacman->m_X, m_Pacman->m_Y};
        if (oldCoord != newCoord)
            m_GameMap.getTile(m_Pacman->m_X, m_Pacman->m_Y)->onEffectPacman(m_GameData);
        m_GameMap.setTile(m_Pacman->m_X, m_Pacman->m_Y, std::make_shared<CEmpty>());
    } else {
        m_Pacman->m_X = oldCoord.first;
        m_Pacman->m_Y = oldCoord.second;
    }
}

void CGame::ghostMove() {
    // Perform a move for each ghost based on if the state of game is vulnerable or not
    for (size_t i = 0; i < m_Ghosts.size(); i++) {
        if (*m_Vulnerable)
            m_Ghosts[i]->moveFlee(std::make_pair(m_Pacman->m_X, m_Pacman->m_Y), m_Config.m_Map);
        else
            m_Ghosts[i]->moveChase(std::make_pair(m_Pacman->m_X, m_Pacman->m_Y), m_Config.m_Map, m_Pacman->m_prevPos);
        m_GameMap.getTile(m_Ghosts[i]->m_X, m_Ghosts[i]->m_Y)->onEffectGhost(m_GameData, m_Ghosts[i]);
    }
}

void CGame::checkCollision() {
    // Check if Pacman and Ghosts collided
    for (auto &m_Ghost: m_Ghosts) {
        if (m_Ghost->m_X == m_Pacman->m_X && m_Ghost->m_Y == m_Pacman->m_Y) {
            if (*m_Vulnerable) {
                m_Pacman->m_Score += 200;
                m_Ghost->respawn();
            } else {
                m_Pacman->m_Lives--;
                m_Pacman->respawn();
                for (auto &i: m_Ghosts) {
                    i->respawn();
                }
                break;
            }
        }
    }
}

void CGame::allRender() const {
    m_GameMap.render(m_mapWin);
    m_Pacman->render(m_mapWin);
    for (const auto &m_Ghost: m_Ghosts) {
        if (*m_Vulnerable) m_Ghost->renderFrightened(m_mapWin);
        else m_Ghost->render(m_mapWin);
    }
    printStats();
    wrefresh(m_mapWin);
}

void CGame::printStats() const {
    mvwprintw(m_statsWin, m_GameData.m_mapHeight, 1, "Remaining coins: %d    ", *(m_RemainingCoins));
    mvwprintw(m_statsWin, m_GameData.m_mapHeight + 1, 1, "Score: %d   ", m_Pacman->m_Score);
    mvwprintw(m_statsWin, m_GameData.m_mapHeight + 2, 1, "Rounds left: %d   ", m_Rounds);
    mvwprintw(m_statsWin, m_GameData.m_mapHeight + 3, 1, "Lives: %d   ", m_Pacman->m_Lives);
    mvwprintw(m_statsWin, m_GameData.m_mapHeight + 4, 1, "Hunting: %d   ", m_HuntRoundsLeft);
    mvwprintw(m_statsWin, m_GameData.m_mapHeight + 5, 1, "Level: %d   ", m_Level);
    wrefresh(m_statsWin);
}

void CGame::Win() {
    std::vector<char> playerNameBuffer(50);
    printWin();
    echo();
    curs_set(2);
    wgetnstr(m_resultWin, playerNameBuffer.data(), 50);
    noecho();
    curs_set(0);
    m_playerEntry.s_playerName = playerNameBuffer.data();
    addToLeaderboard();
    wattroff(m_resultWin, COLOR_PAIR(4));
    winHide();
}

void CGame::Lose() {
    std::vector<char> playerNameBuffer(50);
    printLose();
    echo();
    curs_set(2);
    wgetnstr(m_resultWin, playerNameBuffer.data(), 50);
    noecho();
    curs_set(0);
    m_playerEntry.s_playerName = playerNameBuffer.data();
    addToLeaderboard();
    wattroff(m_resultWin, COLOR_PAIR(4));
    winHide();
}

void CGame::winHide() const {
    werase(m_mapWin);
    werase(m_statsWin);
    werase(m_resultWin);
    wrefresh(m_mapWin);
    wrefresh(m_statsWin);
    wrefresh(m_resultWin);
}

void CGame::printWin() const {
    init_pair(8, COLOR_GREEN, COLOR_BLACK);
    wattron(m_resultWin, COLOR_PAIR(8));
    wprintw(m_resultWin, " __     __                               _ \n");
    wprintw(m_resultWin, " \\ \\   / /                              | |\n");
    wprintw(m_resultWin, "  \\ \\_/ /__  _   _  __      _____  _ __ | |\n");
    wprintw(m_resultWin, "   \\   / _ \\| | | | \\ \\ /\\ / / _ \\| '_ \\| |\n");
    wprintw(m_resultWin, "    | | (_) | |_| |  \\ V  V / (_) | | | |_|\n");
    wprintw(m_resultWin, "    |_|\\___/ \\__,_|   \\_/\\_/ \\___/|_| |_(_)\n\n");
    wattroff(m_resultWin, COLOR_PAIR(8));
    wattron(m_resultWin, COLOR_PAIR(4));
    wprintw(m_resultWin, "          Enter your name: ");
    wrefresh(m_resultWin);
}

void CGame::printLose() const {
    wattron(m_resultWin, COLOR_PAIR(3));
    wprintw(m_resultWin, " __     __           _           _         \n");
    wprintw(m_resultWin, " \\ \\   / /          | |         | |        \n");
    wprintw(m_resultWin, "  \\ \\_/ /__  _   _  | | ___  ___| |_       \n");
    wprintw(m_resultWin, "   \\   / _ \\| | | | | |/ _ \\/ __| __|      \n");
    wprintw(m_resultWin, "    | | (_) | |_| | | | (_) \\__ \\ |_ _ _ _ \n");
    wprintw(m_resultWin, "    |_|\\___/ \\__,_| |_|\\___/|___/\\__(_|_|_)\n");
    wrefresh(m_resultWin);
    wattroff(m_resultWin, COLOR_PAIR(3));
    wattron(m_resultWin, COLOR_PAIR(4));
    wprintw(m_resultWin, "          Enter your name: ");
    wrefresh(m_resultWin);
}

void CGame::addToLeaderboard() {
    std::ifstream file("examples/leaderboard.utf8");
    std::vector<LeaderboardEntry> entries;
    LeaderboardEntry entry;
    if (!file.is_open())
        return;

    // Load all the scores from the scoreboard
    while (file >> entry.s_playerName >> entry.s_Score >> entry.s_Rounds && file.is_open())
        entries.push_back(entry);
    file.close();

    m_playerEntry.s_Score = m_Pacman->m_Score;
    entries.push_back(m_playerEntry);

    // Emplace the new score into the vector
    std::sort(entries.begin(), entries.end(), [](const LeaderboardEntry &a, const LeaderboardEntry &b) {
        if (a.s_Score == b.s_Score && a.s_Rounds == b.s_Rounds)
            return a.s_playerName < b.s_playerName;
        if (a.s_Score == b.s_Score) {
            return a.s_Rounds > b.s_Rounds;
        }
        return a.s_Score > b.s_Score;
    });

    // Write the scores back into the file
    std::ofstream fileOut("examples/leaderboard.utf8");
    if (!fileOut.is_open())
        return;
    for (const auto &leadEntry: entries) {
        fileOut << leadEntry.s_playerName << " " << leadEntry.s_Score << " " << leadEntry.s_Rounds << std::endl;
    }
    fileOut.close();
}

bool CGame::allConfig() {
    if (!(m_Config.loadConfig("examples/config.utf8")))
        return false;

    if (m_Config.m_Mode == "Predefined")
        m_Config.easyConf();
    else if (m_Config.m_Mode != "Custom")
        return false;

    if (m_Config.m_MapMode == "Easy") {
        if (!m_Config.loadMap("examples/easyMap.utf8"))
            return false;
    } else if (m_Config.m_MapMode == "Medium") {
        if (!m_Config.loadMap("examples/mediumMap.utf8"))
            return false;
    } else if (m_Config.m_MapMode == "Hard") {
        if (!m_Config.loadMap("examples/hardMap.utf8"))
            return false;
    } else if (m_Config.m_MapMode == "Custom") {
        if (!m_Config.loadMap("examples/customMap.utf8"))
            return false;
    } else return false;
    return true;
}

CGame::~CGame(){
    delwin(m_mapWin);
    delwin(m_statsWin);
    delwin(m_resultWin);
}
