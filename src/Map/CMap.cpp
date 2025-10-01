#include "CMap.h"

std::shared_ptr<CMapTile> CMap::getTile(int x, int y) const{
    return m_Map[y][x];
}

void CMap::render(WINDOW *win) const{
    for(int y = 0; y < m_Height; y++){
        for(int x = 0; x < m_Width; x++){
            m_Map[y][x]->render(win, x, y);
        }
    }
}

void CMap::setTile(int x, int y, const std::shared_ptr<CMapTile>& c) {
    m_Map[y][x] = c;
}

void CMap::loadMap(const std::vector<std::vector<char>>& mapData) {
    for(const auto& row : mapData) {
        std::vector<std::shared_ptr<CMapTile>> tileRow;
        for(char c : row) {
            std::shared_ptr<CMapTile> tile;
            if(c=='.' || c=='C' || c=='1' || c=='2' || c=='3')
                tile = std::make_shared<CCoin>();
            else if(c=='#')
                tile = std::make_shared<CWall>();
            else if(c==' ')
                tile = std::make_shared<CEmpty>();
            else if(c=='|')
                tile = std::make_shared<CTeleport>();
            else if(c=='o')
                tile = std::make_shared<CFruit>();
            else if(c=='O')
                tile = std::make_shared<CPowerUp>();
            tileRow.push_back(tile);
        }
        m_Map.push_back(tileRow);
    }
    m_Height = mapData.size();
    m_Width = mapData[0].size();
}

