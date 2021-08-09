#include "Character.h"

Character::Character() {
	
	name = " ", race = " ", sex=" ";
	
	playerRace = { "knight", "veteran", "archer", "king" };

	level = 0, health = 0, totalHealth = 0, maxHealth = 0, heal = 0;

	level = 1, current_xp = 0, base_xp = 93;
	xp_to_level = base_xp;
	minlevel = 1, maxlevel = 25;
}

void Character::characterCreation() {
	int couter = 0;

	// create character
	cout << "Enter Characters Name : ";
	getline(cin, name);
	cout << "Enter Characters race: \n";
	cout << "Knight\n";
	cout << "Veteran\n";
	cout << "Archer\n";
	cout << "King\n";
	cout << "Type Below your Race : \n\n";
	cin >> race;
	//whatever player type it'll be put all letter into lowercase
	for_each(race.begin(), race.end(), [](char& c) {
		c = ::tolower(c);
		});

	for (int i = 0; i < sizeof(playerRace); i++) {
		if (race == "knight") {
			health = 90;
			break;
		}
		if (race == "veteran") {
			health = 150;
			break;
		}
		if (race == "archer") {
			health = 60;
			break;
		}
		if (race == "king") {
			health = 70;
			break;
		}
		// if player type not in specify playerRace , just let's player have 100 hp as default
		else
		{
			health = 100;
			break;
		}
	}
	cout << "\n";
	cout << "Enter Characters sex : ";
	cin >> sex;
	system("cls");
	// create loading character scene

	for (int i = 0; i <= couter; i++) {
		if (i == 0)
			cout << "creating character.\n";
		if (i == 1)
			cout << "creating character..\n";
		if (i == 2) {
			cout << "creating character...\n";
			break;
		} 
			
		Sleep(400);
		system("cls");
		couter++;
	}
	race[0] = toupper(race[0]); // make the first letter of race to uppercase
	totalHealth = health;
	maxHealth = totalHealth;
}