#include <SFML/Graphics.hpp>

int main()
{
  sf::RenderWindow window(
      sf::VideoMode({200, 200}),
      "SFML works!"
  );
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
    while (const std::optional<sf::Event> evt = window.pollEvent())
    {
      if (evt->is<sf::Event::Closed>())
        window.close();
    }

    window.clear();
    window.draw(shape);
    window.display();
  }

  return 0;
}
