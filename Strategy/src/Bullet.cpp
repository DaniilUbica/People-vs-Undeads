#include "../include/Units/Bullet.h"

Bullet::Bullet(int coordX, int coordY, bool from_left) {
	this->coordX = coordX;
	this->coordY = coordY;
	this->from_left = from_left;

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

void Bullet::checkCollision(Character* enemy, int damage) {
	if (rect.getGlobalBounds().intersects(enemy->getSprite().getGlobalBounds())) {
		this->isLaunched = false;
		Destroy();
		enemy->takeDamage(damage);
	}
}

void Bullet::checkCollision(Townhall* th) {
	if (rect.getGlobalBounds().intersects(th->getSprite().getGlobalBounds())) {
		this->isLaunched = false;
		Destroy();
		th->takeDamage(1);
	}
}

void Bullet::setTexture(sf::Texture& texture) {
	sprite.setTexture(texture);
}

void Bullet::setLaunched(bool l) {
	isLaunched = l;
}

void Bullet::setDamage(int damage) {

}

bool Bullet::getLaunched() {
	return isLaunched;
}
