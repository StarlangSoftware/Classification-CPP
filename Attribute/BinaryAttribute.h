//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#ifndef CLASSIFICATION_BINARYATTRIBUTE_H
#define CLASSIFICATION_BINARYATTRIBUTE_H
#include "DiscreteAttribute.h"

class BinaryAttribute : public DiscreteAttribute{
public:
    explicit BinaryAttribute(bool value);
    explicit BinaryAttribute(string value);
    bool isDiscrete() override {return false;}
    bool isContinuous() override {return false;};
    bool isDiscreteIndexed() override {return false;};
    bool isBinary() override {return true;};
};


#endif //CLASSIFICATION_BINARYATTRIBUTE_H
