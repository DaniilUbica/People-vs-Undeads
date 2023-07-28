#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

#include "GameObject.h"
#include "State.h"
#include "../UI/HealthBar.h"

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE,
};

class Character : public GameObject {
protected:
	int health;
	int damage;
	float angle = 0;
	bool from_left;
	bool is_active = true;
	bool is_dead = false;
	HealthBar* healthbar;
	Direction direction;
	State state;

	Animation* idle_animation;
	Animation* run_animation;
	Animation* attack_animation;
	Animation* death_animation;
public:
	virtual void Update(std::deque<Character*>& enemies, std::deque<Character*>& allies) = 0;
	virtual void checkCollision(std::vector<Object> objects);
	virtual void takeDamage(int damage);
	virtual void Attack(Character* enemy);
	void playDeathAnimation();

	int getHP();
	float getAngle();
	Direction getDirection();
	bool getFromLeft();
	HealthBar getHealthbar();
	bool getActive();
	bool getDead();

	void setDirection(Direction direction);
	void setAngle(float angle);

	inline bool operator==(const Character& rhs) {
		return this->getPosition().x == rhs.getPosition().x;
	}
};