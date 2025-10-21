#include <iostream>
#include <cstring>

using namespace std;

class Book
{
private:
    int bookID;
    char* title;
    int stock;

public:
    // 생성자: 이니셜라이저 리스트와 깊은 복사 사용
    Book(int ID, const char* bookTitle, int bookStock) : bookID(ID), stock(bookStock)
    {
        // 제목을 위한 메모리를 동적 할당하고, 문자열을 복사 (깊은 복사)
        title = new char[strlen(bookTitle) + 1];
        //strcpy(title, bookTitle);
        strcpy_s(title, strlen(bookTitle) + 1, bookTitle);        
    }

    // 소멸자: 동적 할당된 메모리 해제
    ~Book()
    {
        delete[] title;
    }

    // 도서 번호를 반환하는 const 멤버 함수
    int GetBookID() const
    {
        return bookID;
    }

    // 도서 대여 함수
    void BorrowBook()
    {
        if (stock > 0)
        {
            stock--;
            cout << "'" << title << "' 도서를 대여했습니다." << endl;
        }
        else
        {
            cout << "재고가 부족하여 '" << title << "' 도서를 대여할 수 없습니다." << endl;
        }
    }

    // 도서 반납 함수
    void ReturnBook()
    {
        stock++;
        cout << "'" << title << "' 도서를 반납했습니다." << endl;
    }

    // 도서 정보를 출력하는 const 멤버 함수
    void ShowBookInfo() const
    {
        cout << "--- 도서 정보 ---" << endl;
        cout << "도서 번호: " << bookID << endl;
        cout << "제    목: " << title << endl;
        cout << "재고 수량: " << stock << "권" << endl;
    }
};

int main() {
    Book oop_book(101, "C++ Programming", 5);
    oop_book.ShowBookInfo();

    oop_book.BorrowBook();
    oop_book.BorrowBook();
    cout << "\n## 2권 대여 후 ##" << endl;
    oop_book.ShowBookInfo();

    oop_book.ReturnBook();
    cout << "\n## 1권 반납 후 ##" << endl;
    oop_book.ShowBookInfo();

    return 0;
}
