//
// Created by Куимов Михаил on 20.06.2025.
//

#include <utility>

#include "../include/Renderer.h"

sf::Color Renderer::getTileColor(const int color) {
  switch (color) {
    case 0: return {238, 228, 218};
    case 1: return {237, 224, 200};
    case 2: return {242, 177, 121};
    case 3: return {245, 149, 99};
    case 4: return {246, 124, 95};
    case 5: return {246, 94, 59};
    default: return {205, 193, 180};
  }
}
sf::Color Renderer::getTextColor(int color) {
  return sf::Color::Black;
}

void Renderer::render(const Tiles &tiles) const {
  window_.clear(sf::Color(250, 248, 239));


  // Drawing a 4x4 grid
  for (auto row = 0; row < gridSize; ++row) {
    for (auto col = 0; col < gridSize; ++col) {
      auto x = padding_ + static_cast<float>(col) * (tileSize_ + padding_);
      auto y = padding_ + static_cast<float>(row) * (tileSize_ + padding_);

      sf::RectangleShape cell(sf::Vector2f(tileSize_, tileSize_));
      cell.setPosition({x, y});
      cell.setFillColor(sf::Color(204, 192, 179)); // серовато-коричневый для пустых ячеек
      window_.draw(cell);
    }
  }

  // Drawing tiles
  for (const auto& tile : tiles.getTiles()) {
    auto x = padding_ + static_cast<float>(tile.x) * (tileSize_ + padding_);
    auto y = padding_ + static_cast<float>(tile.y) * (tileSize_ + padding_);

    sf::RectangleShape rect(sf::Vector2f(tileSize_, tileSize_));
    rect.setPosition({x, y});
    rect.setFillColor(getTileColor(tile.color));
    window_.draw(rect);

    sf::Text text(font_, std::to_string(tile.value), 36);
    text.setFillColor(getTextColor(tile.color));

    auto bounds = text.getLocalBounds();

    float cx = bounds.position.x + bounds.size.x / 2.f;
    float cy = bounds.position.y + bounds.size.y / 2.f;

    text.setOrigin({cx, cy});
    text.setPosition({x + tileSize_ / 2.f, y + tileSize_ / 2.f});
  }

  window_.display();
}
Renderer::Renderer(sf::RenderWindow& window, std::string fontPath):
  window_(window), fontPath_(std::move(fontPath)) {};

bool Renderer::init() {
  return font_.openFromFile(fontPath_);
}
