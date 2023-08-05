#pragma once

#include "../Engine/Character.h"
#include "../Engine/Globals.h"

class Melee : public Character {
private:

public:
    Melee(int x, int y, bool from_left);

    void Update(float time, std::deque<Character*>& enemies, std::deque<Character*>& allies, Townhall* th);
    bool checkCollisionWithEnemies(std::deque<Character*> enemies);
    bool checkCollisionWithAllies(std::deque<Character*> allies);
    bool checkCollisionWithTownhall(std::deque<Character*>& enemies, Townhall* th);
    void removeEnemy(std::deque<Character*>& enemies);
};