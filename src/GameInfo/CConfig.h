#pragma once
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class CConfig {
public:

    /**
     * @brief Loads the configuration from a file.
     *
     * This function loads the game configuration from a file specified by the given filename.
     * The configuration file should follow a specific format to set the game mode, map mode, rounds, and hunting time.
     *
     * @param filename The name of the configuration file.
     * @return `true` if the configuration was successfully loaded, `false` otherwise.
     */
    bool loadConfig(const std::string& filename);

    /**
     * @brief Loads the map from a file.
     *
     * This function loads the game map from a file specified by the given filename.
     * The map file should contain a grid of characters representing the game layout
     * and the initial positions of ghosts and Pacman.
     *
     * @param filename The name of the map file.
     * @return `true` if the map was successfully loaded, `false` otherwise.
     */
    bool loadMap(const std::string& filename);

    /**
     * @brief Sets the configuration to easy mode.
     *
     * This function sets the configuration parameters to the values appropriate for the easy difficulty level.
     */
    void easyConf();

    /**
     * @brief Sets the configuration to medium mode.
     *
     * This function sets the configuration parameters to the values appropriate for the medium difficulty level.
     */
    void mediumConf();

    /**
     * @brief Sets the configuration to hard mode.
     *
     * This function sets the configuration parameters to the values appropriate for the hard difficulty level.
     */
    void hardConf();

    /**
     * @brief Sets the configuration to custom easy mode.
     *
     * This function sets the configuration parameters to the custom values for the easy difficulty level.
     */
    void easyCustConf();

    /**
     * @brief Sets the configuration to custom medium mode.
     *
     * This function sets the configuration parameters to the custom values for the medium difficulty level.
     */
    void mediumCustConf();

    /**
     * @brief Sets the configuration to custom hard mode.
     *
     * This function sets the configuration parameters to the custom values for the hard difficulty level.
     */
    void hardCustConf();

    /**
     * @brief Struct representing a ghost.
     */
    struct SGhosts {
        /**
         * @brief Constructs a ghost object.
         *
         * This constructor initializes a `SGhosts` object with the specified ghost type and position.
         *
         * @param GhostType The type of the ghost.
         * @param x The x-coordinate of the ghost's position.
         * @param y The y-coordinate of the ghost's position.
         */
        SGhosts(char GhostType, int x, int y);
        char GhostType;
        int x;
        int y;
    };

    std::string m_Mode;
    std::string m_MapMode;
    std::vector<int> m_CustomRounds;
    std::vector<int> m_CustomHuntingRounds;
    int m_Rounds = 0;
    int m_HuntingRounds = 0;
    int m_CoinsSum = 0;
    int m_mapWidth = 0;
    int m_mapHeight = 0;
    std::vector<SGhosts> m_Ghosts;
    std::pair<int, int> m_PacPos;
    std::vector<std::vector<char>> m_Map;
};
