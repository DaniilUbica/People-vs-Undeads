#include "../include/Units/Range.h"
#include "../include/Textures.h"

Range::Range(int x, int y, bool from_left) {
    idle_animation = new Animation(orc_melee_animation[STAY], 0, 0, 22, 32, 10, ANIMATION_SPEED, 32);
    run_animation = new Animation(orc_melee_animation[RUN], 0, 0, 24, 32, 10, ANIMATION_SPEED, 32);
    attack_animation = new Animation(orc_melee_animation[ATTACK], 0, 0, 32, 32, 10, ANIMATION_SPEED * 1.3, 32);
    death_animation = new Animation(orc_melee_animation[DEATH], 0, 0, 32, 32, 14, ANIMATION_SPEED * 1.3, 32);

    bullet = new Bullet(-10, 10);

    type = RANGE;

    this->health = 15;
    this->damage = 12;
    this->healthbar = new HealthBar(coordX, coordY, health, 32);

    this->coordX = x;
    this->coordY = y;

    this->from_left = from_left;

    state = RUN;
}

Range::~Range() {
    delete bullet;
}

void Range::Update(float time, std::deque<Character*>& enemies, std::deque<Character*>& allies, Townhall* th) {
    if (health > 0) {
        if (state == RUN) {
            if (from_left) {
                this->coordX += RANGE_SPEED * time;
            }
            else {
                this->coordX -= RANGE_SPEED * time;
            }
        }

        if (enemies.size() > 0 && checkCollisionWithEnemies(enemies) 
                && enemies.front()->getActive() || checkCollisionWithTownhall(enemies, th)) {
            state = ATTACK;
        }
        else if (allies.size() > 0 && (checkCollisionWithAllies(allies) 
                || enemies.size() > 0 && checkCollisionWithEnemies(enemies) && !enemies.front()->getActive() || bullet->getLaunched())) {
            state = STAY;
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
                if (!bullet->getLaunched() && bullet->getPosition().x == -10) {
                    Shoot();
                }
            }
            else {
                damage = 1;
                Attack(th);
            }
            break;
        default:
            break;
        }
        bullet->Update(time);
        if (!enemies.empty()) {
            bullet->checkCollision(enemies.front());
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
    this->sprite.setColor(sf::Color::Green);
}

bool Range::checkCollisionWithEnemies(std::deque<Character*> enemies) {
    float x1 = this->sprite.getPosition().x;
    float x2 = enemies.front()->getSprite().getPosition().x;
    if (this->is_active) {
        if (from_left) {
            if (x2 > x1) {
                if (x2 - x1 < (SPRITE_SIZE + INTERVAL + 1)*2) {
                    return true;
                }
            }
        }
        else {
            if (x2 < x1) {
                if (x1 - x2 < (SPRITE_SIZE + INTERVAL + 1)*2) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Range::checkCollisionWithAllies(std::deque<Character*> allies) {
    for (int i = 0; i < allies.size(); i++) {
        Character* other = allies[i];
        if (from_left) {
            if (other->getPosition().x > this->getPosition().x && other->getPosition().x - this->getPosition().x < INTERVAL + SPRITE_SIZE) {
                this->coordX -= SPRITE_SIZE + INTERVAL - (other->getPosition().x - this->getPosition().x) - 1;
                return true;
            }
        }
        else {
            if (other->getPosition().x < this->getPosition().x && abs(other->getPosition().x - this->getPosition().x) < INTERVAL + SPRITE_SIZE) {
                this->coordX += SPRITE_SIZE + INTERVAL - (this->getPosition().x - other->getPosition().x) - 1;
                return true;
            }
        }
    }
    return false;
}

bool Range::checkCollisionWithTownhall(std::deque<Character*>& enemies, Townhall* th) {
    float x1 = this->sprite.getPosition().x;
    float x2 = th->rect.getPosition().x;
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

void Range::removeEnemy(std::deque<Character*>& enemies) {
    if (!enemies.front()->getActive() && enemies.front()->getDead()) {
        enemies.pop_front();
    }
}

void Range::Shoot() {
    if (roundf(this->attack_animation->currentFrame) == this->attack_animation->frames.size()) {
        bullet->setPosition(coordX + SPRITE_SIZE / 2, coordY + SPRITE_SIZE / 2);
        bullet->Launch();
        this->attack_animation->currentFrame = 0.0;
    }
}

Bullet* Range::getBullet() {
    return bullet;
}
