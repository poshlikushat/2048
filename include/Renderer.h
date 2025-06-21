//
// Created by Куимов Михаил on 20.06.2025.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Board.h"


class Renderer final{
  sf::RenderWindow& window_;
  sf::Font font_;
  std::string fontPath_;

  const unsigned gridSize_ = 4;
  float tileSize_;
  const float padding_ = 0.5f;

  static sf::Color getTileColor(int color) ;
  static sf::Color getTextColor(int color) ;
public:
  Renderer(sf::RenderWindow& window, std::string  fontPath);

  bool init();

  void render(const std::vector<Tile>& tiles) const;
};



#endif //RENDERER_H
