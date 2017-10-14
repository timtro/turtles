#include "OOTurtle.hpp"

// #include <SFML/Graphics.hpp>

int main() {
  // sf::RenderWindow window(sf::VideoMode(600, 600), "Turtle.");
  // sf::CircleShape shape(100.f);
  // shape.setFillColor(sf::Color::Red);

  // while (window.isOpen()) {
  //   sf::Event event;
  //   while (window.pollEvent(event)) {
  //     if (event.type == sf::Event::Closed)
  //       window.close();
  //   }

  //   window.clear();
  //   window.draw(shape);
  //   window.display();
  // }

  OOTurtle turtle;

  turtle.move(20);
  turtle.turn(degree_t{90});
  turtle.move(20);

  return 0;
}