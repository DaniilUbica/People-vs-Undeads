#include "../include/Units/Bullet.h"

Bullet::Bullet(int coordX, int coordY) {
	this->coordX = coordX;
	this->coordY = coordY;

	rect.setPosition(coordX, coordY);
	rect.setSize(sf::Vector2f(6, 6));
	rect.setFillColor(sf::Color::Red);
}

void Bullet::Launch() {
	isLaunched = true;
}

void Bullet::Destroy() {
	this->setPosition(-10, 10);
	isLaunched = false;
}

void Bullet::Update(float time) {
	if (isLaunched) {
		if (from_left) {
			coordX += BULLET_SPEED * time;
		}
		else {
			coordX -= BULLET_SPEED * time;
		}
	}
	else {
		Destroy();
	}
	rect.setPosition(coordX, coordY);
}

void Bullet::checkCollision(Character* enemy) {
	if (rect.getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds())) {
		this->isLaunched = false;
		Destroy();
		enemy->takeDamage(BULLET_DAMAGE);
	}
}

void Bullet::setTexture(sf::Texture& texture) {
	sprite.setTexture(texture);
}

void Bullet::setLaunched(bool l) {
	isLaunched = l;
}

bool Bullet::getLaunched() {
	return isLaunched;
}
