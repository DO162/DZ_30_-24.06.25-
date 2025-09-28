#include <iostream>
#include <windows.h>
using namespace std;

class Array {
private:
    int* data;
    int capacity;
    int length;

    void Resize(int newCapacity) {
        int* newData = new int[newCapacity];
        for (int i = 0; i < length; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    // Конструктор
    Array(int initialCapacity = 4) {
        capacity = initialCapacity;
        length = 0;
        data = new int[capacity];
    }

    // Конструктор копіювання
    Array(const Array& other) {
        capacity = other.capacity;
        length = other.length;
        data = new int[capacity];
        for (int i = 0; i < length; i++) data[i] = other.data[i];
    }

    // Оператор присвоєння =
    Array& operator=(const Array& other) {
        if (this == &other) return *this;
        delete[] data;
        capacity = other.capacity;
        length = other.length;
        data = new int[capacity];
        for (int i = 0; i < length; i++) data[i] = other.data[i];
        return *this;
    }

    // Деструктор
    ~Array() {
        delete[] data;
    }

    // Додавання в кінець
    void AddToBack(int value) {
        if (length == capacity) Resize(capacity * 2);
        data[length++] = value;
    }

    // Додавання в початок
    void AddToFront(int value) {
        if (length == capacity) Resize(capacity * 2);
        for (int i = length; i > 0; i--) data[i] = data[i - 1];
        data[0] = value;
        length++;
    }

    // Видалення з кінця
    void RemoveFromBack() {
        if (length > 0) length--;
    }

    // Видалення за значенням
    void RemoveByValue(int value) {
        int j = 0;
        for (int i = 0; i < length; i++) {
            if (data[i] != value) data[j++] = data[i];
        }
        length = j;
    }

    // Очистка
    void Clear() {
        length = 0;
    }

    // Довжина
    int GetLength() const {
        return length;
    }

    // Ємність
    int GetCapacity() const {
        return capacity;
    }

    // Оператор +=
    Array& operator+=(int value) {
        AddToBack(value);
        return *this;
    }

    // Оператор -=
    Array& operator-=(int value) {
        RemoveByValue(value);
        return *this;
    }

    // Оператор ==
    bool operator==(const Array& other) const {
        if (length != other.length) return false;
        for (int i = 0; i < length; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    // Оператор []
    int& operator[](int index) {
        if (index < 0 || index >= length) throw out_of_range("Invalid index");
        return data[index];
    }

    const int& operator[](int index) const {
        if (index < 0 || index >= length) throw out_of_range("Invalid index");
        return data[index];
    }
};

ostream& operator<<(ostream& os, const Array& arr) {
    for (int i = 0; i < arr.GetLength(); i++) {
        os << arr[i] << " ";
    }
    return os;
}

istream& operator>>(istream& is, Array& arr) {
    int value;
    is >> value;
    arr += value;
    return is;
}

int main() {
    SetConsoleOutputCP(1251);
    Array arr;

    arr += 10;
    arr += 20;
    arr.AddToFront(5);
    arr += 30;
    arr -= 20;

    cout << "Масив: " << arr << "\n";
    cout << "Довжина: " << arr.GetLength() << "\n";
    cout << "Ємність: " << arr.GetCapacity() << "\n";

    arr[1] = 99;
    cout << "Після зміни: " << arr << "\n";

    Array arr2 = arr;
    cout << "Копія: " << arr2 << "\n";

    cout << "arr == arr2 ? " << (arr == arr2 ? "Так" : "Ні") << "\n";

    cout << "Введіть число: " << "\n";
    cin >> arr;
    cout << "Після вводу: " << arr << "\n";
}