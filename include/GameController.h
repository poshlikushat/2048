//
// Created by Куимов Михаил on 20.06.2025.
//

#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <SFML/Graphics.hpp>
#include "Board.h"

class GameController {
  public:
    GameController() = delete;
  static bool handleKeyEvent(const sf::Event& event, Direction& dir);
};



#endif //GAMECONTROLLER_H
