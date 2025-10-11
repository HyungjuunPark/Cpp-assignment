#include <iostream>

using namespace std;

// =======================================================
// I. ���� ��� ���� (main �Լ��� switch ���� ���)
// =======================================================
enum MenuChoice {
    MAKE = 1,
    BORROW = 2,
    RETURN = 3,
    INQUIRE = 4,
    EXIT = 5
};

// =======================================================
// II. Book Ŭ���� ���� (�޸� ���� �� ���� ���� ����)
// =======================================================

class Book {
private:
    int bookID;
    char* title;
    int stock;

public:
    // ������: ���� ���� ���� ���� (strlen, strcpy ���� ���� ����)
    Book(int ID, const char* bookTitle, int initialStock) {
        bookID = ID;
        stock = initialStock;

        // strlen ��ü: ���� ���
        int len = 0;
        while (bookTitle[len] != '\0') {
            len++;
        }

        // �޸� ���� �Ҵ� �� strcpy ��ü: ���� ����
        title = new char[len + 1];
        int i = 0;
        while (bookTitle[i] != '\0') {
            title[i] = bookTitle[i];
            i++;
        }
        title[i] = '\0';
    }

    // �Ҹ���: �޸� ����
    ~Book() {
        delete[] title;
    }

    // ���� ������: ���� ���� ����
    Book(const Book& other)
        : bookID(other.bookID), stock(other.stock) {

        int len = 0;
        while (other.title[len] != '\0') { len++; }

        title = new char[len + 1];
        int i = 0;
        while (other.title[i] != '\0') { title[i] = other.title[i]; i++; }
        title[i] = '\0';
    }

    // ��� �Լ�
    int GetBookID() const {
        return bookID;
    }

    void BorrowBook() {
        if (stock >= 1) {
            stock--;
            cout << "'" << title << "' ������ �뿩�߽��ϴ�.\n";
        }
        else {
            cout << "��� �����Ͽ� �뿩�� �� �����ϴ�.\n";
        }
    }

    void ReturnBook() {
        stock++;
        cout << "'" << title << "' ������ �ݳ��߽��ϴ�.\n";
    }

    void ShowBookInfo() const {
        cout << "--- ���� ���� ---";
        cout << "\n���� ��ȣ : " << bookID;
        cout << "\n��		�� : " << title;
        cout << "\n��� ���� : " << stock << '\n';
    }
};

// =======================================================
// III. ���� ���� ���� ����
// =======================================================

Book* bookArr[100]; // Book ��ü �����͸� ������ �迭 (�ִ� 100��)
int bookCount = 0;  // ���� ��ϵ� å�� ��

// =======================================================
// IV. ���� �Լ� ����
// =======================================================

// o ShowMenu()
void ShowMenu() {
    cout << "\n--------------------------------------\n";
    cout << "  [���� ���� �ý���] \n";
    cout << "  1. �ű� ���� ���\n";
    cout << "  2. ���� �뿩\n";
    cout << "  3. ���� �ݳ�\n";
    cout << "  4. ��ü ���� ��ȸ\n";
    cout << "  5. ����\n";
    cout << "--------------------------------------\n";
}

// ���� �Լ�: ID�� Book ��ü �����͸� ã�� ��ȯ
Book* FindBookByID(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (bookArr[i]->GetBookID() == id) {
            return bookArr[i];
        }
    }
    return nullptr; // ã�� ���ϸ� nullptr ��ȯ
}

// o AddNewBook()
void AddNewBook() {
    if (bookCount >= 100) {
        cout << "�� �̻� ������ ����� �� �����ϴ�. (�ִ� 100��)\n";
        return;
    }

    int bookID;
    char title[50];
    int stock;

    cout << "[�ű� ���� ���]\n";
    cout << "���� ID: ";
    if (!(cin >> bookID)) return; // �Է� ���� ó��

    // ������ ���ڿ� �Է��� ���� ���� ���� getline ���
    cin.ignore();
    cout << "��	��: ";
    cin.getline(title, 50);

    cout << "��� ����: ";
    if (!(cin >> stock)) return; // �Է� ���� ó��

    // new Ű���带 ����� Book ��ü�� ���� �Ҵ��ϰ� �迭�� ������ ����
    bookArr[bookCount++] = new Book(bookID, title, stock);

    cout << "## ����� �Ϸ�Ǿ����ϴ�. (���� " << bookCount << "�� ���) ##\n";
}

// o BorrowBook()
void BorrowBook() {
    int id;
    cout << "[���� �뿩]\n";
    cout << "�뿩�� ���� ID: ";
    if (!(cin >> id)) return; // �Է� ���� ó��

    Book* bookToBorrow = FindBookByID(id);

    if (bookToBorrow) {
        bookToBorrow->BorrowBook();
    }
    else {
        cout << "��ȿ���� ���� ���� ID�Դϴ�.\n";
    }
}

// o ReturnBook()
void ReturnBook() {
    int id;
    cout << "[���� �ݳ�]\n";
    cout << "�ݳ��� ���� ID: ";
    if (!(cin >> id)) return; // �Է� ���� ó��

    Book* bookToReturn = FindBookByID(id);

    if (bookToReturn) {
        bookToReturn->ReturnBook();
    }
    else {
        cout << "��ȿ���� ���� ���� ID�Դϴ�.\n";
    }
}

// o ShowAllBookInfo()
void ShowAllBookInfo() {
    cout << "\n==== ��ü ���� ��� (" << bookCount << "��) ====\n";
    if (bookCount == 0) {
        cout << "��ϵ� ������ �����ϴ�.\n";
        return;
    }
    for (int i = 0; i < bookCount; i++) {
        bookArr[i]->ShowBookInfo();
    }
    cout << "======================================\n";
}

// =======================================================
// V. main �Լ� (��û�� �ڵ带 �״�� ���)
// =======================================================

int main() {
    Book oop_book(101, "C++ Programming", 5); // �� ��ü�� �ý��� ������ ����ϴ�.

    int choice;

    while (true) {
        ShowMenu();
        cout << "����: ";
        if (!(cin >> choice)) {
            // �Է� ���� �߻� �� (��: ���ڸ� �Է����� ��) ó��
            cin.clear();
            cin.ignore(100, '\n');
            cout << "�߸��� �Է��Դϴ�. ���ڸ� �Է��ϼ���.\n";
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
            // ���α׷� ���� �� ���� �Ҵ�� ��� Book ��ü �޸� ����
            for (int i = 0; i < bookCount; i++) {
                if (bookArr[i] != nullptr) {
                    delete bookArr[i];
                }
            }
            // oop_book�� ���ÿ� �Ҵ�Ǿ����Ƿ� �ڵ� �����˴ϴ�.
            return 0;
        default:
            cout << "�߸��� �����Դϴ�.\n";
        }
    }
    return 0; // �� �ڵ�� EXIT ���̽����� �̹� ��ȯ�ǹǷ� �������� �ʽ��ϴ�.
}