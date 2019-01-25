//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#ifndef CLASSIFICATION_CONTINUOUSATTRIBUTE_H
#define CLASSIFICATION_CONTINUOUSATTRIBUTE_H

#include <string>
#include "Attribute.h"
using namespace std;

class ContinuousAttribute : public Attribute{
private:
    double value;
public:
    ContinuousAttribute(double value);
    double getValue();
    void setValue(double value);
    string to_string();
};


#endif //CLASSIFICATION_CONTINUOUSATTRIBUTE_H
