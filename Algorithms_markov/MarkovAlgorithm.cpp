#include "MarkovAlgorithm.h"

using namespace std;

Rule::Rule() : terminating(false) {}

Rule::Rule(const MyString& pat, const MyString& repl, bool term)
    : pattern(pat), replacement(repl), terminating(term) {}

MarkovAlgorithm::MarkovAlgorithm() : rules(nullptr), ruleCount(0), capacity(0) {}

MarkovAlgorithm::~MarkovAlgorithm() {
    delete[] rules;
}

void MarkovAlgorithm::resize() {
    if (capacity > 0) {
        capacity *= 2;
    }
    else {
        capacity = 4;
    }

    Rule* newRules = new Rule[capacity];
    for (size_t i = 0; i < ruleCount; ++i) {
        newRules[i] = rules[i];
    }
    delete[] rules;
    rules = newRules;
}

void MarkovAlgorithm::addRule(const MyString& pattern, const MyString& replacement, bool terminating) {
    if (ruleCount >= capacity) {
        resize();
    }
    rules[ruleCount++] = Rule(pattern, replacement, terminating);
}

void MarkovAlgorithm::apply(MyString& input) {
    bool replaced;
    do {
        replaced = false;
        for (size_t i = 0; i < ruleCount; ++i) {
            Rule& rule = rules[i];
            size_t pos = input.find(rule.pattern);
            if (pos != MyString::npos) {
                input.replace(pos, rule.pattern.size(), rule.replacement);
                replaced = true;
                if (rule.terminating) return;
                break;
            }
        }
    } while (replaced);
}

void MarkovAlgorithm::applyWithLock(MyString& input, const MyString& lock) {
    size_t lockPos = input.find(lock);
    while (lockPos != MyString::npos) {
        for (size_t i = 0; i < ruleCount; ++i) {
            if (input.find(rules[i].pattern, lockPos) == lockPos) {
                input.replace(lockPos, rules[i].pattern.size(), rules[i].replacement);
                if (rules[i].terminating) {
                    return;
                }
                break;
            }
        }
    }
}
