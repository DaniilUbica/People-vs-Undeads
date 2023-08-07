#include <iostream>
#include <SFML/Graphics.hpp>

#include "./include/Units/Melee.h"
#include "./include/Units/Range.h"
#include "./include/UI/Canvas.h"
#include "./include/Townhall.h"
#include "./include/AI.h"

void checkReword(std::deque<Warrior*> enemies, int& prev_amount, Canvas& canvas) {
    if (prev_amount > enemies.size()) {
        canvas.addMoney(KILL_REWARD);
    }
    prev_amount = enemies.size();
}

int main() {
    srand(time(NULL));

    setTextures();
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Strategy");
    window.setVerticalSyncEnabled(true);

    sf::Sprite background_sprite(background);
 
    const float start_btn_pos = 30.0;
    const float interval = 15.0;

    sf::Font font;
    font.loadFromFile("./Assets/fonts/font.TTF");

    Canvas canvas(font);
    canvas.addButton(start_btn_pos, 50.0, 50.0, 50.0, sf::Vector3i(168, 79, 79), sf::Vector3i(212, 73, 73), sf::Vector3i(255, 255, 255), sf::Text("Melee", font), MELEE_COOLDOWN, MELEE);
    canvas.addButton(start_btn_pos + 60, 50.0, 50.0, 50.0, sf::Vector3i(168, 79, 79), sf::Vector3i(212, 73, 73), sf::Vector3i(255, 255, 255), sf::Text("Range", font), RANGE_COOLDOWN, RANGE);

    Townhall th_player(-50, 475, 50, 100, human_th);
    Townhall th_enemy(1230, 540, 50, 100, orc_portal);

    std::deque<Warrior*> player;

    std::deque<Warrior*> enemy;

    AI ai(player);

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

        window.draw(background_sprite);

        window.draw(th_player.getSprite());
        th_player.getHealthBar()->drawHealthBar(window);
        th_player.Update();

        window.draw(th_enemy.getSprite());
        th_enemy.getHealthBar()->drawHealthBar(window);
        th_enemy.Update(time);

        ai.Update(enemy);
        ai.Analyse(enemy, player);

        if (player.size() > 0) {
            for (Warrior* ch : player) {
                ch->Update(time, enemy, player, &th_enemy);
                window.draw(ch->getSprite());

                if (ch->getType() == RANGE) {
                    Range* q = dynamic_cast<Range*>(ch);
                    window.draw(q->getBullet()->rect);
                    ch = dynamic_cast<Warrior*>(q);
                }

                if (ch->getActive()) {
                    ch->getHealthbar().drawHealthBar(window);
                }
            }
        }
        if (enemy.size() > 0) {
            for (Warrior* ch : enemy) {
                ch->Update(time, player, enemy, &th_player);
                window.draw(ch->getSprite());
                if (ch->getActive()) {
                    ch->getHealthbar().drawHealthBar(window);
                }
            }
        }
        canvas.Update(window);

        UnitType Warrior = canvas.checkClick(window, event);
        switch (Warrior) {
        case MELEE:
            player.push_back(new Melee(0, 540 + SPRITE_SIZE, true, human_melee_animation));
            break;
        case RANGE:
            player.push_back(new Range(0, 540 + SPRITE_SIZE, true, human_melee_animation));
            break;
        default:
            break;
        }

        checkReword(enemy, prev, canvas);
        canvas.drawButtons(window);
        canvas.drawTimers(window);

        window.display();
    }

    for (Warrior* c : player) {
        delete c;
    }
    for (Warrior* c : enemy) {
        delete c;
    }

    return 0;
}