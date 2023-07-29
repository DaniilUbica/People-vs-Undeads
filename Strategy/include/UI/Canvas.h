#pragma once

#include "./Button.h"
#include "./Timer.h"

class Canvas {
private:
	Button* melee;
public:
	Canvas(sf::Font& font);
	~Canvas();

	void drawButtons(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
};