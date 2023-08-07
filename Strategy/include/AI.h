#include "../include/Engine/Globals.h"
#include "../include/Engine/Character.h"
#include "../include/Units/Melee.h"
#include "../include/UI/Timer.h"
#include "../include/Textures.h"

class AI {
private:
	int money;
	Timer* melee;
	Timer* money_tick;
	int prev;

	bool canSend(UnitType type);
	void sendUnit(std::deque<Warrior*>& units, UnitType type);
	void checkReward(std::deque<Warrior*> enemies);
public:
	AI(std::deque<Warrior*>& units);
	~AI();

	void Update(std::deque<Warrior*>& units);
	void Analyse(std::deque<Warrior*> units, std::deque<Warrior*>& enemies);
};