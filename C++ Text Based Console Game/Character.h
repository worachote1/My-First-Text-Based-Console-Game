#pragma once

#include "Header2.h"
using namespace std;
class Character
{
public:	
	//constructor
	Character();

	// for player
	string name, race, sex;
	vector<string> playerRace;
	int health , totalHealth , maxHealth , heal ;
	int level, current_xp, base_xp, xp_to_level, minlevel, maxlevel;

	//method
	void characterCreation();
};

