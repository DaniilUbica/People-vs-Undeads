#include "../include/UI/Canvas.h"
#include <iostream>

Canvas::~Canvas() {
	for (std::pair<Button*, Timer*> val : buttons_timers) {
		delete val.first;
		delete val.second;
	}
}

void Canvas::drawButtons(sf::RenderWindow& window) {
	for (std::pair<Button*, Timer*> val : buttons_timers) {
		val.first->drawButton(window);
	}
}

void Canvas::drawTimers(sf::RenderWindow& window) {
	for (std::pair<Button*, Timer*> val : buttons_timers) {
		window.draw(val.second->getRect());
	}
}

void Canvas::Update(sf::RenderWindow& window) {
	for (std::pair<Button*, Timer*> val : buttons_timers) {
		if (val.second->getEnd()) {
			val.first->setActive(true);
		}
		else {
			val.first->setActive(false);
		}
		val.first->Update(window);
		val.second->Update();
	}
}

void Canvas::addButton(float x, float y, float w, float h, sf::Vector3i border_color, sf::Vector3i button_color, sf::Vector3i text_color, sf::Text text, float time, UnitType type) {
	Button* btn = new Button(x, y, w, h, sf::Vector3i(168, 79, 79),
		sf::Vector3i(212, 73, 73), sf::Vector3i(255, 255, 255), text);

	buttons_timers.insert({ btn, new Timer(time, x, y, w, h) });
	units.insert({ btn, type });
}

UnitType Canvas::checkClick(sf::RenderWindow& window, sf::Event& event) {
	for (std::pair<Button*, Timer*> val : buttons_timers) {
		if (val.first->checkClick(window, event)) {
			val.second->Restart();
			return units[val.first];
		}
	}
	return NO_TYPE;
}
