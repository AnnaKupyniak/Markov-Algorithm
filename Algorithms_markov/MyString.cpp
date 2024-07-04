#include "MyString.h"

using namespace std;

MyString::MyString() : data(nullptr), length(0) {}

MyString::MyString(const char* str) {
    length = strlen(str);
    data = new char[length + 1];
    strcpy_s(data, length + 1, str);
}

MyString::~MyString() {
    delete[] data;
}

MyString::MyString(const MyString& other) : MyString(other.data) {}

MyString& MyString::operator=(const MyString& other) {
    if (this != &other) {
        delete[] data;
        length = other.length;
        data = new char[length + 1];
        strcpy_s(data, length + 1, other.data);
    }
    return *this;
}

size_t MyString::size() const {
    return length;
}

const char& MyString::operator[](size_t index) const {
    return data[index];
}

void MyString::print() const {
    if (data != nullptr) {
        cout << data << endl;
    }
}

size_t MyString::find(const MyString& str, size_t pos) const {
    if (data && str.data) {
        const char* found = strstr(data + pos, str.data);
        if (found)
            return found - data;
    }
    return npos;
}

MyString& MyString::replace(size_t pos, size_t len, const MyString& str) {
    size_t newLen = length - len + str.length;
    char* newData = new char[newLen + 1];

    strncpy_s(newData, newLen + 1, data, pos);
    strcpy_s(newData + pos, newLen + 1 - pos, str.data);
    strcpy_s(newData + pos + str.length, newLen + 1 - pos - str.length, data + pos + len);

    delete[] data;
    data = newData;
    length = newLen;

    return *this;
}

MyString::operator std::string() const {
    return std::string(data);
}

istream& operator>>(istream& is, MyString& str) {
    std::string temp;
    is >> temp;
    str = temp.c_str();
    return is;
}
