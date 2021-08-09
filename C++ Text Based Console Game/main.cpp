#include "Character.h"
using namespace std;

void HUD();
void Combat();
void CombatHUD();
void Moving();
void CreateMonster();
void levelUp();


// for enemy
int monsterHp = 0, monsterXp = 0, monsterLevel = 0;
string monsterName[] = { "Goblin","Werewolf","Witch","Zombie","Giant","Dragon" };
int currentMonsterName = 5;
string currentMonster = " ";

Character character;

int couter = 3;


int main() {
	
	character.characterCreation();

	HUD();
	Moving();

	system("pause");

	return 0;
}
void HUD() {
	Sleep(500);
	system("cls");
	cout << "Name : " << character.name << "	  Health : " << character.totalHealth
		<< "\nRace : " << character.race << "\nSex : " << character.sex << "\nLevel : " << character.level
		<< "\nXp : " << character.current_xp << "\nXp to level : " << character.xp_to_level
		<<"\n\n--------------------------------------------------------------------------------\n"
		<< endl;
	Moving();
}
void CombatHUD() {
	Sleep(500);
	//change the top from HUD to CombatHUD when found monster
	system("cls");
	cout << "Name : " << character.name << "		|		Monster Name : " << currentMonster
		<< "\nhealth : " << character.totalHealth << "	|			Monster Hp : " << monsterHp
		<< "\nLevel : " << character.level << "		|		Monster Level : " << monsterLevel<<"\n\n";
	cout<< "\n\n--------------------------------------------------------------------------------\n"<< endl;
} 
void Combat() {
	CombatHUD();
	int playerAttack;
	int playerDamage = 8 * character.level/2;
	int monsterAttack = 6 * (monsterLevel / 2);
	if (character.totalHealth >= 1 && monsterHp >= 1) {
		cout << "\n\n";
		cout << "[1] Attack\n";
		cout << "[2] Block\n";
		cout << "[3] Run Away !!!\n\n";
		cin >> playerAttack;
		if (playerAttack == 1) {
			//Attack monster
			cout << "Attacking... you did " << playerDamage << " to the " << currentMonster << endl;
			monsterHp = monsterHp - playerDamage;
			Sleep(1000);
			CombatHUD();
			//monster attack you, if it still alive
			if (monsterHp >= 1) {
				cout << "\nMonster's attacking you...\n";
				character.totalHealth -= monsterAttack;
				cout << "You're suffered " << monsterAttack << " hp : " << character.totalHealth << endl;
				// Change to function
				if (character.totalHealth<=0){
					character.totalHealth = 0;
					//Game is over
					system("cls");
					cout << "You die\nYou were level : " << character.level << " you got killed by " << currentMonster << "\n";
					Sleep(2000);
					exit(0);
				}
			}
			//monster die
			else if (monsterHp <= 0) {
				monsterHp = 0;
				
				cout << "\n";
				cout << "You defeated " << currentMonster << " you're rewarded with " << monsterXp << " xp\nWell Done!!!\n";
				if (character.level != character.xp_to_level) {
					character.current_xp += monsterXp;
					levelUp();
				} 
				Sleep(1000);
				HUD();
			}
			Sleep(1000);
			Combat();
		}
		else if (playerAttack == 2)
		{
			//Block
			// There is 50-50 chance of manage to block 
			cout << "You're blocking....\n";
			int i = (rand() % 100) + 1;
			if (i >= 50) {
				cout << "You blocked the incoming attacking !!!\n";
				character.heal = (character.level * 10) / 2;
				cout << "You've been healed for " << character.heal << endl;
				character.totalHealth += character.heal;
				Sleep(1000);
				Combat();
			}
			else {
				cout << "You failed to block !!!" << endl;
				character.totalHealth -= monsterAttack;
				cout << "Monster attacked through your armor " << monsterAttack << " current hp : " << character.totalHealth << endl;
				Sleep(1000);
				Combat();
			}	
		}
		else if (playerAttack==3) {
			//Run
			cout << "You're try to run !!!\n";
			int x = (rand() % 100) + 1;
			if (x >= 50) {
				cout << "You run away !!!\n";
				// if suceed to run away ,go back to hud
				HUD();
			}
			else {
				cout << "You failed to run away\n";
				//you failed try to run away , so it's easy to get more damage from monster
				character.totalHealth -= (monsterAttack + 10);
				cout << "You're suffered " << (monsterAttack + 10) << " current hp : " << character.totalHealth << "\n";
				Sleep(1000);
				Combat();
			}
		}
		else {
			cout << "Invalid Number!!!\n";
			Sleep(500);
			Combat();
		}
	
	}
	
}
void Moving() {
	int choice;
	cout << "[1] Move Forward\n";
	cout << "[2] Pray for heal\n";
	cout << "[3] Move Backward\n";
	cout << "\n\n";
	cin >> choice;
	if (choice == 1) {
		int temp = rand() % 100 + 1;
		cout << "You're moving forward...\n";
		if (temp >= 50) {
			CreateMonster();
			string tempName = monsterName[rand() % currentMonsterName];
			cout << "You found a " << tempName << " prepare to fight !!! \n\n";
			currentMonster = tempName;
			Sleep(1000);
			Combat();

		}
		cout << "You found no monster";
		Sleep(1000);
		HUD();

	}
	else if (choice == 2) {
		cout << "You wanna go to church for pray\n";
		if (character.totalHealth <= 99) {
			character.totalHealth += 5 * character.level;
		}
		cout << "You get healed !!!" << " ,your health is now " << character.totalHealth << endl;
		Sleep(1000);
		HUD();
	}
	else if (choice == 3) {
		int temp = rand() % 100 + 1;
		cout << "You're moving backward...\n";
		if (temp >= 50) {
			CreateMonster();
			string tempName = monsterName[rand() % currentMonsterName];
			cout << "You found a " << tempName << " prepare to fight !!! \n\n";
			currentMonster = tempName;
			Sleep(1000);
			Combat();
			
		}
		cout << "You found no monster";
		Sleep(1000);
		HUD();
	}
	else {
		cout << "Invalid Number!!!\n";
		Sleep(500);
		Moving();
	}
}
void levelUp() {
	if (character.current_xp >= character.xp_to_level) {
		// level system
		// algorithm for level curve
		character.xp_to_level += floor(character.level + 25 * pow(2, character.level / 7));
		character.totalHealth = floor(character.totalHealth + 13 * pow(2, character.level / 8));
		if (character.level >= character.minlevel && character.level <= character.maxlevel) {
			character.level++;
		}
		character.maxHealth = character.totalHealth;
		cout << "Level up !!! , you're now level : " << character.level << endl;
		cout << "Your total health increased , now your health is " << character.totalHealth << endl;
		cout << "\n";
		Sleep(1000);
		levelUp();
	}
	Sleep(2000);
	HUD();
}
// setting level and hp for monster
void CreateMonster() {
	monsterHp = 30;
	monsterLevel = (rand() % 3) + character.level;
	
	//May be to fixed this value
	monsterHp = (rand() % 30) * monsterLevel;

	monsterXp = monsterHp;
	if (monsterHp == 0) {
		CreateMonster();
	}
	if (monsterLevel == 0) {
		CreateMonster();
	}
}