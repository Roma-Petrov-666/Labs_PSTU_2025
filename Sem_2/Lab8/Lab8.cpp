#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Book {
    string name;
    string author;
    int year;
    int pages;
};

void print(Book book) {
    cout<<"Название: "<<book.name<<endl;
    cout<<"Автор: "<<book.author<<endl;
    cout<<"Год издания: "<<book.year<<endl;
    cout<<"Количество страниц: "<<book.pages<<endl;
}

void DeletElem(Book*& books, int& size, int index) {
    if (index < 0 || index >= size) {
        return;
    }
	if (size == 0) {return; }

    Book* newBooks = new Book[size-1];

    for (int i=0; i < index; i++) {
        newBooks[i] = books[i];
    }
    for (int i = index+1; i < size; i++) {
        newBooks[i-1] = books[i];
    }

    delete[] books;

    books = newBooks;
    size--;
}

void AddElem(Book*& books, int& size, int index, Book& newBook) {
    if (index < 0 || index > size) {
        return;
    }
    
    Book* newBooks = new Book[size+1];

    for (int i=0; i < index; i++) {
        newBooks[i] = books[i];
    }

    newBooks[index] = newBook;

    for (int i=index; i < size; i++) {
        newBooks[i+1] = books[i];
    }

    delete[] books;
    books = newBooks;
    size++;
}

int FindBookByName(Book* books, int size, string& targetName) {
    for (int i=0; i < size; i++) {
        if (books[i].name == targetName) {
            return i;
        }
    }
    return -1;
}

Book* readBooksFromFile(string& filename, int& count) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла." << endl;
        count=0;
        return nullptr;
    }

    string numbers;
    if (!getline(file, numbers)) {
        cout << "Ошибка чтения количества книг." << endl;
        count = 0;
        return nullptr;
    }
    count = stoi(numbers);

    Book* books = new Book[count];

    string name, author, year, pages;
    for (int i = 0; i < count; i++) {
        if (!getline(file, name) || !getline(file, author) ||
            !getline(file, year) || !getline(file, pages)) {
            cout << "Ошибка чтения данных книги." << endl;
            delete[] books;
            count = 0;
            return nullptr;
        }
        books[i] = { name, author, stoi(year), stoi(pages) };

        if (i != count-1) {
            string space;
            getline(file, space);
        }
    }
    return books;
}

void writeBooksToFile(Book* books, int size, string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Ошибка открытия файла для записи" << endl;
        return;
    }

    file<<size<< endl;
    for (int i=0; i < size; i++) {
        file<<books[i].name<<endl;
        file<<books[i].author<<endl;
        file<<books[i].year<<endl;
        file<<books[i].pages<<endl;
        if (i != size-1) {
            file<<endl;
        }
    }
    file.close();
}

int main() {
    int n=0;
	string filename = "Lab8_data.txt";
    Book* books = readBooksFromFile(filename, n);
    if (books == nullptr || n == 0) {
		cout<<"Ошибка чтения";
        return 1;
    }

    DeletElem(books, n, 0);
    DeletElem(books, n, 0);
    DeletElem(books, n, 0);

    Book elem = { "Мёртвые души", "Николай Гоголь", 1842, 450 };
    string targetName = "Евгений Онегин";

    int pos = FindBookByName(books, n, targetName);
    if (pos == -1) {
        cout << "Ошибка поиска" << endl;
        delete[] books;
        return 2;
    } else {
        AddElem(books, n, pos, elem);
    }

    for (int i=0; i < n; i++) {
        print(books[i]);
        cout<<endl;
    }
	writeBooksToFile(books, n, filename);

    delete[] books;
    return 0;
}
