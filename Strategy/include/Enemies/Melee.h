#pragma once

#include "../Engine/Character.h"
#include "../Engine/Globals.h"

class Melee : public Character {
private:

public:
    Melee(int x, int y, bool from_left);

    void Update() override;
    void Update(std::deque<Character*>& enemies, std::deque<Character*>& allies);
    bool checkCollisionWithEnemies(std::deque<Character*> enemies);
    bool checkCollisionWithAllies(std::deque<Character*> allies);
    void removeEnemy(std::deque<Character*>& enemies);
};