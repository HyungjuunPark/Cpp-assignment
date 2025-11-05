#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const int PLAYER_DEFAULT_HEALTH = 100;
const int MONSTER_DEFAULT_HEALTH = 50;

class Monster;

class Entity {
protected:
	string name;
	int health;
public:
	Entity(string name, int defaultHealth) : name(name), health(defaultHealth) {}
	~Entity() {}

	void takeDamage(int dmg) {
		health -= dmg;
		if (health < 0) health = 0;
		cout << " [" << name << "]이 " << dmg << "의 데미지를 입었습니다." << " (HP: " << health << ")\n";
	}
	bool isAlive() const {
		return health > 0;
	}
	string getName() const { return name; }

	void displayStatus() const {
		cout << "Entity [" << name << "] - HP: " << health << '\n';
	}
	void attack(Entity& target);
};

class Player : public Entity {
public:
	Player(string name) : Entity(name, PLAYER_DEFAULT_HEALTH) {}

	void displayStatus() const {
		cout << "Player [" << name << "] - HP: " << health << '\n';
	}

	void attack(Monster& target);
};

class Monster : public Entity {
public:
	Monster(string name) : Entity(name, MONSTER_DEFAULT_HEALTH) {}

	void displayStatus() const {
		cout << "Monster [" << name << "] - HP: " << health << '\n';
	}

	void attack(Player& target);
};

void Player::attack(Monster& target) {
	int damage = rand() % 30 + 1;

	cout <<"Player ["<<name<<"]가 Monster [" << target.getName() << "]을(를) 공격!\n";
	target.takeDamage(damage);
}

void Monster::attack(Player& target) {
	int damage = rand() % 11 + 20;

	cout << "Monster [" << name << "]가 Player [" << target.getName() << "]을(를) 공격!\n";
	target.takeDamage(damage);
}

void Entity::attack(Entity& target) {}

int main() {
	srand(static_cast<unsigned int>(time(NULL))); // static_cast<unsigned int> 추가

	Player player("Hero");
	Monster monster("Goblin");

	cout << "--- 전투 시작! ---\n";

	while (player.isAlive() && monster.isAlive()) {

		player.attack(monster);

		if (monster.isAlive()) {
			monster.attack(player);
		}

		cout << "--- 턴 종료 ---\n";
		player.displayStatus();
		monster.displayStatus();
		cout << '\n';
	}

	cout << "--- 전투 종료! ---\n";
	if (player.isAlive()) {
		cout << "Player [Hero] 승리!\n";
	}
	else {
		cout << "Monster [Goblin] 승리!\n";
	}

	return 0;
}