#ifndef MYSTRING_H
#define MYSTRING_H

#include <iostream>
#include <cstring>

class MyString {
private:
    char* data;
    size_t length;

public:
    MyString();
    MyString(const char* str);
    ~MyString();
    MyString(const MyString& other);
    MyString& operator=(const MyString& other);

    size_t size() const;
    const char& operator[](size_t index) const;
    void print() const;
    size_t find(const MyString& str, size_t pos = 0) const;
    MyString& replace(size_t pos, size_t len, const MyString& str);

    operator std::string() const;
    friend std::istream& operator>>(std::istream& is, MyString& str);

    static const size_t npos = -1; 
};

#endif 
