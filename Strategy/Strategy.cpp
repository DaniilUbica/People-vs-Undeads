#include <iostream>
#include <SFML/Graphics.hpp>

#include "./include/Enemies/Melee.h"
#include "./include/Textures.h"
#include "./include/UI/Canvas.h"
#include "./include/Townhall.h"
#include "./include/AI.h"

void checkReword(std::deque<Character*> enemies, int& prev_amount, Canvas& canvas) {
    if (prev_amount > enemies.size()) {
        canvas.addMoney(KILL_REWARD);
        prev_amount = enemies.size();
    }
}

int main()
{
    setTextures();
    sf::RenderWindow window(sf::VideoMode(800, 400), "Strategy");
    window.setVerticalSyncEnabled(true);

    const float start_btn_pos = 30.0;
    const float interval = 15.0;

    sf::Font font;
    font.loadFromFile("./Assets/fonts/font.TTF");

    Canvas canvas(font);
    canvas.addButton(start_btn_pos, 50.0, 50.0, 50.0, sf::Vector3i(168, 79, 79), sf::Vector3i(212, 73, 73), sf::Vector3i(255, 255, 255), sf::Text("Melee", font), MELEE_COOLDOWN, MELEE);

    Townhall th_player(0, 150, 50, 100);
    Townhall th_enemy(750, 150, 50, 100);

    std::deque<Character*> player;

    std::deque<Character*> enemy;

    AI ai;

    int prev = enemy.size();

    sf::Clock clock;

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time /= 300;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);

        window.draw(th_player.rect);
        th_player.healthbar->drawHealthBar(window);
        th_player.Update();

        window.draw(th_enemy.rect);
        th_enemy.healthbar->drawHealthBar(window);
        th_enemy.Update();

        ai.Update(enemy);

        if (player.size() > 0) {
            for (Character* ch : player) {
                ch->Update(time, enemy, player, &th_enemy);
                window.draw(ch->getSprite());
                if (ch->getActive()) {
                    ch->getHealthbar().drawHealthBar(window);
                }
            }
        }
        if (enemy.size() > 0) {
            for (Character* ch : enemy) {
                ch->Update(time, player, enemy, &th_player);
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

        checkReword(enemy, prev, canvas);
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