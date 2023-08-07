#pragma once

#include "Warrior.h"

class Melee : public Warrior {
public:
    Melee(int x, int y, bool from_left, std::map<State, sf::Texture>& textures);

    void Update(float time, std::deque<Warrior*>& enemies, std::deque<Warrior*>& allies, Townhall* th) override;
};