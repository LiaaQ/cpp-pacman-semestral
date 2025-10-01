#pragma once
#include <cstdio>
#include <string>
#include "GameInfo/CConfig.h"
#include "Players/CPacman.h"
#include "Players/CGhost.h"
#include "Map/CMap.h"
#include "GameInfo/CGameData.h"
#include "Players/CPinky.h"
#include "Players/CInky.h"
#include "Players/CClyde.h"

/**
 * @class CGame
 * @brief Represents a game instance.
 *
 * The CGame class is responsible for managing the game state and controlling the flow of the game.
 * It handles initializing the game, updating game objects, rendering the game screen, handling player input,
 * and determining the win/lose conditions.
 */
/**
 * @class CGame
 * @brief Represents a game instance.
 *
 * The CGame class is responsible for managing the game state and controlling the flow of the game.
 * It handles initializing the game, updating game objects, rendering the game screen, handling player input,
 * and determining the win/lose conditions.
 */
class CGame {
public:
    /**
     * @brief Constructor to initialize the ncurses windows
     */
    CGame();

    /**
     * @brief Runs the game.
     *
     * This function starts the game and manages the game loop.
     * It initializes the game, runs the main game loop until a win or lose condition is met,
     * and handles the appropriate actions when the game ends.
     */
    void runGame();

    /**
     * @brief Configures the game settings.
     *
     * This function handles the configuration of the game settings.
     * It prompts the player to enter the desired game settings, such as the game difficulty, sound settings, etc.
     * It also validates the input and applies the settings accordingly.
     *
     * @return 'false' if loading encounters an error, 'true' if loaded correctly.
     */
    bool allConfig();

    /**
     * @brief Destructor for the ncurses windows
     */
    ~CGame();

private:
    /**
     * @brief Initializes the game.
     *
     * This function initializes the game state by clearing existing game objects, loading the game map,
     * initializing game entities (pacman and ghosts), and setting up the game windows.
     * It also sets up the initial game statistics and displays the game map and initial game state on the screen.
     */
    void gameInit();

    /**
     * @brief Moves the pacman on the game map.
     *
     * This function handles the movement of the pacman on the game map.
     * It updates the pacman's position, checks if the new position is a valid tile to move onto,
     * and triggers the corresponding effects based on the tile type.
     */
    void pacmanMove();

    /**
     * @brief Moves the ghosts on the game map.
     *
     * This function handles the movement of the ghosts on the game map.
     * It calculates the next move for each ghost based on their respective movement strategies,
     * updates their positions, and triggers the corresponding effects based on the tile type.
     */
    void ghostMove();

    /**
     * @brief Checks the collision between ghosts and pacman.
     *
     * Check the collision between Ghosts and Pacman.
     */
    void checkCollision();

    /**
     * @brief Renders all game components on the screen.
     *
     * This function renders all the game components (game map, pacman, ghosts) on the screen.
     * It refreshes the game map window, updates the positions of the entities, and prints the game statistics.
     */
    void allRender() const;

    /**
     * @brief Prints the game statistics on the screen.
     *
     * This function prints the current game statistics on the screen.
     * It displays the remaining coins, score, rounds left, and remaining lives of the pacman.
     */
    void printStats() const;

    /**
     * @brief Handles the game win condition.
     *
     * This function is called when the game is won.
     * It prompts the player to enter their name, adds their score to the leaderboard,
     * and displays the win screen.
     */
    void Win();

    /**
     * @brief Handles the game lose condition.
     *
     * This function is called when the game is lost.
     * It prompts the player to enter their name, adds their score to the leaderboard,
     * and displays the lose screen.
     */
    void Lose();

    /**
     * @brief Hides the game windows.
     *
     * This function clears the game windows to hide them from the screen.
     */
    void winHide() const;

    /**
     * @brief Prints the win screen.
     *
     * This function prints the win screen on the result window.
     * It displays a graphical representation of the win screen and prompts the player to enter their name.
     */
    void printWin() const;

    /**
     * @brief Prints the lose screen.
     *
     * This function prints the lose screen on the result window.
     * It displays a graphical representation of the lose screen and a message indicating the game over state.
     *
     */
    void printLose() const;

    /**
     * @brief Adds the player's score to the leaderboard.
     *
     * This function adds the player's score to the leaderboard.
     * It prompts the player to enter their name and stores their name and score in a leaderboard file.
     * The leaderboard file keeps track of the top players and their scores.
     *
     */
    void addToLeaderboard();


    CConfig m_Config;
    CGameData m_GameData;
    CMap m_GameMap;
    int m_Level = 1;

    /**
     * @brief Stores the player and score info
     */
    struct LeaderboardEntry {
        std::string s_playerName;
        int s_Score;
        int s_Rounds = 0;
    };

    std::shared_ptr<int> m_RemainingCoins = std::make_shared<int>();
    std::shared_ptr<bool> m_Vulnerable = std::make_shared<bool>(true);
    std::shared_ptr<CPacman> m_Pacman = std::make_shared<CPacman>();
    std::vector<std::shared_ptr<CGhost>> m_Ghosts = std::vector<std::shared_ptr<CGhost>>();
    int m_Rounds;
    int m_HuntRoundsLeft = 0;
    LeaderboardEntry m_playerEntry;

    WINDOW* m_mapWin;
    WINDOW* m_statsWin;
    WINDOW* m_resultWin;

};
