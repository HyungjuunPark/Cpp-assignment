#include <iostream>

using namespace std;

// ↓↓↓↓↓↓ [클래스 구현] ↓↓↓↓↓↓

// 1. Animal (기반 클래스 / 추상 클래스)
class Animal {
public:
    virtual void Speak() const = 0;

    virtual void Fly() const {
        // 기본 Animal 클래스에서는 아무것도 하지 않음.
    }

    virtual ~Animal() {}
};

// 2. Dog (파생 클래스)
class Dog : public Animal {
public:
    void Speak() const override {
        cout << "멍멍! (Woof)\n";
    }
    void Fly() const override {
        // Dog는 날 수 없으므로 비어 둠
    }
    ~Dog() override {
        cout << "Woof...\n";
    }
};

// 3. Cat (파생 클래스)
class Cat : public Animal {
public:
    void Speak() const override {
        cout << "야옹~ (Meow)\n";
    }
    void Fly() const override {
        // Cat은 날 수 없으므로 비어 둠
    }
    ~Cat() override {
        cout << "Meow...\n";
    }
};

// 4. Bird (파생 클래스)
class Bird : public Animal {
public:
    void Speak() const override {
        cout << "짹짹 (Jjip)\n";
    }
    void Fly() const override {
        cout << "새가 하늘을 납니다! (Flying High!)\n";
    }
    ~Bird() override {
        cout << "Jjip...\n";
    }
};

// 5. Zoo (핸들러 클래스)
class Zoo {
private:
    Animal* animalList[50];
    int animalCount;

public:
    Zoo() : animalCount(0) {}

    void AddAnimal(Animal* animal) {
        if (animalCount < 50) {
            animalList[animalCount++] = animal;
        }
        else {
            delete animal;
        }
    }

    void MakeAllSpeak() const {
        cout << "--- 모든 동물 울기 시작! ---\n";
        for (int i = 0; i < animalCount; ++i) {
            animalList[i]->Speak();
        }
        cout << "--------------------------\n\n\n"; 
    }

    void StartAirShow() const {
        cout << "--- 비행 쇼를 시작합니다! ---\n"; 
        for (int i = 0; i < animalCount; ++i) {
            animalList[i]->Fly();
        }
        cout << "--------------------------\n\n"; 
    }

    ~Zoo() {
        cout << "Zoo 문 닫음: 동물들을 집으로 보냅니다...\n";
        for (int i = 0; i < animalCount; ++i) {
            delete animalList[i];
        }
    }
};

// ↑↑↑↑↑↑ [클래스 구현] ↑↑↑↑↑↑

// main 함수는 수정하지 마시오.
int main()
{
    Zoo myZoo;

    myZoo.AddAnimal(new Dog());
    myZoo.AddAnimal(new Cat());
    myZoo.AddAnimal(new Bird());

    myZoo.MakeAllSpeak();

    myZoo.StartAirShow();

    return 0;

}