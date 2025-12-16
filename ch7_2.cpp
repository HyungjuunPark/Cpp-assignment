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
        cout << "  [" << name << "]이(가) " << dmg << "의 데미지를 입었습니다. "
            << "(HP: " << health << ")\n";
    }

    bool isAlive() const {
        return health > 0;
    }

    string getName() const { return name; }

    virtual void displayStatus() const {
        cout << "개체 [" << name << "] - HP: " << health << endl;
    }

    virtual void heal(int amount) {
        health += amount;
        cout << "  [" << name << "]이(가) " << amount << "의 체력을 회복했습니다. (HP: " << health << ")\n";
    }
};

class Player;
class Monster;
class MagicMonster;

class Player : public Entity {
private:
    bool m_hasSword;
    bool m_hasShield;
    int m_itemsAcquiredCount;

public:
    Player(string name) : Entity(name, 100), m_hasSword(false), m_hasShield(false), m_itemsAcquiredCount(0) {}

    void displayStatus() const override {
        cout << "플레이어 [" << name << "] - HP: " << health;
        if (m_hasSword) cout << " (검 장착)";
        if (m_hasShield) cout << " (방패 장착)";
        cout << " (획득 아이템: " << m_itemsAcquiredCount << "/3)";
        cout << endl;
    }

    void takeDamage(int dmg) override {
        if (m_hasShield) {
            cout << "  [" << name << "]의 방패가 공격을 막아냈습니다!\n";
            m_hasShield = false; // 방패 소모
        }
        else {
            Entity::takeDamage(dmg);
        }
    }

    void findAndUseItem() {
        if (m_itemsAcquiredCount >= 3) return;

        int chance = rand() % 100;
        if (chance < 20) { // 20% 확률로 아이템 발견
            m_itemsAcquiredCount++;
            int itemType = rand() % 3;

            if (itemType == 0) {
                if (!m_hasSword) {
                    m_hasSword = true;
                    cout << "  [" << name << "]이(가) 검을 획득했습니다! (누적 아이템 " << m_itemsAcquiredCount << "/3)\n";
                }
                else {
                    cout << "  [" << name << "]이(가) 검을 찾았지만 이미 가지고 있습니다! (누적 아이템 " << m_itemsAcquiredCount << "/3)\n";
                }
            }
            else if (itemType == 1) {
                if (!m_hasShield) {
                    m_hasShield = true;
                    cout << "  [" << name << "]이(가) 방패를 획득했습니다! (누적 아이템 " << m_itemsAcquiredCount << "/3)\n";
                }
                else {
                    cout << "  [" << name << "]이(가) 방패를 찾았지만 이미 가지고 있습니다! (누적 아이템 " << m_itemsAcquiredCount << "/3)\n";
                }
            }
            else {
                cout << "  [" << name << "]이(가) 포션을 발견하여 사용합니다! (누적 아이템 " << m_itemsAcquiredCount << "/3)\n";
                heal(10);
            }
        }
    }

    void attack(Monster& target);
    void attack(MagicMonster& target);
};

class Monster : protected Entity {
public:
    // 부모의 public 멤버를 가져옴
    using Entity::takeDamage;
    using Entity::isAlive;
    using Entity::getName;

    Monster(string name, int defaultHealth = 50) : Entity(name, defaultHealth) {}

    void displayStatus() const override {
        cout << "몬스터 [" << name << "] - HP: " << health << endl;
    }

    void attack(Player& target);
};

class MagicMonster : public Monster {
protected:
    int magicShield;
public:
    MagicMonster(string name)
        : Monster(name, 50), magicShield(30) {
    }

    using Entity::isAlive;

    void takeDamage(int dmg) override {
        cout << "  [" << name << "]의 매직 쉴드가 공격을 흡수합니다!\n";
        if (dmg <= magicShield) {
            magicShield -= dmg;
        }
        else {
            int remainingDmg = dmg - magicShield;
            magicShield = 0;
            Entity::takeDamage(remainingDmg);
        }
    }

    void displayStatus() const override {
        cout << "매직 몬스터 [" << name << "] - HP: " << health
            << ", 쉴드: " << magicShield << endl;
    }

    void regenerateShield() {
        if (magicShield < 30) {
            magicShield += 5;
            if (magicShield > 30) magicShield = 30;
            cout << "  [" << name << "]의 쉴드가 5만큼 회복되었습니다. (현재: " << magicShield << ")\n";
        }
    }
};

void Player::attack(Monster& target) {
    cout << "플레이어 [" << name << "]가 몬스터 [" << target.getName() << "]를 공격!\n";
    int damage = rand() % 30 + 1;
    if (m_hasSword) damage += 5;
    target.takeDamage(damage);
}

void Player::attack(MagicMonster& target) {
    cout << "플레이어 [" << name << "]가 매직 몬스터 [" << target.getName() << "]를 공격!\n";
    int damage = rand() % 30 + 1;
    if (m_hasSword) damage += 5;
    target.takeDamage(damage);
}

void Monster::attack(Player& target) {
    cout << "몬스터 [" << name << "]가 플레이어 [" << target.getName() << "]를 공격!\n";
    int damage = rand() % 11 + 20;
    target.takeDamage(damage);
}

int main() {
    srand(static_cast<unsigned int>(time(NULL)));

    Player player("용사");

    cout << "--- [기능 테스트] 기본 몬스터 (Protected 상속) ---\n";
    Monster monster("고블린");
    monster.takeDamage(10);
    cout << "  고블린 생존 여부: " << (monster.isAlive() ? "생존" : "사망") << endl;

    cout << "\n--- [메인 전투] 플레이어 vs 매직 몬스터 ---\n";
    MagicMonster magicGoblin("매직 고블린");

    player.displayStatus();
    magicGoblin.displayStatus();

    while (player.isAlive() && magicGoblin.isAlive()) {
        player.attack(magicGoblin);

        if (magicGoblin.isAlive()) {
            magicGoblin.attack(player);
        }

        player.findAndUseItem();
        magicGoblin.regenerateShield();

        cout << "--- 턴 종료 ---\n";
        player.displayStatus();
        magicGoblin.displayStatus();
        cout << "\n";
    }

    cout << "--- 전투 종료! ---\n";
    if (player.isAlive()) {
        cout << "플레이어 [" << player.getName() << "] 승리!\n";
    }
    else {
        cout << "매직 몬스터 [" << magicGoblin.getName() << "] 승리!\n";
    }

    return 0;
}