#include "../include/Engine/Globals.h"
#include "../include/Engine/Character.h"
#include "../include/Units/Melee.h"
#include "../include/UI/Timer.h"

class AI {
private:
	int money;
	Timer* melee;
	int prev;

	bool canSend(UnitType type);
	void sendUnit(std::deque<Character*>& units, UnitType type);
	void checkReward(std::deque<Character*> enemies);
public:
	AI(std::deque<Character*>& units);
	~AI();

	void Update(std::deque<Character*>& units);
	void Analyse(std::deque<Character*> units, std::deque<Character*>& enemies);
};