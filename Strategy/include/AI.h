#include "../include/Engine/Globals.h"
#include "../include/Engine/Character.h"
#include "../include/Units/Melee.h"
#include "../include/Units/Tank.h"
#include "../include/Units/Range.h"
#include "../include/UI/Timer.h"
#include "../include/Textures.h"
#include "../include/Tower.h"

class AI {
private:
	int money;
	Timer* melee, *range, *tank;
	Timer* money_tick;
	int prev;
	int ally_prev;
	Tower* tower;
	int tower_updates_counter = 0;
	int kills_counter = 0;

	bool canSend(UnitType type);
	void sendUnit(std::deque<Warrior*>& units, UnitType type);
	void checkReward(std::deque<Warrior*> enemies);
	void buildTower();
public:
	AI(std::deque<Warrior*>& units);
	~AI();

	void Update(float time, std::deque<Warrior*>& units, std::deque<Warrior*>& enemies);
	void Analyse(std::deque<Warrior*>& units, std::deque<Warrior*>& enemies);
	void restartTimers();

	Tower* getTower();
};