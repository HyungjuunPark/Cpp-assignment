#include <iostream>
using namespace std;

// �ּҸ� ��ȯ�ϴ� �⺻ ����
void Swap(int*& p1, int*& p2) {
    int* tmp = p1;
    p1 = p2;
    p2 = tmp;
}

// nullptr ���� + �ּ� ��ȯ�ϴ� �����ε� ����
void Swap(int*& p1, int*& p2, int fallback) {
    if (p1 == nullptr) {
        p1 = new int(fallback);
    }
    if (p2 == nullptr) {
        p2 = new int(fallback);
    }
    // ���Ŀ��� �� ������ ��� ��ȿ�ϹǷ� �ּ� ��ȯ
    int* tmp = p1;
    p1 = p2;
    p2 = tmp;
}

// ��ƿ: ������ ���� ��� (���� �ּ�)
void PrintPtr(const char* name, int* p) {
    if (p == nullptr) {
        cout << name << " = null\n";
    }
    else {
        cout << name << " = " << *p << " (addr=" << static_cast<const void*>(p) << ")\n";
    }
}

int main() {
    // �ʱ� ����
    int* p1 = nullptr;
    int* p2 = new int(50);

    cout << "--- Initial ---\n";
    PrintPtr("p1", p1);
    PrintPtr("p2", p2);
    cout << '\n';

    // (A) nullptr ���� + �ּ� ��ȯ
    cout << "--- Swap(p1, p2, 999) ---\n";
    cout << "Before: ";
    if (p1) cout << "p1 = " << *p1; else cout << "p1 = null";
    cout << ", ";
    if (p2) cout << "p2 = " << *p2 << '\n'; else cout << "p2 = null\n";

    Swap(p1, p2, 999); // �ʿ�� fallback���� new int(999) �Ҵ� �� �ּ� ��ȯ

    cout << "After : ";
    if (p1) cout << "p1 = " << *p1 << " (addr=" << static_cast<const void*>(p1) << ")"; else cout << "p1 = null";
    cout << ", ";
    if (p2) cout << "p2 = " << *p2 << " (addr=" << static_cast<const void*>(p2) << ")\n\n"; else cout << "p2 = null\n\n";

    // (B) �ּҸ� ��ȯ
    cout << "--- Swap(p1, p2) ---\n";
    cout << "Before: ";
    if (p1) cout << "p1 = " << *p1 << " (addr=" << static_cast<const void*>(p1) << ")"; else cout << "p1 = null";
    cout << ", ";
    if (p2) cout << "p2 = " << *p2 << " (addr=" << static_cast<const void*>(p2) << ")\n"; else cout << "p2 = null\n";

    Swap(p1, p2); // �ּҸ� ��ȯ

    cout << "After : ";
    if (p1) cout << "p1 = " << *p1 << " (addr=" << static_cast<const void*>(p1) << ")"; else cout << "p1 = null";
    cout << ", ";
    if (p2) cout << "p2 = " << *p2 << " (addr=" << static_cast<const void*>(p2) << ")\n\n"; else cout << "p2 = null\n\n";

    // �޸� ����(ȣ���� å��)
    cout << "--- Cleanup ---\n";
    delete p1; p1 = nullptr;
    delete p2; p2 = nullptr;
    cout << "delete p1, delete p2 ���� �Ϸ�\n";

    return 0;
}
