#include "OOTurtle.hpp"
#include <sstream>
#include <iostream>

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

  std::ostringstream oss;
  OOTurtle turtle(oss);

  int r = 50;

  turtle.move(r);
  turtle.turn(degree_t{120});
  turtle.move(r);
  turtle.turn(degree_t{120});
  turtle.move(r);
  turtle.turn(degree_t{120});
  
  std::cout << oss.str();
  return 0;
}