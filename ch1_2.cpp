#include <iostream>
using namespace std;

void printCell(int d, int i) {
    int v = d * i;

    cout << " " << d << " x " << i << " = ";
    if (v < 10) cout << " ";
    cout << v;
}

int main() {
    int a, b, order;

    cout << "a : ";
    cin >> a;
    cout << "b : ";
    cin >> b;
    cout << "order(0일시 오름차순 이외는 내림차순) : ";
    cin >> order;

    if (a > b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }

    if (order == 0) {
        for (int i = 1; i <= 9; i++) {
            for (int d = a; d <= b; d++) {
                printCell(d, i);
                if (d != b) cout << "\t";
            }
            cout << "\n";
        }
    }
    else {
        for (int i = 1; i <= 9; i++) {
            for (int d = b; d >= a; d--) {
                printCell(d, i);
                if (d != a) cout << "\t";
            }
            cout << "\n";
        }
    }

    return 0;
}