#include "../include/AI.h"
#include <iostream>

AI::AI() {
	money = START_MONEY_VALUE;
	melee = new Timer(MELEE_COOLDOWN, 0, 0, 0, 50);
}

AI::~AI() {
	delete melee;
}

void AI::Update(std::deque<Character*>& units) {
	melee->Update();
	if (melee->getEnd()) {
		sendUnit(units, MELEE);
		melee->Restart();
	}
}

void AI::sendUnit(std::deque<Character*>& units, UnitType type) {
	switch (type) {
	case MELEE:
		if (canSend(type)) {
			units.push_back(new Melee(750.0, 200, false));
			money -= MELEE_COST;
		}
		break;
	case RANGE:
		break;
	case SUPPORT:
		break;
	case TANK:
		break;
	case NO_TYPE:
		break;
	default:
		break;
	}
}

bool AI::canSend(UnitType type) {
	switch (type) {
	case MELEE:
		if (MELEE_COST <= money) {
			return true;
		}
		break;
	case RANGE:
		if (RANGE_COST <= money) {
			return true;
		}
		break;
	case SUPPORT:
		if (SUPPORT_COST <= money) {
			return true;
		}
		break;
	case TANK:
		if (TANK_COST <= money) {
			return true;
		}
		break;
	case NO_TYPE:
		break;
	default:
		break;
	}
	return false;
}