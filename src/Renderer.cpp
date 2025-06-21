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

    const sf::Vector2u winSize = window_.getSize();
    // Общая длина (ширина) всей сетки вместе с отступами
    const float totalGrid = static_cast<float>(gridSize_) * tileSize_
                    + (static_cast<float>(gridSize_) + 1) * padding_;
    // Смещение по X и по Y — разница окна и сетки пополам
    const float offsetX = (static_cast<float>(winSize.x) - totalGrid) / 2.f;
    const float offsetY = (static_cast<float>(winSize.y) - totalGrid) / 2.f;

    // 3) Рисуем пустую сетку 4×4, используя смещения offsetX/Y
    for (int row = 0; row < static_cast<int>(gridSize_); ++row) {
        for (int col = 0; col < static_cast<int>(gridSize_); ++col) {
            // к старому расчёту padding_ + col*… прибавляем offset
            const float x = offsetX + padding_ + static_cast<float>(col) * (tileSize_ + padding_);
            const float y = offsetY + padding_ + static_cast<float>(row) * (tileSize_ + padding_);

            sf::RectangleShape cell({tileSize_, tileSize_});
            cell.setPosition(sf::Vector2f(x, y));
            cell.setFillColor(sf::Color(204, 192, 179));
            window_.draw(cell);
        }
    }

    // 4) Рисуем непустые плитки тоже с учётом offsetX/Y
    for (const auto& tile : tiles) {
        if (tile.value == 0) continue;

        float x = offsetX + padding_ + static_cast<float>(tile.x) * (tileSize_ + padding_);
        float y = offsetY + padding_ + static_cast<float>(tile.y) * (tileSize_ + padding_);

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
  // высчитываем tileSize под ширину окна
  const sf::Vector2u ws = window_.getSize();
  // оставляем padding_ слева и справа, итого (gridSize_+1)*padding_
  const float totalPadding = (static_cast<float>(gridSize_) + 1) * padding_;
  // делим оставшееся пространство поровну на gridSize_ клеток
  tileSize_ = (static_cast<float>(ws.x) - totalPadding) / static_cast<float>(gridSize_);
}

bool Renderer::init() {
  return font_.openFromFile(fontPath_);
}
