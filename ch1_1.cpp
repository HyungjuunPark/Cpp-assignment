#include <iostream>
using namespace std;

int main() {
    unsigned int x;
    cout << "입력 : ";
    cin >> x;

    // 자릿수와 자리수 합, 역순 만들기
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

    cout << "자릿수: " << digits << "\n";
    cout << "자리수 합: " << sum << "\n";
    cout << "역순: " << rev << "\n";
    cout << "회문수: " << (rev == x ? "YES" : "NO") << "\n";
    cout << "3의 배수: " << (sum % 3 == 0 ? "YES" : "NO")
        << ", 9의 배수: " << (sum % 9 == 0 ? "YES" : "NO") << "\n";

    return 0;
}