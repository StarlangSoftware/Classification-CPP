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
    explicit ContinuousAttribute(double value);
    double getValue();
    int continuousAttributeSize() override;
    vector<double> continuousAttributes() override;
    void setValue(double value);
    string to_string() override;
};


#endif //CLASSIFICATION_CONTINUOUSATTRIBUTE_H
