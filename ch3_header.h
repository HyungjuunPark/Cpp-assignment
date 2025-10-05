#ifndef __CHARACTOR_H__
#define __CHARACTOR_H__
#include <string>
using namespace std;

class Charactor {
private:
	string name;
	int hp;
	int attackPower;

public:
	void InitMembers(const string name, int hp, int power);
	void ShowStatus();
	void Attack(Charactor& target);
	void TakeDamage(int damage);
	bool IsDead();
};

#endif

