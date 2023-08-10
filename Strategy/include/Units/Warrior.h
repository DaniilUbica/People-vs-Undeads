#pragma once

#include "../Engine/Character.h"
#include "../Townhall.h"

class Warrior : public Character {
protected:
    int max_damage = 0;
    int min_damage = 0;
public:
	virtual ~Warrior();

    virtual void Update(float time, std::deque<Warrior*>& enemies, std::deque<Warrior*>& allies, Townhall* th) = 0;
    virtual bool checkCollisionWithEnemies(std::deque<Warrior*> enemies);
    virtual bool checkCollisionWithAllies(std::deque<Warrior*> allies);
    virtual bool checkCollisionWithTownhall(std::deque<Warrior*>& enemies, Townhall* th);
    void removeEnemy(std::deque<Warrior*>& enemies);
};