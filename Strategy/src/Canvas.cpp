#include "../include/UI/Canvas.h"

Canvas::Canvas(sf::Font& font) {
	money = START_MONEY_VALUE;
	money_txt = sf::Text(std::to_string(money), font);
	money_txt.setFillColor(sf::Color::Yellow);
	money_txt.setPosition(60, 110);
	money_txt.setCharacterSize(16);

	money_tick = new Timer(1, 0, 0, 0, 5);
}

Canvas::~Canvas() {
	for (std::pair<Button*, Timer*> val : buttons_timers) {
		delete val.first;
		delete val.second;
	}
	delete money_tick;
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
	if (money_tick->getEnd()) {
		money += MONEY_PER_TICK;
		money_tick->Restart();
	}

	money_tick->Update();
	money_txt.setString(std::to_string(money));

	for (std::pair<Button*, Timer*> val : buttons_timers) {
		if (val.second->getEnd()) {
			UnitType u = units[val.first];
			if (u == MELEE && money - MELEE_COST >= 0 || u == RANGE && money - RANGE_COST >= 0 || u == TANK && money - TANK_COST >= 0
				|| u == SUPPORT && money - SUPPORT_COST >= 0) {
				val.first->setActive(true);
			} 
			else {
				val.first->setActive(false);
			}
		}
		else {
			val.first->setActive(false);
		}
		val.first->Update(window);
		val.second->Update();
	}

	money_txt.setString(std::to_string(money));

	window.draw(money_txt);
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
			switch (units[val.first]) {
			case MELEE:
				money -= MELEE_COST;
				break;
			case RANGE:
				money -= RANGE_COST;
				break;
			case TANK:
				money -= TANK_COST;
				break;
			case SUPPORT:
				money -= SUPPORT_COST;
				break;
			default:
				break;
			}
			return units[val.first];
		}
	}
	return NO_TYPE;
}

void Canvas::addMoney(int money) {
	this->money += money;
}
