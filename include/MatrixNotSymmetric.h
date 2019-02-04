//
// Created by Olcay Taner Yıldız on 26.11.2018.
//

#ifndef MATH_MATRIXNOTSYMMETRIC_H
#define MATH_MATRIXNOTSYMMETRIC_H
#include <exception>
using namespace std;

class MatrixNotSymmetric : public exception{
public:
    const char* what() const noexcept override;
};


#endif //MATH_MATRIXNOTSYMMETRIC_H
