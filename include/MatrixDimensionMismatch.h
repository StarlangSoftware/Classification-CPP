//
// Created by Olcay Taner Yıldız on 26.11.2018.
//

#ifndef MATH_MATRIXDIMENSIONMISMATCH_H
#define MATH_MATRIXDIMENSIONMISMATCH_H
#include <exception>
using namespace std;

class MatrixDimensionMismatch : public exception {
public:
    const char* what() const noexcept override;
};


#endif //MATH_MATRIXDIMENSIONMISMATCH_H
