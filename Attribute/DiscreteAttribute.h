//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#ifndef CLASSIFICATION_DISCRETEATTRIBUTE_H
#define CLASSIFICATION_DISCRETEATTRIBUTE_H
#include <string>
#include "Attribute.h"

using namespace std;

class DiscreteAttribute : public Attribute{
private:
    string value = "NULL";
public:
    DiscreteAttribute(string value);
    DiscreteAttribute(bool value);
    int continuousAttributeSize();
    vector<double> continuousAttributes();
    string getValue();
    string to_string();
};


#endif //CLASSIFICATION_DISCRETEATTRIBUTE_H
