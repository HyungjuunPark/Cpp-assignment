#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Entity {
protected:
    string name;
    int health;
public:
    Entity(string name, int defaultHealth) : name(name), health(defaultHealth) {}
    virtual ~Entity() {}

    virtual void takeDamage(int dmg) {
        health -= dmg;
        if (health < 0) health = 0;
        cout << "  [" << name << "]이 " << dmg << "의 데미지를 입었습니다. "
            << "(HP: " << health << ")\n";
    }
    bool isAlive() const {
        return health > 0;
    }
    string getName() const { return name; }

    virtual void displayStatus() const {
        cout << "Entity [" << name << "] - HP: " << health << endl;
    }
};

class Player;
class Monster;

class Player : public Entity {
public:
    Player(string name) : Entity(name, 100) {
    }

    void displayStatus() const  {
        cout << "Player [" << name << "] - HP: " << health << endl;
    }

    void attack(Monster& target);
};

class Monster : public Entity {
public:
    Monster(string name, int defaultHealth = 50) : Entity(name, 50) {
    }

    void displayStatus() const  {
        cout << "Monster [" << name << "] - HP: " << health << endl;
    }

    void attack(Player& target);
};

void Player::attack(Monster& target) {
    cout << "Player [" << this->name << "]가 Monster ["
        << target.getName() << "]을(를) 공격!\n";
    int damage = rand() % 30 + 1;
    target.takeDamage(damage);
}

void Monster::attack(Player& target) {
    cout << "Monster [" << this->name << "]가 Player ["
        << target.getName() << "]을(를) 공격!\n";
    int damage = rand() % 11 + 20;
    target.takeDamage(damage);
}

int main() {
    srand(time(NULL));

    Player player("Hero");
    Monster monster("Goblin");

    player.displayStatus();
    monster.displayStatus();

    cout << "\n--- 전투 시작! ---\n";

    while (player.isAlive() && monster.isAlive()) {
        player.attack(monster);

        if (monster.isAlive()) {
            monster.attack(player);
        }

        cout << "--- 턴 종료 ---\n";
        player.displayStatus();
        monster.displayStatus();
        cout << "\n";
    }

    cout << "--- 전투 종료! ---\n";
    if (player.isAlive()) {
        cout << "Player [" << player.getName() << "] 승리!\n";
    }
    else {
        cout << "Monster [" << monster.getName() << "] 승리!\n";
    }

    return 0;
}
