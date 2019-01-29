//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#ifndef CLASSIFICATION_DISCRETEINDEXEDATTRIBUTE_H
#define CLASSIFICATION_DISCRETEINDEXEDATTRIBUTE_H
#include "DiscreteAttribute.h"

class DiscreteIndexedAttribute : public DiscreteAttribute{
private:
    int index;
    int maxIndex;
public:
    DiscreteIndexedAttribute(string value, int index, int maxIndex);
    int getIndex();
    int getMaxIndex();
    int continuousAttributeSize() override;
    vector<double> continuousAttributes() override;
    bool isDiscrete() override {return false;}
    bool isContinuous() override {return false;};
    bool isDiscreteIndexed() override {return true;};
    bool isBinary() override {return false;};
};


#endif //CLASSIFICATION_DISCRETEINDEXEDATTRIBUTE_H
