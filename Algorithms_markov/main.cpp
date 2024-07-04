#include "MyString.h"
#include "MarkovAlgorithm.h"
#include <gtest/gtest.h>

using namespace std;

TEST(MyStringTest, CharConstructor) {
    MyString s("test");
    EXPECT_EQ(s.size(), 4);
    EXPECT_EQ(s[0], 't');
    EXPECT_EQ(s[1], 'e');
    EXPECT_EQ(s[2], 's');
    EXPECT_EQ(s[3], 't');
}

TEST(MyStringTest, CopyConstructor) {
    MyString s1("test");
    MyString s2(s1);
    EXPECT_EQ(s2.size(), 4);
    EXPECT_EQ(s2[0], 't');
    EXPECT_EQ(s2[1], 'e');
    EXPECT_EQ(s2[2], 's');
    EXPECT_EQ(s2[3], 't');
}

TEST(MyStringTest, AssignmentOperator) {
    MyString s1("test");
    MyString s2 = s1;
    EXPECT_EQ(s2.size(), 4);
    EXPECT_EQ(s2[0], 't');
    EXPECT_EQ(s2[1], 'e');
    EXPECT_EQ(s2[2], 's');
    EXPECT_EQ(s2[3], 't');
}

TEST(MyStringTest, Find) {
    MyString s("hello");
    EXPECT_EQ(s.find("ell"), 1);
    EXPECT_EQ(s.find("world"), MyString::npos);
}

TEST(MyStringTest, Replace) {
    MyString s("hello");
    s.replace(2, 2, "p!");
    EXPECT_EQ(s.size(), 5);
    EXPECT_EQ(s[0], 'h');
    EXPECT_EQ(s[1], 'e');
    EXPECT_EQ(s[2], 'p');
    EXPECT_EQ(s[3], '!');
    EXPECT_EQ(s[4], 'o');
}

TEST(MarkovAlgorithmTest, Apply) {
    MarkovAlgorithm alg;
    alg.addRule("hello", "world");

    MyString s("hello");
    alg.apply(s);
    EXPECT_EQ(s.size(), 5);
    EXPECT_EQ(s[0], 'w');
    EXPECT_EQ(s[1], 'o');
    EXPECT_EQ(s[2], 'r');
    EXPECT_EQ(s[3], 'l');
    EXPECT_EQ(s[4], 'd');
}

TEST(MarkovAlgorithmTest, ApplyWithLock) {
    MarkovAlgorithm alg;
    alg.addRule("a", "b");
    alg.addRule("|", "0", true);

    MyString s("a|a");
    MyString lock("|");
    alg.applyWithLock(s, lock);
    EXPECT_EQ(s.size(), 3);
    EXPECT_EQ(s[0], 'a');
    EXPECT_EQ(s[1], '0');
    EXPECT_EQ(s[2], 'a');
}

int main() {
    MarkovAlgorithm algorithm;
    MarkovAlgorithm algorithm2;

    algorithm.addRule("sad", "happy");
    algorithm.addRule("CocaCola", "Pepsi", true);

    MyString str("sad CocaCola");

    cout << "Initial string: ";
    str.print();

    algorithm.apply(str);

    cout << "String after applying Markov algorithm: ";
    str.print();
    cout << "-------------------------------" << endl;

    algorithm2.addRule("a", "b");
    algorithm2.addRule("c", "d");
    algorithm2.addRule("|", "0", true);
    algorithm2.addRule("r", "d");

    MyString input("ab|c|ra");
    cout << "Initial string: ";
    input.print();
    algorithm2.applyWithLock(input, "|");
    cout << "String after applying Markov algorithm with lock: ";
    input.print();

    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
