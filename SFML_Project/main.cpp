#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

struct cell {
    bool iscross;
    bool ispaint;
    int x;
    int y;
};

RenderWindow window(sf::VideoMode(800, 800), "The picross Magician");


void map() {

}

void drawq(float x, float y) {
    RectangleShape test(sf::Vector2f(50, 50));
    test.setFillColor(sf::Color::Red);
    test.setPosition(100, 100);
    window.draw(test);
}

int main() {

    // Création d'un cercle
    sf::CircleShape shape(50); // Rayon de 50 pixels
    shape.setFillColor(sf::Color::Green);
    sf::RectangleShape rect(sf::Vector2f(50, 50));
    rect.setFillColor(sf::Color::Black);
    rect.setPosition(sf::Vector2f(100, 100));
    // Boucle principale
    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close(); // Fermer la fenêtre
        }

        if (Keyboard::isKeyPressed(Keyboard::Z)) { rect.move(Vector2f(0, -0.05)); }
        if (Keyboard::isKeyPressed(Keyboard::S)) { rect.move(Vector2f(0, 0.05)); }
        if (Keyboard::isKeyPressed(Keyboard::D)) { rect.move(Vector2f(0.05, 0)); }
        if (Keyboard::isKeyPressed(Keyboard::Q)) { rect.move(Vector2f(-0.05, 0)); }
        if (Mouse::isButtonPressed(Mouse::Left)) { drawq(Mouse::getPosition().x, Mouse::getPosition().y); }

        if (Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
 

        window.clear(sf::Color::White);
        window.draw(rect);
        window.display();
    }
        

    return 0;
}