#include <iostream>
#include <cstring>

using namespace std;
const int NAME_LEN = 50;

// ============ 문제 1에서 구현한 Book 클래스 (수정 없음) ============
class Book
{
private:
    int bookID;
    char* title;
    int stock;

public:
    Book(int ID, const char* bookTitle, int bookStock) : bookID(ID), stock(bookStock)
    {
        title = new char[strlen(bookTitle) + 1];
        //strcpy(title, bookTitle);
        strcpy_s(title, strlen(bookTitle) + 1, bookTitle);
    }
    ~Book()
    {
        delete[] title;
    }
    int GetBookID() const { return bookID; }
    void BorrowBook()
    {
        if (stock > 0) {
            stock--;
            cout << "'" << title << "' 도서를 대여했습니다." << endl << endl;
        }
        else {
            cout << "재고가 부족하여 '" << title << "' 도서를 대여할 수 없습니다." << endl << endl;
        }
    }
    void ReturnBook()
    {
        stock++;
        cout << "'" << title << "' 도서를 반납했습니다." << endl << endl;
    }
    void ShowBookInfo() const
    {
        cout << "--- 도서 정보 ---" << endl;
        cout << "도서 번호: " << bookID << endl;
        cout << "제    목: " << title << endl;
        cout << "재고 수량: " << stock << "권" << endl;
        cout << "-----------------" << endl << endl;
    }
};

// ============ 전역 변수 및 함수 선언 ============
Book* bookArr[100]; // Book 객체 포인터 배열
int bookCount = 0;  // 등록된 책의 수

void ShowMenu(void);
void AddNewBook(void);
void BorrowBook(void);
void ReturnBook(void);
void ShowAllBookInfo(void);
enum { MAKE = 1, BORROW, RETURN, INQUIRE, EXIT };


// ============ 전역 함수 구현 ============
void ShowMenu(void)
{
    cout << "===== 도서 관리 프로그램 =====" << endl;
    cout << "1. 신규 도서 등록" << endl;
    cout << "2. 도서 대여" << endl;
    cout << "3. 도서 반납" << endl;
    cout << "4. 전체 도서 조회" << endl;
    cout << "5. 프로그램 종료" << endl;
    cout << "==========================" << endl;
}

void AddNewBook(void)
{
    int id, stock;
    char title[NAME_LEN];

    cout << "[신규 도서 등록]" << endl;
    cout << "도서 ID: "; cin >> id;
    cout << "제    목: "; cin >> title;
    cout << "재고 수량: "; cin >> stock;
    cout << endl;

    bookArr[bookCount++] = new Book(id, title, stock);
    cout << "## 등록이 완료되었습니다. ##" << endl << endl;
}

void BorrowBook(void)
{
    int id;
    cout << "[도서 대여]" << endl;
    cout << "대여할 도서의 ID: "; cin >> id;

    for (int i = 0; i < bookCount; i++)
    {
        if (bookArr[i]->GetBookID() == id)
        {
            bookArr[i]->BorrowBook();
            return;
        }
    }
    cout << "유효하지 않은 도서 ID입니다." << endl << endl;
}

void ReturnBook(void)
{
    int id;
    cout << "[도서 반납]" << endl;
    cout << "반납할 도서의 ID: "; cin >> id;

    for (int i = 0; i < bookCount; i++)
    {
        if (bookArr[i]->GetBookID() == id)
        {
            bookArr[i]->ReturnBook();
            return;
        }
    }
    cout << "유효하지 않은 도서 ID입니다." << endl << endl;
}

void ShowAllBookInfo(void)
{
    if (bookCount == 0) {
        cout << "등록된 도서가 없습니다." << endl << endl;
        return;
    }

    cout << "[전체 도서 목록]" << endl;
    for (int i = 0; i < bookCount; i++)
    {
        bookArr[i]->ShowBookInfo();
    }
}

int main(void)
{
    int choice;

    while (true)
    {
        ShowMenu();
        cout << "선택: ";
        cin >> choice;
        cout << endl;

        switch (choice)
        {
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
            // 동적 할당된 모든 Book 객체 메모리 해제
            for (int i = 0; i < bookCount; i++) {
                delete bookArr[i];
            }
            return 0;
        default:
            cout << "잘못된 선택입니다." << endl;
        }
    }
    return 0;
}
