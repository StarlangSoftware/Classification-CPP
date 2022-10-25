//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#ifndef CLASSIFICATION_BINARYATTRIBUTE_H
#define CLASSIFICATION_BINARYATTRIBUTE_H
#include "DiscreteAttribute.h"

class BinaryAttribute : public DiscreteAttribute{
public:
    explicit BinaryAttribute(bool value);
    explicit BinaryAttribute(const string& value);
    bool isDiscrete() const override {return false;}
    bool isContinuous() const override {return false;};
    bool isDiscreteIndexed() const override {return false;};
    bool isBinary() const override {return true;};
};


#endif //CLASSIFICATION_BINARYATTRIBUTE_H
