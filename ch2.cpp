#include <iostream>
using namespace std;

// 주소만 교환하는 기본 버전
void Swap(int*& p1, int*& p2) {
    int* tmp = p1;
    p1 = p2;
    p2 = tmp;
}

// nullptr 보충 + 주소 교환하는 오버로딩 버전
void Swap(int*& p1, int*& p2, int fallback) {
    if (p1 == nullptr) {
        p1 = new int(fallback);
    }
    if (p2 == nullptr) {
        p2 = new int(fallback);
    }
    // 이후에는 두 포인터 모두 유효하므로 주소 교환
    int* tmp = p1;
    p1 = p2;
    p2 = tmp;
}

// 유틸: 포인터 상태 출력 (값과 주소)
void PrintPtr(const char* name, int* p) {
    if (p == nullptr) {
        cout << name << " = null\n";
    }
    else {
        cout << name << " = " << *p << " (addr=" << static_cast<const void*>(p) << ")\n";
    }
}

int main() {
    // 초기 상태
    int* p1 = nullptr;
    int* p2 = new int(50);

    cout << "--- Initial ---\n";
    PrintPtr("p1", p1);
    PrintPtr("p2", p2);
    cout << '\n';

    // (A) nullptr 보충 + 주소 교환
    cout << "--- Swap(p1, p2, 999) ---\n";
    cout << "Before: ";
    if (p1) cout << "p1 = " << *p1; else cout << "p1 = null";
    cout << ", ";
    if (p2) cout << "p2 = " << *p2 << '\n'; else cout << "p2 = null\n";

    Swap(p1, p2, 999); // 필요시 fallback으로 new int(999) 할당 후 주소 교환

    cout << "After : ";
    if (p1) cout << "p1 = " << *p1 << " (addr=" << static_cast<const void*>(p1) << ")"; else cout << "p1 = null";
    cout << ", ";
    if (p2) cout << "p2 = " << *p2 << " (addr=" << static_cast<const void*>(p2) << ")\n\n"; else cout << "p2 = null\n\n";

    // (B) 주소만 교환
    cout << "--- Swap(p1, p2) ---\n";
    cout << "Before: ";
    if (p1) cout << "p1 = " << *p1 << " (addr=" << static_cast<const void*>(p1) << ")"; else cout << "p1 = null";
    cout << ", ";
    if (p2) cout << "p2 = " << *p2 << " (addr=" << static_cast<const void*>(p2) << ")\n"; else cout << "p2 = null\n";

    Swap(p1, p2); // 주소만 교환

    cout << "After : ";
    if (p1) cout << "p1 = " << *p1 << " (addr=" << static_cast<const void*>(p1) << ")"; else cout << "p1 = null";
    cout << ", ";
    if (p2) cout << "p2 = " << *p2 << " (addr=" << static_cast<const void*>(p2) << ")\n\n"; else cout << "p2 = null\n\n";

    // 메모리 해제(호출자 책임)
    cout << "--- Cleanup ---\n";
    delete p1; p1 = nullptr;
    delete p2; p2 = nullptr;
    cout << "delete p1, delete p2 수행 완료\n";

    return 0;
}
