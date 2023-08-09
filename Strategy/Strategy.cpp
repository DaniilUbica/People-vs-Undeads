#include <iostream>
#include <SFML/Graphics.hpp>

#include "./include/Units/Melee.h"
#include "./include/Units/Range.h"
#include "./include/UI/Canvas.h"
#include "./include/Townhall.h"
#include "./include/AI.h"
#include "./include/Tower.h"
#include "./include/UI/LoseScreen.h"

void checkReword(std::deque<Warrior*> enemies, int& prev_amount, Canvas& canvas) {
    if (prev_amount > enemies.size()) {
        canvas.addMoney(KILL_REWARD);
    }
    prev_amount = enemies.size();
}

int main() {
    to_menu:
    srand(time(NULL));

    setTextures();
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Strategy");
    window.setVerticalSyncEnabled(true);

    sf::Sprite background_sprite(background);
 
    const float start_btn_pos = 30.0;
    const float interval = 15.0;

    bool play = false;

    sf::Font font;
    font.loadFromFile("./Assets/fonts/font.TTF");

    LoseScreen lose_screen(font);

    Canvas canvas(font);
    canvas.addButton(start_btn_pos, 50.0, 50.0, 50.0, sf::Vector3i(168, 79, 79), sf::Vector3i(212, 73, 73), sf::Vector3i(255, 255, 255), sf::Text("Melee\n       50", font), MELEE_COOLDOWN, MELEE);
    canvas.addButton(start_btn_pos + 60, 50.0, 50.0, 50.0, sf::Vector3i(168, 79, 79), sf::Vector3i(212, 73, 73), sf::Vector3i(255, 255, 255), sf::Text("Range\n       70", font), RANGE_COOLDOWN, RANGE);
    canvas.addButton(1200, 50.0, 50.0, 50.0, sf::Vector3i(168, 79, 79), sf::Vector3i(212, 73, 73), sf::Vector3i(255, 255, 255), sf::Text("Build\nTower\n     "  + std::to_string(TOWER_COST + TOWER_COST_SCALE * canvas.getTowerUpdatesCounter()), font), 5.0, TOWER);

    Townhall th_player(-50, 475, 50, 100, human_th);
    Townhall th_enemy(1230, 540, 50, 100, orc_portal);

    std::deque<Warrior*> player;
    Tower tower(70, PLAYER_START_Y, true);

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
        th_player.Update();

        window.draw(th_enemy.getSprite());
        th_enemy.Update(time);

        if (th_enemy.getHealth() > 0 && th_player.getHealth() > 0) {

            if (canvas.getIsPlaying()) {
                th_player.getHealthBar()->drawHealthBar(window);
                th_enemy.getHealthBar()->drawHealthBar(window);

                ai.Analyse(enemy, player);
                ai.Update(time, enemy, player);

                play = true;
            }
            else if (play == false) {
                ai.restartTimers();
            }

            tower.Update(time, enemy);

            window.draw(tower.getBullet()->rect);
            window.draw(ai.getTower()->getBullet()->rect);

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
            canvas.Update(window);

            UnitType unit = canvas.checkClick(window, event);
            int start_x = PLAYER_START_X;
            if (!player.empty() && player.back()->getPosition().x <= PLAYER_START_X) {
                start_x = player.back()->getPosition().x - INTERVAL;
            }
            switch (unit) {
            case MELEE:
                player.push_back(new Melee(start_x, PLAYER_START_Y + SPRITE_SIZE, true, human_melee_animation));
                break;
            case RANGE:
                player.push_back(new Range(start_x, PLAYER_START_Y + SPRITE_SIZE, true, human_melee_animation));
                break;
            case TOWER:
                tower.addTowerDamage();
                break;
            default:
                break;
            }

            checkReword(enemy, prev, canvas);
            canvas.drawButtons(window);
            canvas.drawTimers(window);
        }
        else {
            lose_screen.Update(window);
            if (th_enemy.getHealth() <= 0) {
                lose_screen.showLoseScreen(window, 0);
            }
            if (th_player.getHealth() <= 0) {
                lose_screen.showLoseScreen(window, 1);
            }
            int lose_click = lose_screen.checkClick(window, event);
            if (lose_click == 1) {
                goto to_menu;
            }
        }

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