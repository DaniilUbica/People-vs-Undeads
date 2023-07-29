#include "../include/Enemies/Melee.h"
#include "../include/Textures.h"
#include <iostream>
Character* findNext(Character* lhs, std::deque<Character*>& allies) {
    for (int i = 0; i < allies.size() - 1; i++) {
        if (lhs == allies[i]) {
            return allies[i + 1];
        }
    }
    return allies.front();
}

Melee::Melee(int x, int y, bool from_left) {
    idle_animation = new Animation(orc_melee_animation[STAY], 0, 0, 22, 32, 10, ANIMATION_SPEED, 32);
    run_animation = new Animation(orc_melee_animation[RUN], 0, 0, 24, 32, 10, ANIMATION_SPEED, 32);
    attack_animation = new Animation(orc_melee_animation[ATTACK], 0, 0, 32, 32, 10, ANIMATION_SPEED, 32);
    death_animation = new Animation(orc_melee_animation[DEATH], 0, 0, 32, 32, 14, ANIMATION_SPEED, 32);

    this->health = 5;
    this->damage = 1;
    this->healthbar = new HealthBar(coordX, coordY, health, 32);

    this->coordX = x;
    this->coordY = y;

    this->from_left = from_left;

    state = RUN;
}

void Melee::Update() {
    state = RUN;
    switch (state) {
    case RUN:
        this->sprite = death_animation->Tick(false);
        break;
    case STAY:
        this->sprite = idle_animation->Tick(false);
        break;
    case ATTACK:
        this->sprite = attack_animation->Tick(false);
        break;
    default:
        break;
    }
    this->sprite.setPosition(coordX, coordY);
}

void Melee::Update(std::deque<Character*>& enemies, std::deque<Character*>& allies) {
    if (health > 0) {
        if (from_left) {
            this->coordX += MELEE_SPEED;
        }
        else {
            this->coordX -= MELEE_SPEED;
        }

        if (allies.size() > 0 && (checkCollisionWithAllies(allies) || enemies.size() > 0 && checkCollisionWithEnemies(enemies) && !enemies.front()->getActive())) {
            state = STAY;
        }
        else if (enemies.size() > 0 && checkCollisionWithEnemies(enemies) && enemies.front()->getActive()) {
            state = ATTACK;
        }
        else {
            state = RUN;
        }

        switch (state) {
        case RUN:
            this->sprite = run_animation->Tick(!from_left);
            break;
        case STAY:
            this->sprite = idle_animation->Tick(!from_left);
            break;
        case ATTACK:
            this->sprite = attack_animation->Tick(!from_left);
            Attack(enemies.front());
            break;
        default:
            break;
        }
    }
    else {
        playDeathAnimation();
        this->is_active = false;
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
}

bool Melee::checkCollisionWithEnemies(std::deque<Character*> enemies) {
    float x1 = this->sprite.getPosition().x;
    float x2 = enemies.front()->getSprite().getPosition().x;
    if (this->is_active) {
        if (from_left) {
            if (x2 > x1) {
                if (x2 - x1 < (SPRITE_SIZE + INTERVAL + 1)) {
                    x1 -= SPRITE_SIZE + INTERVAL - (x2 - x1);
                    this->coordX = x1;
                    return true;
                }
            }
        }
        else {
            if (x2 < x1) {
                if (x1 - x2 < (SPRITE_SIZE + INTERVAL + 1)) {
                    x1 += SPRITE_SIZE + INTERVAL - (x1 - x2);
                    this->coordX = x1;
                    return true;
                }
            }
        }
    }
    return false;
}

bool Melee::checkCollisionWithAllies(std::deque<Character*> allies) {
    for (int i = 0; i < allies.size(); i++) {
        Character* other = allies[i];
        if (from_left) {
            if (other->getPosition().x > this->getPosition().x && other->getPosition().x - this->getPosition().x < INTERVAL + SPRITE_SIZE) {
                this->coordX -= SPRITE_SIZE + INTERVAL - (other->getPosition().x - this->getPosition().x);
                return true;
            }
        }
        else {
            if (other->getPosition().x < this->getPosition().x && abs(other->getPosition().x - this->getPosition().x) < INTERVAL + SPRITE_SIZE) {
                this->coordX += SPRITE_SIZE + INTERVAL - (this->getPosition().x - other->getPosition().x);
                return true;
            }
        }
    }
    return false;
}

void Melee::removeEnemy(std::deque<Character*>& enemies) {
    if (!enemies.front()->getActive() && enemies.front()->getDead()) {
        enemies.pop_front();
    }
}