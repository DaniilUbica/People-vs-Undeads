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
    Melee* m3 = new Melee(35, 200, true);
    Melee* m4 = new Melee(800, 200, false);
    const float start_btn_pos = 30.0;
    const float interval = 15.0;

    sf::Font font;
    font.loadFromFile("./Assets/fonts/font.TTF");

    Canvas canvas;
    canvas.addButton(start_btn_pos, 50.0, 50.0, 50.0, sf::Vector3i(168, 79, 79), sf::Vector3i(212, 73, 73), sf::Vector3i(255, 255, 255), sf::Text("Melee", font), MELEE_COOLDOWN, MELEE);

    std::deque<Character*> player;
    player.push_back(m1);
    player.push_back(m3);
    player.push_back(new Melee(0, 200, true));

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
        canvas.Update(window);

        UnitType unit = canvas.checkClick(window, event);
        switch (unit) {
        case MELEE:
            player.push_back(new Melee(0, 200, true));
            break;
        default:
            break;
        }

        canvas.drawButtons(window);
        canvas.drawTimers(window);
        window.display();
    }

    for (Character* c : player) {
        delete c;
    }
    for (Character* c : enemy) {
        delete c;
    }

    return 0;
}