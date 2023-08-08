#pragma once

#include "../Engine/Character.h"
#include "../Townhall.h"

class Warrior : public Character {
public:
	~Warrior();

    virtual void Update(float time, std::deque<Warrior*>& enemies, std::deque<Warrior*>& allies, Townhall* th) = 0;
    virtual bool checkCollisionWithEnemies(std::deque<Warrior*> enemies);
    virtual bool checkCollisionWithAllies(std::deque<Warrior*> allies);
    virtual bool checkCollisionWithTownhall(std::deque<Warrior*>& enemies, Townhall* th);
    void removeEnemy(std::deque<Warrior*>& enemies);
};