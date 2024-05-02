#include <iostream>
#include <map>
#include <string>

#include "Lab4Exmaple.h"
using namespace std;
#include <iostream>
#include <cstring>

class VectorULong {
private:
    unsigned long* data;
    size_t size;
    int state;

public:
    // Конструктор без параметрів
    VectorULong() : size(1), state(0) {
        data = new unsigned long[size]();
    }

    // Конструктор з одним параметром - розмір вектора
    VectorULong(size_t s) : size(s), state(0) {
        data = new unsigned long[size]();
    }

    // Конструктор із двома параметрами - розмір вектора та значення ініціалізації
    VectorULong(size_t s, unsigned long initValue) : size(s), state(0) {
        data = new unsigned long[size]();
        for (size_t i = 0; i < size; ++i) {
            data[i] = initValue;
        }
    }

    // Конструктор копіювання
    VectorULong(const VectorULong& other) : size(other.size), state(other.state) {
        data = new unsigned long[size]();
        memcpy(data, other.data, size * sizeof(unsigned long));
    }

    // Деструктор
    ~VectorULong() {
        delete[] data;
    }

    // Перевантаження операцій
    VectorULong& operator=(const VectorULong& other) {
        if (this != &other) {
            delete[] data;
            size = other.size;
            state = other.state;
            data = new unsigned long[size]();
            memcpy(data, other.data, size * sizeof(unsigned long));
        }
        return *this;
    }

    // Оператор присвоєння зі скаляром
    VectorULong& operator=(unsigned long scalar) {
        for (size_t i = 0; i < size; ++i) {
            data[i] = scalar;
        }
        return *this;
    }

    // Оператор +=
    VectorULong& operator+=(const VectorULong& other) {
        for (size_t i = 0; i < size; ++i) {
            data[i] += other.data[i];
        }
        return *this;
    }

    // Оператор -=
    VectorULong& operator-=(const VectorULong& other) {
        for (size_t i = 0; i < size; ++i) {
            data[i] -= other.data[i];
        }
        return *this;
    }

    // Оператор *= зі скаляром
    VectorULong& operator*=(unsigned long scalar) {
        for (size_t i = 0; i < size; ++i) {
            data[i] *= scalar;
        }
        return *this;
    }

    // Оператор /= зі скаляром
    VectorULong& operator/=(unsigned long scalar) {
        if (scalar != 0) {
            for (size_t i = 0; i < size; ++i) {
                data[i] /= scalar;
            }
        }
        return *this;
    }

    // Оператор %=
    VectorULong& operator%=(unsigned long scalar) {
        if (scalar != 0) {
            for (size_t i = 0; i < size; ++i) {
                data[i] %= scalar;
            }
        }
        return *this;
    }

    // Оператор [] для звернення до елементів за індексом
    unsigned long& operator[](size_t index) {
        if (index >= size) {
            state = -1; // Помилка: виходить за межі масиву
            return data[size - 1]; // Повертаємо останній елемент
        }
        return data[index];
    }

    // Перевантаження оператора виведення в потік <<
    friend ostream& operator<<(ostream& out, const VectorULong& vec) {
        out << "[ ";
        for (size_t i = 0; i < vec.size; ++i) {
            out << vec.data[i] << " ";
        }
        out << "]";
        return out;
    }

    // Перевантаження оператора введення з потоку >>
    friend istream& operator>>(istream& in, VectorULong& vec) {
        for (size_t i = 0; i < vec.size; ++i) {
            in >> vec.data[i];
        }
        return in;
    }

    // Перевантаження оператора порівняння ==
    bool operator==(const VectorULong& other) const {
        if (size != other.size) {
            return false;
        }
        for (size_t i = 0; i < size; ++i) {
            if (data[i] != other.data[i]) {
                return false;
            }
        }
        return true;
    }

    // Перевантаження оператора порівняння !=
    bool operator!=(const VectorULong& other) const {
        return !(*this == other);
    }

    // Перевантаження оператора порівняння <
    bool operator<(const VectorULong& other) const {
        for (size_t i = 0; i < size; ++i) {
            if (data[i] >= other.data[i]) {
                return false;
            }
        }
        return true;
    }

    // Перевантаження оператора порівняння <=
    bool operator<=(const VectorULong& other) const {
        return (*this == other) || (*this < other);
    }

    // Перевантаження оператора порівняння >
    bool operator>(const VectorULong& other) const {
        return !(*this <= other);
    }

    // Перевантаження оператора порівняння >=
    bool operator>=(const VectorULong& other) const {
        return !(*this < other);
    }

    // Перевірка стану
    int getState() const {
        return state;
    }

    // Підрахунок числа об'єктів даного типу
    static int countObjects;

    // Унарний оператор ++
    VectorULong& operator++() {
        for (size_t i = 0; i < size; ++i) {
            ++data[i];
        }
        return *this;
    }

    // Унарний оператор --
    VectorULong& operator--() {
        for (size_t i = 0; i < size; ++i) {
            --data[i];
        }
        return *this;
    }

    // Унарний оператор !
    bool operator!() const {
        return size == 0;
    }

    // Унарний оператор ~
    VectorULong operator~() const {
        VectorULong result(size);
        for (size_t i = 0; i < size; ++i) {
            result.data[i] = ~data[i];
        }
        return result;
    }

    // Унарний оператор -
    VectorULong operator-() const {
        VectorULong result(size);
        for (size_t i = 0; i < size; ++i) {
            // Перетворення на знаковий тип для обчислення від'ємного значення
            long signedData = static_cast<long>(data[i]);
            result.data[i] = -signedData; // Повернення від'ємного значення
        }
        return result;
    }

    // Оператор |=
    VectorULong& operator|=(const VectorULong& other) {
        for (size_t i = 0; i < size; ++i) {
            data[i] |= other.data[i];
        }
        return *this;
    }

    // Оператор ^=
    VectorULong& operator^=(const VectorULong& other) {
        for (size_t i = 0; i < size; ++i) {
            data[i] ^= other.data[i];
        }
        return *this;
    }

    // Оператор &=
    VectorULong& operator&=(const VectorULong& other) {
        for (size_t i = 0; i < size; ++i) {
            data[i] &= other.data[i];
        }
        return *this;
    }

    // Бінарний оператор +
    VectorULong operator+(const VectorULong& other) const {
        VectorULong result(*this);
        result += other;
        return result;
    }

    // Бінарний оператор -
    VectorULong operator-(const VectorULong& other) const {
        VectorULong result(*this);
        result -= other;
        return result;
    }

    // Бінарний оператор *
    VectorULong operator*(unsigned long scalar) const {
        VectorULong result(*this);
        result *= scalar;
        return result;
    }

    // Бінарний оператор /
    VectorULong operator/(unsigned long scalar) const {
        VectorULong result(*this);
        result /= scalar;
        return result;
    }

    // Бінарний оператор %
    VectorULong operator%(unsigned long scalar) const {
        VectorULong result(*this);
        result %= scalar;
        return result;
    }

    // Бінарний оператор |
    VectorULong operator|(const VectorULong& other) const {
        VectorULong result(*this);
        result |= other;
        return result;
    }

    // Бінарний оператор ^
    VectorULong operator^(const VectorULong& other) const {
        VectorULong result(*this);
        result ^= other;
        return result;
    }

    // Бінарний оператор &
    VectorULong operator&(const VectorULong& other) const {
        VectorULong result(*this);
        result &= other;
        return result;
    }
};

int VectorULong::countObjects = 0;

class LibraryCatalog {
private:
    map<int, string> catalog;
    int codeError;

public:
    // Конструктор за замовчуванням
    LibraryCatalog() : codeError(0) {}

    // Функція додавання книги до каталогу
    void addBook(int inventoryNumber, const string& title) {
        catalog[inventoryNumber] = title;
    }

    // Перевантаження оператора індексації []
    string& operator[](int inventoryNumber) {
        if (catalog.find(inventoryNumber) == catalog.end()) {
            codeError = -1; // Помилка: книга з таким інвентарним номером відсутня
            // Повертаємо порожню назву книги
            static string emptyString;
            return emptyString;
        }
        return catalog[inventoryNumber];
    }

    // Функція для отримання коду помилки
    int getErrorCode() const {
        return codeError;
    }

    // Функція для скидання коду помилки
    void resetErrorCode() {
        codeError = 0;
    }

    // Перевантаження дружніх операцій введення та виведення
    friend ostream& operator<<(ostream& out, const LibraryCatalog& catalog) {
        for (const auto& pair : catalog.catalog) {
            out << "Inventory Number: " << pair.first << ", Title: " << pair.second << endl;
        }
        return out;
    }

    friend istream& operator>>(istream& in, LibraryCatalog& catalog) {
        int inventoryNumber;
        string title;
        cout << "Enter Inventory Number: ";
        in >> inventoryNumber;
        cout << "Enter Title: ";
        in.ignore(); // Ігноруємо знак нового рядка, залишений після введення inventoryNumber
        getline(in, title);
        catalog.addBook(inventoryNumber, title);
        return in;
    }
};

int main()
{
    cout << " Lab #4  task chain  !\n";

    int task;
    cout << "Enter task" << endl;
    cin >> task;
    switch (task)
    {
    case 1: {
        // Створення об'єктів класу VectorULong
        VectorULong vec1(5, 10); // Розмір 5, всі значення 10
        VectorULong vec2(5, 5);  // Розмір 5, всі значення 5

        // Виведення початкових векторів
        cout << "Initial vectors:\n";
        cout << "Vector 1: " << vec1 << endl;
        cout << "Vector 2: " << vec2 << endl;

        // Перевірка операцій +=
        vec1 += vec2;
        cout << "Vector 1 after += Vector 2: " << vec1 << endl;

        // Перевірка операцій -=
        vec1 -= vec2;
        cout << "Vector 1 after -= Vector 2: " << vec1 << endl;

        // Перевірка операцій *=
        vec1 *= 2;
        cout << "Vector 1 after *= 2: " << vec1 << endl;

        // Перевірка операцій /=
        vec1 /= 2;
        cout << "Vector 1 after /= 2: " << vec1 << endl;

        // Перевірка операцій %=
        vec1 %= 3;
        cout << "Vector 1 after %= 3: " << vec1 << endl;

        // Перевірка операторів +, -, *, /, %, |, ^, &
        VectorULong vec3 = vec1 + vec2;
        cout << "Vector 1 + Vector 2: " << vec3 << endl;


        VectorULong vec5 = vec1 * 3;
        cout << "Vector 1 * 3: " << vec5 << endl;

        VectorULong vec6 = vec1 / 2;
        cout << "Vector 1 / 2: " << vec6 << endl;

        VectorULong vec7 = vec1 % 3;
        cout << "Vector 1 % 3: " << vec7 << endl;

        VectorULong vec8 = vec1 | vec2;
        cout << "Vector 1 | Vector 2: " << vec8 << endl;

        VectorULong vec9 = vec1 ^ vec2;
        cout << "Vector 1 ^ Vector 2: " << vec9 << endl;

        VectorULong vec10 = vec1 & vec2;
        cout << "Vector 1 & Vector 2: " << vec10 << endl;

        // Перевірка операторів порівняння
        cout << "Vector 1 == Vector 2: " << (vec1 == vec2) << endl;
        cout << "Vector 1 != Vector 2: " << (vec1 != vec2) << endl;
        cout << "Vector 1 < Vector 2: " << (vec1 < vec2) << endl;
        cout << "Vector 1 <= Vector 2: " << (vec1 <= vec2) << endl;
        cout << "Vector 1 > Vector 2: " << (vec1 > vec2) << endl;
        cout << "Vector 1 >= Vector 2: " << (vec1 >= vec2) << endl;



        // Перевірка оператора доступу до елементів за індексом
        cout << "Element at index 2 of Vector 1: " << vec1[2] << endl;
    }
    case 2: {
        LibraryCatalog catalog; // Створюємо об'єкт класу LibraryCatalog

        // Додаємо книги до каталогу
        catalog.addBook(101, "The Great Gatsby");
        catalog.addBook(102, "To Kill a Mockingbird");
        catalog.addBook(103, "1984");
        catalog.addBook(104, "Pride and Prejudice");

        // Виводимо каталог на екран
        cout << "Library Catalog:" << endl;
        cout << catalog << endl;

        // Додавання нової книги з консолі
        cout << "Enter details for a new book:" << endl;
        cin >> catalog;

        // Перевіряємо, чи виникла помилка при додаванні книги
        int errorCode = catalog.getErrorCode();
        if (errorCode != 0) {
            cout << "Error: Unable to add the book. Error code: " << errorCode << endl;
            // Скидаємо код помилки
            catalog.resetErrorCode();
        }
        else {
            cout << "Book successfully added to the catalog." << endl;
        }

        // Виводимо оновлений каталог на екран
        cout << "Updated Library Catalog:" << endl;
        cout << catalog << endl;
        break;
    }
    }
}
