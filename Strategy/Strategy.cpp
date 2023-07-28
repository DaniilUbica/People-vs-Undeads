#include <iostream>
#include <SFML/Graphics.hpp>

#include "./include/Enemies/Melee.h"
#include "./include/Textures.h"
#include "./include/UI/Canvas.h"

int main()
{
    setTextures();
    sf::RenderWindow window(sf::VideoMode(800, 400), "Strategy");

    Melee* m1 = new Melee(100, 200, true);
    Melee* m2 = new Melee(700, 200, false);
    Melee* m3 = new Melee(20, 200, true);
    Melee* m4 = new Melee(800, 200, false);
    const float start_btn_pos = 30.0;
    const float interval = 15.0;

    sf::Font font;
    font.loadFromFile("./Assets/fonts/font.TTF");

    Button melee(start_btn_pos, 40.0, 40.0, 40.0, sf::Vector3i(168, 79, 79),
        sf::Vector3i(212, 73, 73), sf::Vector3i(255, 255, 255), sf::Text("Melee", font));

    std::deque<Character*> player;
    player.push_back(m1);
    player.push_back(m3);

    std::deque<Character*> enemy;
    enemy.push_back(m2);
    enemy.push_back(m4);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (melee.checkClick(window, event)) {
            player.push_back(new Melee(player.back()->getPosition().x - 70.0, 200, true));
            melee.setActive(false);
        }

        window.clear(sf::Color::White);
        if (player.size() > 0) {
            for (Character* ch : player) {
                ch->Update(enemy, player);
                window.draw(ch->getSprite());
                if (ch->getActive()) {
                    ch->getHealthbar().drawHealthBar(window);
                }
            }
        }
        if (enemy.size() > 0) {
            for (Character* ch : enemy) {
                ch->Update(player, enemy);
                window.draw(ch->getSprite());
                if (ch->getActive()) {
                    ch->getHealthbar().drawHealthBar(window);
                }
            }
        }
        melee.Update(window);
        melee.drawButton(window);
        window.display();
    }

    delete m1;
    delete m2;

    return 0;
}