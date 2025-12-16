//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_STATISTICALTESTNOTAPPLICABLE_H
#define CLASSIFICATION_STATISTICALTESTNOTAPPLICABLE_H
#include <exception>
#include <string>
using namespace std;

class StatisticalTestNotApplicable : public exception{
private:
    string test;
    string reason;
public:
    [[nodiscard]] const char* what() const noexcept override;
    StatisticalTestNotApplicable(string test, string reason);
};


#endif //CLASSIFICATION_STATISTICALTESTNOTAPPLICABLE_H
