#ifndef MARKOVALGORITHM_H
#define MARKOVALGORITHM_H

#include "MyString.h"

class Rule {
public:
    MyString pattern;
    MyString replacement;
    bool terminating;

    Rule();
    Rule(const MyString& pat, const MyString& repl, bool term = false);
};

class MarkovAlgorithm {
private:
    Rule* rules;
    size_t ruleCount;
    size_t capacity;

    void resize();

public:
    MarkovAlgorithm();
    ~MarkovAlgorithm();

    void addRule(const MyString& pattern, const MyString& replacement, bool terminating = false);
    void apply(MyString& input);
    void applyWithLock(MyString& input, const MyString& lock);
};

#endif 
