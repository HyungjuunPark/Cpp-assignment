#include <iostream>
using namespace std;

int main() {
    unsigned int x;
    cout << "�Է� : ";
    cin >> x;

    // �ڸ����� �ڸ��� ��, ���� �����
    unsigned int t = x;
    int digits = 0;
    int sum = 0;
    unsigned int rev = 0;

    while (t > 0) {
        int d = t % 10;
        sum += d;
        rev = rev * 10 + d;
        t /= 10;
        digits++;
    }

    cout << "�ڸ���: " << digits << "\n";
    cout << "�ڸ��� ��: " << sum << "\n";
    cout << "����: " << rev << "\n";
    cout << "ȸ����: " << (rev == x ? "YES" : "NO") << "\n";
    cout << "3�� ���: " << (sum % 3 == 0 ? "YES" : "NO")
        << ", 9�� ���: " << (sum % 9 == 0 ? "YES" : "NO") << "\n";

    return 0;
}