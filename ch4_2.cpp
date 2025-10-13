#include <iostream>

using namespace std;

// =======================================================
// I. 전역 상수 정의 (main 함수의 switch 문에 사용)
// =======================================================
enum MenuChoice {
    MAKE = 1,
    BORROW = 2,
    RETURN = 3,
    INQUIRE = 4,
    EXIT = 5
};

// =======================================================
// II. Book 클래스 정의 (메모리 관리 및 깊은 복사 포함)
// =======================================================

class Book {
private:
    int bookID;
    char* title;
    int stock;

public:
    // 생성자: 깊은 복사 로직 포함 (strlen, strcpy 없이 직접 구현)
    Book(int ID, const char* bookTitle, int initialStock) {
        bookID = ID;
        stock = initialStock;

        // strlen 대체: 길이 계산
        int len = 0;
        while (bookTitle[len] != '\0') {
            len++;
        }

        // 메모리 동적 할당 및 strcpy 대체: 깊은 복사
        title = new char[len + 1];
        int i = 0;
        while (bookTitle[i] != '\0') {
            title[i] = bookTitle[i];
            i++;
        }
        title[i] = '\0';
    }

    // 소멸자: 메모리 해제
    ~Book() {
        delete[] title;
    }

    // 복사 생성자: 깊은 복사 방지
    Book(const Book& other)
        : bookID(other.bookID), stock(other.stock) {

        int len = 0;
        while (other.title[len] != '\0') { len++; }

        title = new char[len + 1];
        int i = 0;
        while (other.title[i] != '\0') { title[i] = other.title[i]; i++; }
        title[i] = '\0';
    }

    // 멤버 함수
    int GetBookID() const {
        return bookID;
    }

    void BorrowBook() {
        if (stock >= 1) {
            stock--;
            cout << "'" << title << "' 도서를 대여했습니다.\n";
        }
        else {
            cout << "재고가 부족하여 대여할 수 없습니다.\n";
        }
    }

    void ReturnBook() {
        stock++;
        cout << "'" << title << "' 도서를 반납했습니다.\n";
    }

    void ShowBookInfo() const {
        cout << "--- 도서 정보 ---";
        cout << "\n도서 번호 : " << bookID;
        cout << "\n제		목 : " << title;
        cout << "\n재고 수량 : " << stock << '\n';
    }
};

// =======================================================
// III. 전역 공간 변수 선언
// =======================================================

Book* bookArr[100]; // Book 객체 포인터를 저장할 배열 (최대 100권)
int bookCount = 0;  // 현재 등록된 책의 수

// =======================================================
// IV. 전역 함수 구현
// =======================================================

// o ShowMenu()
void ShowMenu() {
    cout << "\n--------------------------------------\n";
    cout << "  [도서 관리 시스템] \n";
    cout << "  1. 신규 도서 등록\n";
    cout << "  2. 도서 대여\n";
    cout << "  3. 도서 반납\n";
    cout << "  4. 전체 도서 조회\n";
    cout << "  5. 종료\n";
    cout << "--------------------------------------\n";
}

// 헬퍼 함수: ID로 Book 객체 포인터를 찾아 반환
Book* FindBookByID(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (bookArr[i]->GetBookID() == id) {
            return bookArr[i];
        }
    }
    return nullptr; // 찾지 못하면 nullptr 반환
}

// o AddNewBook()
void AddNewBook() {
    if (bookCount >= 100) {
        cout << "더 이상 도서를 등록할 수 없습니다. (최대 100권)\n";
        return;
    }

    int bookID;
    char title[50];
    int stock;

    cout << "[신규 도서 등록]\n";
    cout << "도서 ID: ";
    if (!(cin >> bookID)) return; // 입력 오류 처리

    // 안전한 문자열 입력을 위해 버퍼 비우고 getline 사용
    cin.ignore();
    cout << "제	목: ";
    cin.getline(title, 50);

    cout << "재고 수량: ";
    if (!(cin >> stock)) return; // 입력 오류 처리

    // new 키워드를 사용해 Book 객체를 동적 할당하고 배열에 포인터 저장
    bookArr[bookCount++] = new Book(bookID, title, stock);

    cout << "## 등록이 완료되었습니다. (현재 " << bookCount << "권 등록) ##\n";
}

// o BorrowBook()
void BorrowBook() {
    int id;
    cout << "[도서 대여]\n";
    cout << "대여할 도서 ID: ";
    if (!(cin >> id)) return; // 입력 오류 처리

    Book* bookToBorrow = FindBookByID(id);

    if (bookToBorrow) {
        bookToBorrow->BorrowBook();
    }
    else {
        cout << "유효하지 않은 도서 ID입니다.\n";
    }
}

// o ReturnBook()
void ReturnBook() {
    int id;
    cout << "[도서 반납]\n";
    cout << "반납할 도서 ID: ";
    if (!(cin >> id)) return; // 입력 오류 처리

    Book* bookToReturn = FindBookByID(id);

    if (bookToReturn) {
        bookToReturn->ReturnBook();
    }
    else {
        cout << "유효하지 않은 도서 ID입니다.\n";
    }
}

// o ShowAllBookInfo()
void ShowAllBookInfo() {
    cout << "\n==== 전체 도서 목록 (" << bookCount << "권) ====\n";
    if (bookCount == 0) {
        cout << "등록된 도서가 없습니다.\n";
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        bookArr[i]->ShowBookInfo();
    }
    cout << "======================================\n";
}

// =======================================================
// V. main 함수 (요청된 코드를 그대로 사용)
// =======================================================

int main() {
    Book oop_book(101, "C++ Programming", 5); // 이 객체는 시스템 관리를 벗어납니다.

    int choice;

    while (true) {
        ShowMenu();
        cout << "선택: ";
        if (!(cin >> choice)) {
            // 입력 오류 발생 시 (예: 문자를 입력했을 때) 처리
            cin.clear();
            cin.ignore(100, '\n');
            cout << "잘못된 입력입니다. 숫자를 입력하세요.\n";
            continue;
        }
        cout << '\n';

        switch (choice) {
        case MAKE:
            AddNewBook();
            break;
        case BORROW:
            BorrowBook();
            break;
        case RETURN:
            ReturnBook();
            break;
        case INQUIRE:
            ShowAllBookInfo();
            break;
        case EXIT:
            // 프로그램 종료 시 동적 할당된 모든 Book 객체 메모리 해제
            for (int i = 0; i < bookCount; i++) {
                if (bookArr[i] != nullptr) {
                    delete bookArr[i];
                }
            }
            // oop_book은 스택에 할당되었으므로 자동 해제됩니다.
            return 0;
        default:
            cout << "잘못된 선택입니다.\n";
        }
    }
    return 0; // 이 코드는 EXIT 케이스에서 이미 반환되므로 도달하지 않습니다.
}
