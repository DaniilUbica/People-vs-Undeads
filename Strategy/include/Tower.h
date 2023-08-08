#pragma once

#include "./Engine/Globals.h"
#include "./Engine/GameObject.h"
#include "./Units/Bullet.h"
#include "./UI/Timer.h"
#include "./Units/Warrior.h"

class Tower : public GameObject {
private:
	int damage = 0;
	Timer* attack_timer;
	Bullet* bullet;
	bool from_left;

	void Shoot();
public:
	Tower(int x, int y, bool from_left);
	~Tower();

	void Update(float time, std::deque<Warrior*>& enemies);
	void addTowerDamage();

	Bullet* getBullet();
};