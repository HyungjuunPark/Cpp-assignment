#include <iostream>
#include "ch3_header.h"
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	srand(time(NULL));
	Charactor warrior;
	Charactor goblin;

	warrior.InitMembers("전사", 100, 5);
	goblin.InitMembers("고블린", 50, 8);

	cout << "--- 캐릭터 생성 ---\n";

	warrior.ShowStatus();
	goblin.ShowStatus();
	cout << '\n';

	while (warrior.IsDead() == false && goblin.IsDead() == false) {

		warrior.Attack(goblin);
		goblin.Attack(warrior);
		warrior.ShowStatus();
		goblin.ShowStatus();

		cout << '\n';
	}
	cout << "--- 결투 종료 ---\n";

	if (warrior.IsDead() == true) {
		cout << "승리자: " << "goblin" << '\n';
	}
	else
		cout << "승리자: " << "warrior" << '\n';
	return 0;
}

