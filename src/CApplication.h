#pragma once

#include <string>
#include <iostream>
#include <ncurses.h>
#include "Map/CMap.h"
#include "CGame.h"

/**
 * @class CApplication
 * @brief Represents the application for the Pacman game.
 *
 * The CApplication class handles the main menu, game execution, leaderboard display, and error handling.
 * It utilizes the ncurses library for terminal-based user interface.
 */
class CApplication{
public:
    /**
     * @brief Default constructor for CApplication.
     *
     * Initializes the menu and leaderboard windows, refreshes the screen,
     * and displays the start page.
     */
    CApplication();
    /**
     * @brief Displays the start page with the game logo and handles the main menu.
     *
     * The function continuously displays the game logo and presents the main menu options.
     * It waits for the user to select an option and performs the corresponding action.
     * If there is an issue with loading the game configuration, an error message is displayed,
     * and the program exits after a key press.
     */
    void startPage();

    /**
    * @brief Prints the game logo in the menu window.
    *
    * The function prints the game logo using ASCII art in the menu window.
    * It also adds a box around the logo for visual appeal.
    */
    void printLogo() const;

    /**
     * @brief Displays the main menu and handles user input for menu selection.
     *
     * The function displays the main menu options and highlights the user's selection.
     * It waits for the user to navigate and make a selection using the arrow keys.
     * The selected option index is returned.
     *
     * @return The index of the selected menu option.
     */
    int menu();

    /**
     * @brief Displays an error message when there is a problem with loading the game configuration.
     */
    void failed() const;

    /**
     * @brief Prints the leaderboard entries in the leaderboard window.
     *
     * The function reads the leaderboard file and displays the player name, score, and rounds played.
     * Each entry is printed on a separate line.
     * If there is an error opening the leaderboard file, an error message is displayed in the leaderboard window.
     */
    void printLeaderboard();

    /**
     * @brief Destructor for deleting the ncurses windows.
     */
    ~CApplication();

private:
    WINDOW* m_leaderboardWin;
    WINDOW* m_menuWin;
};
