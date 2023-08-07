#include "..\include\Units\Warrior.h"

Warrior::~Warrior() {
	delete healthbar;
	delete idle_animation;
	delete run_animation;
	delete attack_animation;
	delete death_animation;
}

bool Warrior::checkCollisionWithEnemies(std::deque<Warrior*> enemies) {
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

bool Warrior::checkCollisionWithAllies(std::deque<Warrior*> allies) {
    for (int i = 0; i < allies.size(); i++) {
        Warrior* other = allies[i];
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

bool Warrior::checkCollisionWithTownhall(std::deque<Warrior*>& enemies, Townhall* th) {
    float x1 = this->sprite.getPosition().x;
    float x2 = th->getSprite().getPosition().x + 150;
    if (from_left) {
        x2 = th->getSprite().getPosition().x - 15;
    }
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

void Warrior::removeEnemy(std::deque<Warrior*>& enemies) {
    if (!enemies.front()->getActive() && enemies.front()->getDead()) {
        enemies.pop_front();
    }
}