#include "../include/Tower.h"

Tower::Tower(int x, int y, bool from_left) {
	coordX = x;
	coordY = y;
	this->from_left = from_left;

	bullet = new Bullet(-10, 10, from_left);
	attack_timer = new Timer(TOWER_ATTACK_SPEED, 0, 0, 0, 50);
}

Tower::~Tower() {
	delete bullet;
	delete attack_timer;
}

void Tower::Update(float time, std::deque<Warrior*>& enemies) {
	attack_timer->Update();
	if (damage > 0) {
		if (from_left) {
			if (!enemies.empty() && enemies.front()->getPosition().x <= TOWER_ATTACK_RANGE) {
				Shoot();
			}
		}
		else {
			if (!enemies.empty() && enemies.front()->getPosition().x >= WINDOW_WIDTH + TOWER_ATTACK_RANGE) {
				Shoot();
			}
		}
		bullet->Update(time);
		if (!enemies.empty()) {
			bullet->checkCollision(enemies.front(), damage);
			if (enemies.front()->getDead()) {
				enemies.pop_front();
			}
		}
	}
}

void Tower::Shoot() {
	if (attack_timer->getEnd() && bullet->getPosition().x == -10) {
		bullet->setPosition(coordX + SPRITE_SIZE / 2, coordY + SPRITE_SIZE);
		bullet->Launch();
		attack_timer->Restart();
	}
}

void Tower::addTowerDamage() {
	damage += TOWER_ATTACK_SCALE;
}

Bullet* Tower::getBullet() {
	return bullet;
}
