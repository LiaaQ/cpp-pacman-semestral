TARGET = teplinat
CXX = g++ -g
CXX_FLAGS = -Wall -pedantic -std=c++17
BUILD_DIR = build
MKDIR = mkdir -p
LIBS = -lncurses

.PHONY: all
all: compile

.PHONY: compile
compile: $(TARGET)

.PHONY: run
run: $(TARGET)
	./$(TARGET)

$(TARGET): $(BUILD_DIR)/CApplication.o $(BUILD_DIR)/CGame.o $(BUILD_DIR)/GameInfo/CConfig.o $(BUILD_DIR)/GameInfo/CGameData.o $(BUILD_DIR)/Map/CCoin.o $(BUILD_DIR)/Map/CEmpty.o $(BUILD_DIR)/Map/CFruit.o $(BUILD_DIR)/Map/CMap.o $(BUILD_DIR)/Map/CMapTile.o $(BUILD_DIR)/Map/CPowerUp.o $(BUILD_DIR)/Map/CTeleport.o $(BUILD_DIR)/Map/CWall.o $(BUILD_DIR)/Players/CClyde.o $(BUILD_DIR)/Players/CGhost.o $(BUILD_DIR)/Players/CInky.o $(BUILD_DIR)/Players/CPacman.o $(BUILD_DIR)/Players/CPinky.o $(BUILD_DIR)/main.o
	$(CXX) $(CXX_FLAGS) $^ -o $@ $(LIBS)

$(BUILD_DIR)/%.o: src/%.cpp
	$(MKDIR) $(@D)
	$(CXX) $(CXX_FLAGS) $< -c -o $@

.PHONY: clean
clean:
	rm -rf $(TARGET) $(BUILD_DIR)/ 2>/dev/null


# Dependencies

$(BUILD_DIR)/CApplication.o: src/CApplication.cpp src/CApplication.h src/Map/CMap.h src/Map/CCoin.h src/Map/CMapTile.h

$(BUILD_DIR)/CClyde.o: src/Players/CClyde.cpp src/Players/CClyde.h src/Players/CGhost.h

$(BUILD_DIR)/CCoin.o: src/Map/CCoin.cpp src/Map/CCoin.h src/Map/CMapTile.h

$(BUILD_DIR)/CConfig.o: src/GameInfo/CConfig.cpp src/GameInfo/CConfig.h

$(BUILD_DIR)/CEmpty.o: src/Map/CEmpty.cpp src/Map/CEmpty.h src/Map/CMapTile.h

$(BUILD_DIR)/CFruit.o: src/Map/CFruit.cpp src/Map/CFruit.h src/Map/CMapTile.h

$(BUILD_DIR)/CGame.o: src/CGame.cpp src/CGame.h src/GameInfo/CConfig.h src/Players/CPacman.h src/Players/CGhost.h

$(BUILD_DIR)/CGameData.o: src/GameInfo/CGameData.cpp src/GameInfo/CGameData.h

$(BUILD_DIR)/CGhost.o: src/Players/CGhost.cpp src/Players/CGhost.h

$(BUILD_DIR)/CInky.o: src/Players/CInky.cpp src/Players/CInky.h src/Players/CGhost.h

$(BUILD_DIR)/CMap.o: src/Map/CMap.cpp src/Map/CMap.h src/Map/CCoin.h src/Map/CMapTile.h

$(BUILD_DIR)/CMapTile.o: src/Map/CMapTile.cpp src/Map/CMapTile.h

$(BUILD_DIR)/CPacman.o: src/Players/CPacman.cpp src/Players/CPacman.h

$(BUILD_DIR)/CPinky.o: src/Players/CPinky.cpp src/Players/CPinky.h src/Players/CGhost.h

$(BUILD_DIR)/CPowerUp.o: src/Map/CPowerUp.cpp src/Map/CPowerUp.h src/Map/CMapTile.h

$(BUILD_DIR)/CTeleport.o: src/Map/CTeleport.cpp src/Map/CTeleport.h src/Map/CMapTile.h

$(BUILD_DIR)/CWall.o: src/Map/CWall.cpp src/Map/CWall.h src/Map/CMapTile.h

$(BUILD_DIR)/main.o: src/main.cpp src/CApplication.h src/Map/CMap.h src/Map/CCoin.h src/Map/CMapTile.h
