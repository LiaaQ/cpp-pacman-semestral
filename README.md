# Semester Project – Turn-Based Pacman (C++)

This project is a turn-based version of Pacman, created as a university semester assignment.  
The goal is for Pacman to collect all coins on the map while avoiding ghosts trying to stop him.

---

## Gameplay Features
- **Turn-based mechanics** – unlike classic Pacman, every move is a discrete step.  
- **Ghost AI with multiple strategies**:
  - **Pinky** – directly chases the player.  
  - **Inky** – predicts Pacman’s next position.  
  - **Clyde** – heads toward the farthest tile from Pacman.  
- **Powerups and Items**:
  - **Fruit** – restores a life.  
  - **Powerup** – lets Pacman defeat ghosts temporarily.  
- **Teleport tiles** – Pacman can cross from one side of the map to the other.  
- **Configurable setup** – the player can choose which ghosts appear in the game, what the map looks like and other aspects.

---

## System Design & Implementation
- The **map** is represented as a 2D vector of `CMapTiles`, with polymorphism used to handle different types of static tiles.  
- **Ghosts** are implemented through polymorphism as well, allowing different chasing strategies to be encapsulated in separate classes while sharing a common interface.  
- This design makes it easy to extend or swap AI behaviors without changing the game loop.
- To get a visualisation of the class hierarchy, run Doxygen.

---

This was one of my first projects where I had to think about **system architecture** and **effective code** rather than visuals.  
Designing the ghost AI using polymorphism helped me understand how to build flexible, extensible systems in C++.  
It was also an early exercise in thinking about **game balance, player choices, and adaptability**.
