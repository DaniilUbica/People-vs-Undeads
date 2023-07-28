#pragma once

#include <SFML/Graphics.hpp>

#include "../include/Engine/State.h"

__declspec(selectany) std::map<State, sf::Texture> orc_melee_animation;

static void setTextures() {
    orc_melee_animation[STAY].loadFromFile("./Assets/orc_idle.png");
    orc_melee_animation[RUN].loadFromFile("./Assets/orc_walk.png");
    orc_melee_animation[ATTACK].loadFromFile("./Assets/orc_attack.png");
    orc_melee_animation[DEATH].loadFromFile("./Assets/orc_death.png");
}