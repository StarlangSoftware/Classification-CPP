//
// Created by Olcay Taner Yıldız on 26.11.2018.
//

#ifndef MATH_VECTORSIZEMISMATCH_H
#define MATH_VECTORSIZEMISMATCH_H
#include <exception>
using namespace std;

class VectorSizeMismatch : public exception{
public:
    const char* what() const noexcept override;
};


#endif //MATH_VECTORSIZEMISMATCH_H
