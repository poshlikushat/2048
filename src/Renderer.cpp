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

void Renderer::render(const std::vector<Tile>& tiles) const {
    window_.clear(sf::Color(250, 248, 239));
    constexpr float topPadding = 80.f;
    constexpr float sidePadding = 5.f;
    constexpr float offsetX = sidePadding;
    constexpr float offsetY = topPadding;
    for (int row = 0; row < static_cast<int>(gridSize_); ++row) {
        for (int col = 0; col < static_cast<int>(gridSize_); ++col) {
            const float x = offsetX + padding_ + static_cast<float>(col) * (tileSize_ + padding_);
            const float y = offsetY + padding_ + static_cast<float>(row) * (tileSize_ + padding_);

            sf::RectangleShape cell({tileSize_, tileSize_});
            cell.setPosition(sf::Vector2f(x, y));
            cell.setFillColor(sf::Color(204, 192, 179));
            window_.draw(cell);
        }
    }

    for (const auto& tile : tiles) {
        if (tile.value == 0) continue;

        const float x = offsetX + padding_ + static_cast<float>(tile.x) * (tileSize_ + padding_);
        const float y = offsetY + padding_ + static_cast<float>(tile.y) * (tileSize_ + padding_);

        sf::RectangleShape rect({tileSize_, tileSize_});
        rect.setPosition(sf::Vector2f(x, y));
        rect.setFillColor(getTileColor(tile.color));
        window_.draw(rect);

      sf::Text text(font_, std::to_string(tile.value), 36);
      text.setFillColor(getTextColor(tile.color));

        const auto bounds = text.getLocalBounds();
        const float cx = bounds.position.x + bounds.size.x / 2.f;
        const float cy = bounds.position.y + bounds.size.y / 2.f;
        text.setOrigin(sf::Vector2f(cx, cy));
        text.setPosition(sf::Vector2f(x + tileSize_ / 2.f, y + tileSize_ / 2.f));

        window_.draw(text);
    }

    window_.display();
}

Renderer::Renderer(sf::RenderWindow& window, std::string fontPath)
 : window_(window), fontPath_(std::move(fontPath))
{
  const sf::Vector2u ws = window_.getSize();
  const float totalPadding = (static_cast<float>(gridSize_) + 1) * padding_;
  tileSize_ = (static_cast<float>(ws.x) - totalPadding) / static_cast<float>(gridSize_);
}

bool Renderer::init() {
  return font_.openFromFile(fontPath_);
}
