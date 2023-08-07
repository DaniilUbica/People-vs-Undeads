#include "../include/AI.h"
#include <iostream>

AI::AI(std::deque<Warrior*>& units) {
	money = START_MONEY_VALUE;
	melee = new Timer(MELEE_COOLDOWN, 0, 0, 0, 50);
	prev = units.size();
	money_tick = new Timer(1, 0, 0, 0, 5);
}

AI::~AI() {
	delete melee;
}

void AI::Update(std::deque<Warrior*>& units) {
	if (money_tick->getEnd()) {
		money += MONEY_PER_TICK;
		money_tick->Restart();
	}

	money_tick->Update();

	melee->Update();
	if (melee->getEnd()) {
		sendUnit(units, MELEE);
		melee->Restart();
	}
}

void AI::Analyse(std::deque<Warrior*> units, std::deque<Warrior*>& enemies) {
	checkReward(enemies);
}

void AI::checkReward(std::deque<Warrior*> enemies) {
	if (prev > enemies.size()) {
		money += KILL_REWARD;
	}
		prev = enemies.size();
}

void AI::sendUnit(std::deque<Warrior*>& units, UnitType type) {
	switch (type) {
	case MELEE:
		if (canSend(type)) {
			units.push_back(new Melee(1230, 540 + SPRITE_SIZE, false, orc_melee_animation));
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
