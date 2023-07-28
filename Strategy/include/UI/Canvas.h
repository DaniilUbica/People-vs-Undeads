#pragma once

#include "./Button.h"
#include "./Timer.h"

class Canvas {
private:
	Button* melee;
public:
	Canvas();
	~Canvas();

	void drawButtons(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
};