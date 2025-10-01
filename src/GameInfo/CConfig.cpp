//
// Created by natal on 24/05/2023.
//
#include "CConfig.h"

bool validTile(char &c){
    if(c=='.' || c=='#' || c=='1' || c=='2' || c=='3' || c=='C' || c=='\n' || c=='\r' || c=='|' || c=='o' || c=='O')
        return true;
    return false;
}

bool CConfig::loadConfig(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;

    if(!file.is_open())
        return false;

    while(std::getline(file, line) && file.is_open()){

        if(line.empty() || line[0]=='/')
            continue;

        std::istringstream iss(line);
        std::string key, value, section;
        iss >> key;

        if(key == "Mode:"){
            iss >> value;
            m_Mode = value;
        } else if(key == "Map:"){
            iss >> value;
            m_MapMode = value;
        } else if (key == "Rounds:") {
            while (iss >> value) {
                int roundValue = std::stoi(value);
                if (roundValue < 1)
                    return false;
                m_CustomRounds.push_back(roundValue);
            }
        } else if (key == "Hunting:") {
            while (iss >> value) {
                int huntingValue = std::stoi(value);
                if (huntingValue < 1)
                    return false;
                m_CustomHuntingRounds.push_back(huntingValue);
            }
        }
    }
    if(m_CustomHuntingRounds.size() < 3 || m_CustomRounds.size() < 3)
        return false;
    return true;
}

bool CConfig::loadMap(const std::string &filename) {
    std::string mapLine;
    std::ifstream file(filename);
    bool pacmanInMap = false;

    if(!file.is_open())
        return false;

    while(std::getline(file, mapLine))
    {
        if(mapLine.empty())
            continue;

        if(m_mapHeight==0)
            m_mapWidth = mapLine.size()-1;

        if(mapLine.size() > 100 || m_mapWidth!=static_cast<int>(mapLine.size())-1)
            return false;

        // Check if first character is wall or teleport
        if(mapLine[0]!='#' && mapLine[0]!='|')
            return false;

        // Check if there is a teleport on the other side as well
        if(mapLine[0]=='|' && mapLine[mapLine.size()-2]!='|')
            return false;

        // Check if last character is wall or teleport
        if(mapLine[mapLine.size()-2]!='#' && mapLine[mapLine.size()-2]!='|')
            return false;

        // Check if there is a teleport on the other side as well
        if(mapLine[mapLine.size()-2]=='|' && mapLine[0]!='|')
            return false;

        // Check if there isn't a wall next to a teleport
        if((mapLine[0]=='|' && mapLine[1]=='#') || (mapLine[mapLine.size()-2]=='|' && mapLine[mapLine.size()-3]=='#'))
            return false;

        std::vector<char> row;
        int i = 0;
        for(char c : mapLine) {
            if(!validTile(c))
                return false;
            if(c=='1' || c=='2' || c=='3') {
                SGhosts Ghost(c, i, m_mapHeight);
                m_Ghosts.push_back(Ghost);
                m_CoinsSum++;
                if(m_Ghosts.size()>4)
                    return false;
            }
            if(c=='C') {
                m_PacPos.first = i;
                m_PacPos.second = m_mapHeight;
                m_CoinsSum++;
                pacmanInMap = true;
            }
            if(c=='.') {
                m_CoinsSum++;
            }
            row.push_back(c);
            i++;
        }
        m_Map.push_back(row);
        ++m_mapHeight;
    }

    file.close();

    if(m_mapHeight>100 || m_mapWidth<5 || m_mapHeight<5 || !pacmanInMap)
        return false;

    return true;
}

void CConfig::easyConf() {
    m_Rounds = 500;
    m_HuntingRounds = 50;
}

void CConfig::mediumConf() {
    m_Rounds = 350;
    m_HuntingRounds = 35;
}

void CConfig::hardConf() {
    m_Rounds = 200;
    m_HuntingRounds = 20;
}

void CConfig::easyCustConf() {
    m_Rounds = m_CustomRounds[0];
    m_HuntingRounds = m_CustomHuntingRounds[0];
}

void CConfig::mediumCustConf() {
    m_Rounds = m_CustomRounds[1];
    m_HuntingRounds = m_CustomHuntingRounds[1];
}

void CConfig::hardCustConf() {
    m_Rounds = m_CustomRounds[2];
    m_HuntingRounds = m_CustomHuntingRounds[2];
}

CConfig::SGhosts::SGhosts(char GhostType, int x, int y) {
    this->GhostType=GhostType;
    this->x=x;
    this->y=y;
}
