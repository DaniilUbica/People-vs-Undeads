#pragma once

#include "../Engine/Globals.h"
#include "../Engine/Character.h"

class Bullet : public GameObject {
private:
	bool isLaunched = false;
	bool from_left;
public:

	sf::RectangleShape rect;
	Bullet(int coordX, int coordY, bool from_left);

	void Launch();
	void Destroy();
	void Update(float time);
	void checkCollision(Character* enemy);
	void checkCollision(Townhall* th);
	void checkCollision(Character* enemy, int damage);

	void setTexture(sf::Texture& texture);
	void setLaunched(bool l);
	void setDamage(int damage);

	bool getLaunched();
};

