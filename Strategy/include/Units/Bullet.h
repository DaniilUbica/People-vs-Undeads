#pragma once

#include "../Engine/Globals.h"
#include "../Engine/Character.h"

class Bullet : public GameObject {
private:
	bool isLaunched = false;
	bool from_left;
public:

	sf::RectangleShape rect;
	Bullet(int coordX, int coordY);

	void Launch();
	void Destroy();
	void Update(float time);
	void checkCollision(Character* enemy);

	void setTexture(sf::Texture& texture);
	void setLaunched(bool l);

	bool getLaunched();
};

