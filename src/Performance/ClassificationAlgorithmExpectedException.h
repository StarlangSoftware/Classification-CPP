//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_CLASSIFICATIONALGORITHMEXPECTEDEXCEPTION_H
#define CLASSIFICATION_CLASSIFICATIONALGORITHMEXPECTEDEXCEPTION_H
#include <exception>
using namespace std;

class ClassificationAlgorithmExpectedException : public exception {
public:
    const char* what() const noexcept override;
};


#endif //CLASSIFICATION_CLASSIFICATIONALGORITHMEXPECTEDEXCEPTION_H
