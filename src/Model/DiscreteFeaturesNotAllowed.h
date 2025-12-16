//
// Created by Olcay Taner Yıldız on 17.02.2019.
//

#ifndef CLASSIFICATION_DISCRETEFEATURESNOTALLOWED_H
#define CLASSIFICATION_DISCRETEFEATURESNOTALLOWED_H
#include <exception>
using namespace std;

class DiscreteFeaturesNotAllowed : public exception{
public:
    [[nodiscard]] const char* what() const noexcept override;
};


#endif //CLASSIFICATION_DISCRETEFEATURESNOTALLOWED_H
