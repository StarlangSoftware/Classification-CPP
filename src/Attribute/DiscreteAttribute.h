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
    explicit DiscreteAttribute(const string& value);
    explicit DiscreteAttribute(bool value);
    int continuousAttributeSize() const override;
    vector<double> continuousAttributes() const override;
    bool isDiscrete() const override {return true;}
    bool isContinuous() const override {return false;};
    bool isDiscreteIndexed() const override {return false;};
    bool isBinary() const override {return false;};
    string getValue() const;
    string to_string() const override;
};


#endif //CLASSIFICATION_DISCRETEATTRIBUTE_H
