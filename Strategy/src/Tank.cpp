#include "../include/Units/Tank.h"

Tank::Tank(int x, int y, bool from_left, std::map<State, sf::Texture>& textures, int min, int max) {
    idle_animation = new Animation(textures[STAY], 0, 0, 22, 32, 10, ANIMATION_SPEED, 32);
    run_animation = new Animation(textures[RUN], 0, 0, 24, 32, 10, ANIMATION_SPEED, 32);
    attack_animation = new Animation(textures[ATTACK], 0, 0, 32, 32, 10, ANIMATION_SPEED * 1.3, 32);
    death_animation = new Animation(textures[DEATH], 0, 0, 32, 32, 14, ANIMATION_SPEED * 1.3, 32);

    type = TANK;

    this->max_damage = max;
    this->min_damage = min;

    this->health = 90;
    this->damage = 1;
    this->healthbar = new HealthBar(coordX, coordY, health, 32);

    this->coordX = x;
    this->coordY = y;

    this->from_left = from_left;

    state = RUN;
}

void Tank::Update(float time, std::deque<Warrior*>& enemies, std::deque<Warrior*>& allies, Townhall* th) {
    if (health > 0) {

        this->damage = rand() % max_damage + min_damage;

        if (from_left) {
            this->coordX += MELEE_SPEED * time;
        }
        else {
            this->coordX -= MELEE_SPEED * time;
        }

        if (allies.size() > 0 && (checkCollisionWithAllies(allies) || enemies.size() > 0 && checkCollisionWithEnemies(enemies) && !enemies.front()->getActive())) {
            state = STAY;
        }
        else if (enemies.size() > 0 && checkCollisionWithEnemies(enemies) || checkCollisionWithTownhall(enemies, th)) {
            state = ATTACK;
        }
        else {
            state = RUN;
        }

        switch (state) {
        case RUN:
            this->sprite = run_animation->Tick(time, !from_left);
            break;
        case STAY:
            this->sprite = idle_animation->Tick(time, !from_left);
            break;
        case ATTACK:
            this->sprite = attack_animation->Tick(time, !from_left);
            if (!enemies.empty()) {
                Attack(enemies.front());
            }
            else {
                damage = 1;
                Attack(th);
            }
            break;
        default:
            break;
        }
    }
    else {
        this->is_active = false;
        playDeathAnimation(time);
    }
    if (enemies.size() > 0) {
        removeEnemy(enemies);
    }

    if (from_left) {
        healthbar->Update(coordX + 5.0, coordY, health);
    }
    else {
        healthbar->Update(coordX, coordY, health);
    }

    this->sprite.setPosition(coordX, coordY);
    this->sprite.setScale(1.5, 1.5);
    this->sprite.setColor(sf::Color::Red);
}