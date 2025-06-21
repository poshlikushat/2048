#include "../include/GameController.h"

bool GameController::handleKeyEvent(const sf::Event& event, Direction& dir) {
  if (!event.is<sf::Event::KeyPressed>())
    return false;

  switch (const auto kp = event.getIf<sf::Event::KeyPressed>(); kp->code) {
    case sf::Keyboard::Key::Up:    dir = Direction::UP;    return true;
    case sf::Keyboard::Key::Down:  dir = Direction::DOWN;  return true;
    case sf::Keyboard::Key::Left:  dir = Direction::LEFT;  return true;
    case sf::Keyboard::Key::Right: dir = Direction::RIGHT; return true;
    default: return false;
  }
}
