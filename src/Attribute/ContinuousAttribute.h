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
    double getValue() const;
    int continuousAttributeSize() const override;
    vector<double> continuousAttributes() const override;
    void setValue(double _value);
    string to_string() const override;
    bool isDiscrete() const override {return false;}
    bool isContinuous() const override {return true;};
    bool isDiscreteIndexed() const override {return false;};
    bool isBinary() const override {return false;};
};


#endif //CLASSIFICATION_CONTINUOUSATTRIBUTE_H
