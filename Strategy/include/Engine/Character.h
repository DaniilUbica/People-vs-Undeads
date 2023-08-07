#pragma once

#include <SFML/Graphics.hpp>
#include <queue>

#include "GameObject.h"
#include "State.h"
#include "../UI/HealthBar.h"
#include "../Townhall.h"

enum UnitType {
	MELEE,
	RANGE,
	SUPPORT,
	TANK,
	NO_TYPE,
};

enum Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NONE,
};

class Character : public GameObject {
protected:
	int damage;
	float angle = 0;
	bool from_left;
	bool is_active = true;
	bool is_dead = false;
	int health;
	HealthBar* healthbar;
	Direction direction;
	State state;
	UnitType type;

	Animation* idle_animation;
	Animation* run_animation;
	Animation* attack_animation;
	Animation* death_animation;
public:
	virtual void checkCollision(std::vector<Object> objects);
	virtual void takeDamage(int damage);
	virtual void Attack(Character* enemy);
	virtual void Attack(Townhall* th);
	void playDeathAnimation(float time);

	int getHP();
	float getAngle();
	Direction getDirection();
	bool getFromLeft();
	HealthBar getHealthbar();
	bool getActive();
	bool getDead();
	UnitType getType();

	void setDirection(Direction direction);
	void setAngle(float angle);

	inline bool operator==(const Character& rhs) {
		return this->getPosition().x == rhs.getPosition().x;
	}
};