//����-���
//#include <iostream>
//#include "Charactor.h"
//#include <string>
//#include <cstdlib>
//
//using namespace std;
//
//void Charactor::InitMembers(const string name, int hp, int power) {
//	this->name = name;
//	this->hp = hp;
//	this->attackPower = power;
//}
//
//void Charactor::ShowStatus() {
//	cout << "�̸�: " << name << ", HP: " << hp << '\n';
//}
//
//void Charactor::Attack(Charactor& target) {
//	cout << name << "��(��) " << target.name << "��(��) �����Ͽ� " << 
//		attackPower << "�� ���ظ� �������ϴ�!\n";
//	target.TakeDamage(attackPower);
//}
//
//void Charactor::TakeDamage(int damage) {
//	hp -= damage;
//}
//
//bool Charactor::IsDead() {
//	if (hp <= 0)
//		return true;
//	else
//		return false;
//}