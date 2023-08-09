#include "../include/Townhall.h"

Townhall::~Townhall() {
	delete idle_anim;
	delete healthbar;
}

Townhall::Townhall(float x, float y, float h, float w, sf::Texture& texture) {
	this->coordX = x;
	this->coordY = y;
	this->height = h;
	this->width = w;

	this->health = 50;

	this->healthbar = new HealthBar(coordX + 50, coordY, health, 32);

	this->sprite.setTexture(texture);
	this->sprite.setScale(1.5, 1.5);
	this->sprite.setPosition(coordX, coordY);
}

Townhall::Townhall(float x, float y, float h, float w, std::map<State, sf::Texture>& textures) {
	this->coordX = x;
	this->coordY = y;
	this->height = h;
	this->width = w;

	this->health = 2;

	this->healthbar = new HealthBar(coordX + 10, coordY, health, 32);

	idle_anim = new Animation(textures[STAY], 0, 0, 31, 43, 7, ANIMATION_SPEED, 64);
}

void Townhall::Update() {
	this->healthbar->Update(coordX + 100, coordY, health);
}

void Townhall::Update(float time) {
	this->healthbar->Update(coordX + 10, coordY, health);
	this->sprite = idle_anim->Tick(time, true);
	sprite.setScale(2, 2);
	sprite.setPosition(coordX, coordY);
}

void Townhall::takeDamage(int damage) {
	health -= damage;
}

HealthBar* Townhall::getHealthBar() {
	return healthbar;
}

int Townhall::getHealth() {
	return health;
}
