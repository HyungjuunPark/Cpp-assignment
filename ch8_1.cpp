#include <iostream>
#include <string> // string 사용을 위해 포함

using namespace std;

// 1. Animal (기반 클래스 / 추상 클래스)
class Animal {
public:
    // 순수 가상 함수: 동물이 소리 내는 기능
    virtual void Speak() const = 0;

    // 가상 소멸자: 파생 클래스 소멸 시 메모리 누수 방지
    virtual ~Animal() {}
};

// 2. Dog (파생 클래스)
class Dog : public Animal {
public:
    void Speak() const override {
        cout << "멍멍! (Woof)" << endl;
    }
    ~Dog() override {
        cout << "Woof..." << endl;
    }
};

// 2. Cat (파생 클래스)
class Cat : public Animal {
public:
    void Speak() const override {
        cout << "야옹~ (Meow)" << endl;
    }
    ~Cat() override {
        cout << "Meow..." << endl;
    }
};

// 2. Bird (파생 클래스)
class Bird : public Animal {
public:
    void Speak() const override {
        cout << "짹짹 (Jjip)" << endl;
    }
    ~Bird() override {
        cout << "Jjip..." << endl;
    }
};

// 3. Zoo (핸들러 클래스)
class Zoo {
private:
    // Animal 객체 포인터 저장 배열 (최대 50)
    Animal* animalList[50];
    // 현재 저장된 동물의 수
    int animalCount;

public:
    // Zoo(): 기본 생성자
    Zoo() : animalCount(0) {}

    // AddAnimal(Animal* animal): 배열에 Animal 포인터 추가
    void AddAnimal(Animal* animal) {
        if (animalCount < 50) {
            animalList[animalCount++] = animal;
        }
        else {
            // 정원 초과 시 처리 (메모리 누수 방지를 위해 삭제 권장)
            delete animal;
            cout << "경고: 동물원 정원 초과!" << endl;
        }
    }

    // MakeAllSpeak() const: 모든 동물이 Speak() 하도록 순회
    void MakeAllSpeak() const {
        cout << "--- 모든 동물 울기 시작! ---" << endl;
        for (int i = 0; i < animalCount; ++i) {
            animalList[i]->Speak(); // 다형성 호출
        }
        cout << "--------------------------" << endl;
    }

    // ~Zoo(): 소멸자. 메시지 출력 후 모든 동적 할당 메모리 해제
    ~Zoo() {
        cout << "Zoo 문 닫음: 동물들을 집으로 보냅니다..." << endl;
        // 배열에 저장된 모든 Animal 객체의 메모리 해제
        for (int i = 0; i < animalCount; ++i) {
            // 가상 소멸자 호출을 통해 Dog, Cat, Bird의 소멸자가 먼저 호출되고 메모리가 해제됨
            delete animalList[i];
        }
    }
};

int main()
{
    // 1. Zoo 클래스 객체 생성
    Zoo myZoo;

    // 2. 동물 객체들을 동적 할당하여 Zoo에 추가
    myZoo.AddAnimal(new Dog());
    myZoo.AddAnimal(new Cat());
    myZoo.AddAnimal(new Bird());

    // 3. Zoo에 있는 모든 동물들이 소리내도록 함 (다형성)
    myZoo.MakeAllSpeak();

    // 4. main 함수 종료 시 myZoo 객체가 소멸되면서
    // 자동으로 모든 동물들의 메모리가 해제되어야 함
    return 0;

}
