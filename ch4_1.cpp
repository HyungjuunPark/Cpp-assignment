#include <iostream>
using namespace std;

class Book {
private:
	int bookID;
	char* title;
	int stock;

public:
	// 생성자: strlen, strcpy 없이 깊은 복사 구현
	Book(int bookID, const char* title, int stock) {
		this->bookID = bookID;
		this->stock = stock;

		// 1. 문자열 길이 직접 계산
		int len = 0;
		while (title[len] != '\0') {
			len++;
		}

		// 2. 힙 메모리 동적 할당 (널 문자를 포함하여 len + 1)
		this->title = new char[len + 1];

		// 3. 문자열 내용 직접 복사 (깊은 복사)
		int i = 0;
		while (i <= len) { // 널 문자까지 복사하기 위해 <= len
			this->title[i] = title[i];
			i++;
		}
	}

	// 소멸자: 힙 메모리 해제
	~Book() {
		delete[] title;
	}

	int GetBookID() const {
		return bookID;
	}

	void BorrowBook() {
		if (stock >= 1) {
			cout << "'" << title << "' 도서를 대여했습니다.\n";
			stock--;
		}
		else
			cout << "재고가 부족하여 대여할 수 없습니다.\n";
	}

	void ReturnBook() {
		stock++;
	}

	void ShowBookInfo() const {
		cout << "--- 도서 정보 ---\n";
		cout << "도서 번호: " << bookID << '\n';
		cout << "제	목: " << title << '\n'; // 올바르게 출력됨
		cout << "재고 수량: " << stock << "권\n";
	}
};

int main() {
	// 상수 문자열 리터럴을 안전하게 전달
	Book oop_book(101, "C++ Programming", 5);
	oop_book.ShowBookInfo();

	oop_book.BorrowBook();
	oop_book.BorrowBook();
	cout << "\n## 2권 대여 후 ##" << '\n';
	oop_book.ShowBookInfo();

	oop_book.ReturnBook();
	cout << "\n## 1권 반납 후 ##" << '\n';
	oop_book.ShowBookInfo();

	return 0;
}
