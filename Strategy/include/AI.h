#include "../include/Engine/Globals.h"
#include "../include/Engine/Character.h"
#include "../include/Enemies/Melee.h"
#include "../include/UI/Timer.h"

class AI {
private:
	int money;
	Timer* melee;

	bool canSend(UnitType type);
	void sendUnit(std::deque<Character*>& units, UnitType type);
public:
	AI();
	~AI();

	void Update(std::deque<Character*>& units);
};