#include "../include/AI.h"
#include <iostream>

AI::AI(std::deque<Warrior*>& units) {
	money = START_MONEY_VALUE;
	melee = new Timer(MELEE_COOLDOWN, 0, 0, 0, 50);
	range = new Timer(RANGE_COOLDOWN, 0, 0, 0, 50);
	prev = units.size();
	ally_prev = 0;
	money_tick = new Timer(1, 0, 0, 0, 5);

	tower = new Tower(ENEMY_START_X, ENEMY_START_Y, false);
}

AI::~AI() {
	delete melee;
}

void AI::Update(float time, std::deque<Warrior*>& units, std::deque<Warrior*>& enemies) {
	if (money_tick->getEnd()) {
		money += MONEY_PER_TICK;
		money_tick->Restart();
	}

	money_tick->Update();
	melee->Update();
	range->Update();
	tower->Update(time, enemies);
}

void AI::Analyse(std::deque<Warrior*>& units, std::deque<Warrior*>& enemies) {
	int choice = rand() % 2 + 0;

	if (ally_prev > units.size()) {
		money += ALLY_DEATH_REWARD;
	}
	ally_prev = units.size();

	checkReward(enemies);
	if (!enemies.empty() && money <= MELEE_COST && units.empty()) {
		money += KILL_REWARD;
	}
	if ((enemies.empty() && units.size() >= 3 || 
			units.size() - enemies.size() >= 3) && canSend(TOWER)) {
		buildTower();
	}
	else {
		if (melee->getEnd() && choice == 0) {
			sendUnit(units, MELEE);
			melee->Restart();
		}
		if (range->getEnd() && choice == 1) {
			sendUnit(units, RANGE);
			range->Restart();
		}
	}
}

void AI::restartTimers() {
	melee->Restart();
	range->Restart();
	money_tick->Restart();
}

Tower* AI::getTower() {
	return tower;
}

void AI::checkReward(std::deque<Warrior*> enemies) {
	if (prev > enemies.size()) {
		money += KILL_REWARD;
	}
	prev = enemies.size();
}

void AI::buildTower() {
	if (canSend(TOWER)) {
		money -= TOWER_COST - TOWER_COST_SCALE * tower_updates_counter;
		tower->addTowerDamage();
		tower_updates_counter++;
	}
}

void AI::sendUnit(std::deque<Warrior*>& units, UnitType type) {
	int start_x = ENEMY_START_X;
	if (!units.empty() && units.back()->getPosition().x <= PLAYER_START_X) {
		start_x = units.back()->getPosition().x + INTERVAL;
	}
	switch (type) {
	case MELEE:
		if (canSend(type)) {
			units.push_back(new Melee(start_x, ENEMY_START_Y + SPRITE_SIZE, false, orc_melee_animation));
			money -= MELEE_COST;
		}
		break;
	case RANGE:
		if (canSend(type)) {
			units.push_back(new Range(start_x, ENEMY_START_Y + SPRITE_SIZE, false, orc_melee_animation));
			money -= RANGE_COST;
		}
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
	case TOWER:
		if (TOWER_COST - TOWER_COST_SCALE * tower_updates_counter <= money) {
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
