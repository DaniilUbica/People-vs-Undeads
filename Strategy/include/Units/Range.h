#pragma once

#include "Warrior.h"
#include "../Units/Bullet.h"

class Range : public Warrior {
private:
    Bullet* bullet;
public:
    Range(int x, int y, bool from_left, std::map<State, sf::Texture>& textures);
    ~Range();

    void Update(float time, std::deque<Warrior*>& enemies, std::deque<Warrior*>& allies, Townhall* th) override;
    bool checkCollisionWithEnemies(std::deque<Warrior*> enemies) override;
    bool checkCollisionWithAllies(std::deque<Warrior*> allies) override;
    bool checkCollisionWithTownhall(std::deque<Warrior*>& enemies, Townhall* th) override;
    void Shoot();

    Bullet* getBullet();
};