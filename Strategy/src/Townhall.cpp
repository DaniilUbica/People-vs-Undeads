#include "../include/Townhall.h"

Townhall::Townhall(float x, float y, float h, float w) {
	this->coordX = x;
	this->coordY = y;
	this->height = h;
	this->width = w;

	this->health = 50;

	this->healthbar = new HealthBar(coordX + 10, coordY, health, 32);

	rect.setSize(sf::Vector2f(h, w));
	rect.setPosition(coordX, coordY);
	rect.setFillColor(sf::Color::Black);
}

void Townhall::Update() {
	this->healthbar->Update(coordX + 10, coordY, health);
}

void Townhall::takeDamage(int damage) {
	health -= damage;
}
