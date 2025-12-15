#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib> 
using namespace std;

// 콘솔 화면을 지우는 함수 (OS에 따라 다름)
void clearScreen() {
#ifdef _WIN32
    // Windows
    system("cls"); 
#endif
}

// 달의 위상 그림 (5x11 크기)
const vector<vector<string>> moonPhases = {
    // 1. New Moon (삭)
    // 완전히 어두운 달
   {
        "",
        "",
        "",
        "",
        "",
        "",
        ""
    },
    // 2. Waxing Crescent (초승달)
    // 오른쪽 아래만 밝은 달 (오른쪽이 점점 차오름)
    {
        "      **",
        "       ***",
        "        ***",
        "        ****",
        "        ***",
        "       ***",
        "      **"
    },
    // 3. First Quarter (상현달)
    // 오른쪽 절반이 밝은 달
    {
        "      **",
        "      ****",
        "      *****",
        "      ******",
        "      *****",
        "      ****",
        "      **"
    },
    // 4. Waxing Gibbous (상현망간달)
    // 오른쪽 3/4 이상이 밝은 달
    {
        "      **",
        "     *****",
        "    *******",
        "    ********",
        "    *******",
        "     *****",
        "      **"
    },
    // 5. Full Moon (망)
    // 완전히 밝은 달
    {
        "    ****",
        "  ********",
        " **********",
        "************",
        " **********",
        "  ********",
        "    ****"
    },
    // 6. Waning Gibbous (하현망간달)
    // 왼쪽 3/4 이상이 밝은 달 (왼쪽부터 점점 기울어짐)
    {
        "    **",
        "  *****",
        " *******",
        "********",
        " *******",
        "  *****",
        "    **"
    },
    // 7. Last Quarter (하현달)
    // 왼쪽 절반이 밝은 달
    {
        "    **",
        "  ****",
        " *****",
        "******",
        " *****",
        "  ****",
        "    **"
    },
    // 8. Waning Crescent (그믐달)
    // 왼쪽 아래만 밝은 달
    {
        "    **",
        "  ***",
        " ***",
        "****",
        " ***",
        "  ***",
        "    **"
    },
};

// 달의 위상 이름 (참고용)
const vector<string> phaseNames = {
    "1. New Moon (삭)", "2. Waxing Crescent (초승달)", "3. First Quarter (상현달)", "4. Waxing Gibbous (상현망간달)",
    "5. Full Moon (망)", "6. Waning Gibbous (하현망간달)", "7. Last Quarter (하현달)", "8. Waning Crescent (그믐달)"
};

void displayPhase(const vector<string>& phase, const string& name) {
    clearScreen();
    //cout << "--- " << name << " ---\n"; 
    for (const auto& line : phase) {
        cout << line << "\n";
    }
    cout << flush; 
}

int main() {
    const int delay_ms = 100;
    // 시뮬레이션 루프
    while (true) {
        for (size_t i = 0; i < moonPhases.size(); ++i) {
            displayPhase(moonPhases[i], phaseNames[i]);
            this_thread::sleep_for(chrono::milliseconds(delay_ms));
            //this_thread::sleep_for(chrono::seconds(1));
        }
    }

    return 0;
}