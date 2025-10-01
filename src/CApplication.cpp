//
// Created by natal on 13/05/2023.
//
#include "CApplication.h"
#include <string>

CApplication::CApplication() {
    m_menuWin = newwin(15, 70, 1, 1);
    m_leaderboardWin = newwin(60, 60, 1, 1);
    refresh();
    startPage();
    wrefresh(m_menuWin);
    wrefresh(m_leaderboardWin);
}

void CApplication::startPage(){
    while(true)
    {
    printLogo();
    int choice;
    CGame PacmanGame;
    // Exit if there is a problem with the config files
    if (PacmanGame.allConfig()) {
        choice = menu();
    } else {
        failed();
        wrefresh(m_menuWin);
        getch();
        endwin();
        return;
    }

    if (choice == 0) {
            werase(m_menuWin);
            wrefresh(m_menuWin);
            PacmanGame.runGame();
    } else if (choice == 1) {
        werase(m_menuWin);
        wrefresh(m_menuWin);
        printLeaderboard();
        wrefresh(m_leaderboardWin);
        getch();
        werase(m_leaderboardWin);
        wrefresh(m_leaderboardWin);
    }
    else {
    endwin();
        return;
    }
}
    attroff(COLOR_PAIR(1));
}

int CApplication::menu() {
    wattron(m_menuWin, COLOR_PAIR(1));
    keypad(m_menuWin, true);
    setlocale(LC_ALL, "");
    std::string choices[3] = {"Play", "Hall Of Fame", "Exit"};
    int highlight = 0;
    int choice;

    // Let the player skim through the choices until they press enter
    while(true){
        for(int i = 0; i < 3; i++)
        {
            if(i == highlight)
                wattron(m_menuWin, A_REVERSE);
            mvwprintw(m_menuWin, 10+i, 34 - choices[i].size()/2, choices[i].c_str());
            wattroff(m_menuWin, A_REVERSE);
        }
        choice = wgetch(m_menuWin);
        switch(choice)
        {
            case KEY_UP:
                highlight--;
                if(highlight == -1)
                    highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight == 3)
                    highlight = 2;
                break;
            default:
                break;
        }
        if(choice==10)
            break;
    }

    wattroff(m_menuWin, COLOR_PAIR(1));
    return highlight;
}

void CApplication::failed() const {
    init_pair(1, COLOR_RED, COLOR_BLACK);
    wattron(m_menuWin, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(m_menuWin, 11, 13, "There was a problem with loading the config.");
    wattroff(m_menuWin, COLOR_PAIR(1) | A_BOLD);
}

void CApplication::printLogo() const {
    mvwprintw(m_menuWin, 3, 13, "  _ __   __ _  ___ _ __ ___   __ _ _ __  \n");
    mvwprintw(m_menuWin, 4, 13, " | '_ \\ / _` |/ __| '_ ` _ \\ / _` | '_ \\ \n");
    mvwprintw(m_menuWin, 5, 13, " | |_) | (_| | (__| | | | | | (_| | | | |\n");
    mvwprintw(m_menuWin, 6, 13, " | .__/ \\__,_|\\___|_| |_| |_|\\__,_|_| |_|\n");
    mvwprintw(m_menuWin, 7, 13, " |_|                                     ");
    box(m_menuWin, '|', '_');
}

void CApplication::printLeaderboard() {
    std::ifstream file("examples/leaderboard.utf8");

    if (!file.is_open()) {
        mvwprintw(m_leaderboardWin, 10, 10, "Error: Failed to open leaderboard file");
        return;
    }

    std::string playerName;
    int score, rounds;
    int line = 1; // Starting line to display the entries

    while (file >> playerName >> score >> rounds) {
        mvwprintw(m_leaderboardWin, line, 1, "%d.", line);
        mvwprintw(m_leaderboardWin, line, 8, playerName.c_str());
        mvwprintw(m_leaderboardWin, line, 29, std::to_string(score).c_str());
        mvwprintw(m_leaderboardWin, line, 49, std::to_string(rounds).c_str());
        line++; // Move to the next line for the next entry
    }

    file.close();
}

CApplication::~CApplication(){
    delwin(m_menuWin);
    delwin(m_leaderboardWin);
}
