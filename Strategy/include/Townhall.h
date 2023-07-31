#pragma once

#include "./Engine/GameObject.h"
#include "./UI/HealthBar.h"

class Townhall : public GameObject {
private:
public:
	int health;
	HealthBar* healthbar;
	sf::RectangleShape rect;

	Townhall(float x, float y, float h, float w);

	void Update();
	void takeDamage(int damage);
};

