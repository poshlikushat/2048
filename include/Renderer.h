//
// Created by Куимов Михаил on 20.06.2025.
//

#ifndef RENDERER_H
#define RENDERER_H

#include <SFML/Graphics.hpp>
#include "Tile.h"


class Renderer final{
  sf::RenderWindow& window_;
  sf::Font font_;
  std::string fontPath_;

  // Tile size and padding
  const float tileSize_ = 100.f;
  const float padding_ = 0.5f;

  sf::Color getTileColor(int color) const;
  sf::Color getTextColor(int color) const;
public:
  Renderer(sf::RenderWindow& window, const std::string& fontPath);

  bool init();

  void render(const Tiles& tiles);
};



#endif //RENDERER_H
