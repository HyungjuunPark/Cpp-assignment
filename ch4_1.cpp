#include <iostream>
using namespace std;

class Book {
private:
	int bookID;
	char* title;
	int stock;

public:
	// ������: strlen, strcpy ���� ���� ���� ����
	Book(int ID, const char* bookTitle, int stock) {
		this->bookID = ID;
		this->stock = stock;

		// 1. ���ڿ� ���� ���� ���
		int len = 0;
		while (bookTitle[len] != '\0') {
			len++;
		}

		// 2. �� �޸� ���� �Ҵ� (�� ���ڸ� �����Ͽ� len + 1)
		this->title = new char[len + 1];

		// 3. ���ڿ� ���� ���� ���� (���� ����)
		int i = 0;
		while (i <= len) { // �� ���ڱ��� �����ϱ� ���� <= len
			this->title[i] = bookTitle[i];
			i++;
		}
	}

	// �Ҹ���: �� �޸� ����
	~Book() {
		delete[] title;
	}

	int GetBookID() const {
		return bookID;
	}

	void BorrowBook() {
		if (stock >= 1) {
			cout << "'" << title << "' ������ �뿩�߽��ϴ�.\n";
			stock--;
		}
		else
			cout << "��� �����Ͽ� �뿩�� �� �����ϴ�.\n";
	}

	void ReturnBook() {
		stock++;
	}

	void ShowBookInfo() const {
		cout << "--- ���� ���� ---\n";
		cout << "���� ��ȣ: " << bookID << '\n';
		cout << "��	��: " << title << '\n'; // �ùٸ��� ��µ�
		cout << "��� ����: " << stock << "��\n";
	}
};

int main() {
	// ��� ���ڿ� ���ͷ��� �����ϰ� ����
	Book oop_book(101, "C++ Programming", 5);
	oop_book.ShowBookInfo();

	oop_book.BorrowBook();
	oop_book.BorrowBook();
	cout << "\n## 2�� �뿩 �� ##" << '\n';
	oop_book.ShowBookInfo();

	oop_book.ReturnBook();
	cout << "\n## 1�� �ݳ� �� ##" << '\n';
	oop_book.ShowBookInfo();

	return 0;
}