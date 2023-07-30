#pragma once

#include "../Engine/Globals.h"
#include "./Button.h"
#include "./Timer.h"

enum UnitType {
	MELEE,
	RANGE,
	SUPPORT,
	TANK,
	NO_TYPE,
};

class Canvas {
private:
	Button* melee;
	Timer* melee_timer;
	std::map<Button*, UnitType> units;
	std::map<Button*, Timer*> buttons_timers;
public:
	~Canvas();

	void drawButtons(sf::RenderWindow& window);
	void drawTimers(sf::RenderWindow& window);
	void Update(sf::RenderWindow& window);
	void addButton(float x, float y, float w, float h, sf::Vector3i border_color, sf::Vector3i button_color, sf::Vector3i text_color, sf::Text text, float time, UnitType type);
	UnitType checkClick(sf::RenderWindow& window, sf::Event& event);
};