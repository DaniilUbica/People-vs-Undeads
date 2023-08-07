#pragma once

#include <SFML/Graphics.hpp>

#include "../include/Engine/State.h"

__declspec(selectany) std::map<State, sf::Texture> orc_melee_animation;
__declspec(selectany) sf::Texture background;
__declspec(selectany) sf::Texture human_th;
__declspec(selectany) std::map<State, sf::Texture> orc_portal;
__declspec(selectany) std::map<State, sf::Texture> human_melee_animation;

static void setTextures() {
    orc_melee_animation[STAY].loadFromFile("./Assets/orc_idle.png");
    orc_melee_animation[RUN].loadFromFile("./Assets/orc_walk.png");
    orc_melee_animation[ATTACK].loadFromFile("./Assets/orc_attack.png");
    orc_melee_animation[DEATH].loadFromFile("./Assets/orc_death.png");

    background.loadFromFile("./Assets/back.png");
    human_th.loadFromFile("./Assets/human_th.png");
    orc_portal[STAY].loadFromFile("./Assets/portal.png");

    human_melee_animation[STAY].loadFromFile("./Assets/warrior_idle.png");
    human_melee_animation[RUN].loadFromFile("./Assets/warrior_walk.png");
    human_melee_animation[ATTACK].loadFromFile("./Assets/warrior_attack.png");
    human_melee_animation[DEATH].loadFromFile("./Assets/warrior_death.png");
}