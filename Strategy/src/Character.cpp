#include "../include/Engine/Character.h"

void Character::takeDamage(int damage) {
	health -= damage;
}

void Character::Attack(Character* enemy) {
	if (roundf(this->attack_animation->currentFrame) == this->attack_animation->frames.size()) {
		enemy->takeDamage(this->damage);
		this->attack_animation->currentFrame = 0.0;
	}
}

void Character::Attack(Townhall* th) {
	if (roundf(this->attack_animation->currentFrame) == this->attack_animation->frames.size()) {
		th->takeDamage(1);
		this->attack_animation->currentFrame = 0.0;
	}
}

void Character::playDeathAnimation(float time) {
	if (roundf(this->death_animation->currentFrame) != death_animation->frames.size()) {
		this->sprite = death_animation->Tick(time, !from_left);
	}
	else {
		is_dead = true;
	}
}

Direction Character::getDirection() {
	return direction;
}

bool Character::getFromLeft() {
	return from_left;
}

HealthBar Character::getHealthbar() {
	return *healthbar;
}

bool Character::getActive() {
	return is_active;
}

bool Character::getDead() {
	return is_dead;
}

UnitType Character::getType() {
	return type;
}

int Character::getHP() {
	return health;
}

float Character::getAngle() {
	return angle;
}

void Character::setDirection(Direction direction) {
	this->direction = direction;
}

void Character::setAngle(float angle) {
	this->angle = angle;
}

Character::~Character() {
	delete healthbar;
	delete idle_animation;
	delete run_animation;
	delete attack_animation;
	delete death_animation;
}

void Character::checkCollision(std::vector<Object> objects) {
	sf::FloatRect rect = this->sprite.getGlobalBounds();
	for (Object obj : objects) {
		sf::FloatRect o_rect = obj.r.getGlobalBounds();
		if (rect.intersects(obj.r.getGlobalBounds())) {
			if (obj.type == SOLID) {
				float overlapX = std::min(rect.left + rect.width, o_rect.left + o_rect.width) - std::max(rect.left, o_rect.left);
				float overlapY = std::min(rect.top + rect.height, o_rect.top + o_rect.height) - std::max(rect.top, o_rect.top);
				if (overlapX < overlapY) {
					if (rect.left < o_rect.left) {
						coordX = o_rect.left - rect.width / 2;
					}
					else {
						coordX = o_rect.left + o_rect.width + rect.width / 2;
					}
				}
				else {
					if (rect.top < o_rect.top) {
						coordY = o_rect.top - rect.height / 2;
					}
					else {
						coordY = o_rect.top + o_rect.height + rect.height / 2;
					}
				}
			}
		}
	}
}