#pragma once

#include "./Engine/GameObject.h"
#include "./Engine/State.h"
#include "./Engine/Globals.h"
#include "./UI/HealthBar.h"

class Townhall : public GameObject {
private:
	Animation* idle_anim;
	int health;
	HealthBar* healthbar;
public:
	Townhall(float x, float y, float h, float w, sf::Texture& texture);
	Townhall(float x, float y, float h, float w, std::map<State, sf::Texture>& textures);
	~Townhall();

	void Update();
	void Update(float time);
	void takeDamage(int damage);

	HealthBar* getHealthBar();
	int getHealth();
};

