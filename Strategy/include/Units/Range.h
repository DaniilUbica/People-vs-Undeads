#pragma once

#include "../Engine/Character.h"
#include "../Engine/Globals.h"
#include "../Units/Bullet.h"

class Range : public Character {
private:
    Bullet* bullet;
public:
    Range(int x, int y, bool from_left);
    ~Range();

    void Update(float time, std::deque<Character*>& enemies, std::deque<Character*>& allies, Townhall* th);
    bool checkCollisionWithEnemies(std::deque<Character*> enemies);
    bool checkCollisionWithAllies(std::deque<Character*> allies);
    bool checkCollisionWithTownhall(std::deque<Character*>& enemies, Townhall* th);
    void removeEnemy(std::deque<Character*>& enemies);
    void Shoot();

    Bullet* getBullet();
};