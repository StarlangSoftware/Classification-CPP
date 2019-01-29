//
// Created by Olcay Taner Yıldız on 26.11.2018.
//

#ifndef MATH_MATRIXROWMISMATCH_H
#define MATH_MATRIXROWMISMATCH_H
#include <exception>
using namespace std;

class MatrixRowMismatch : public exception {
public:
    const char* what() const noexcept override;
};


#endif //MATH_MATRIXROWMISMATCH_H
