#include <iostream>
#include "ch3_header.h"
#include <string>
#include <cstdlib>

using namespace std;

void Charactor::InitMembers(const string name, int hp, int power) {
	this->name = name;
	this->hp = hp;
	this->attackPower = power;
}

void Charactor::ShowStatus() {
	cout << "이름: " << name << ", HP: " << hp << '\n';
}

void Charactor::Attack(Charactor& target) {
	cout << name << "이(가) " << target.name << "을(를) 공격하여 " << 
		attackPower << "의 피해를 입혔습니다!\n";
	target.TakeDamage(attackPower);
}

void Charactor::TakeDamage(int damage) {
	hp -= damage;
}

bool Charactor::IsDead() {
	if (hp <= 0)
		return true;
	else
		return false;
}
