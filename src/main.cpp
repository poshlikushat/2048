#include <SFML/Graphics.hpp>
#include "../include/Board.h"
#include "../include/Renderer.h"
#include "../include/GameController.h"

int main() {
  sf::RenderWindow window(
      sf::VideoMode(sf::Vector2u{480, 600}),
      "2048"
  );
  window.setFramerateLimit(60);

  Renderer renderer(window, "assets/fonts/Sansation-Regular.ttf");
  if (!renderer.init())
    return -1;

  Board board;

  while (window.isOpen()) {
    while (auto evt = window.pollEvent()) {
      if (evt->is<sf::Event::Closed>()) {
        window.close();
        break;
      }

      if (Direction dir; GameController::handleKeyEvent(*evt, dir)) {
        if (board.move(dir)) {
          board.spawnTile();
        }
      }
    }
    renderer.render(board.getTiles());
  }

  return 0;
}
