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
    DiscreteIndexedAttribute(const string& value, int index, int maxIndex);
    int getIndex() const;
    int getMaxIndex() const;
    int continuousAttributeSize() const override;
    vector<double> continuousAttributes() const override;
    bool isDiscrete() const override {return false;}
    bool isContinuous() const override {return false;};
    bool isDiscreteIndexed() const override {return true;};
    bool isBinary() const override {return false;};
};


#endif //CLASSIFICATION_DISCRETEINDEXEDATTRIBUTE_H
