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
    [[nodiscard]] int getIndex() const;
    [[nodiscard]] int getMaxIndex() const;
    [[nodiscard]] int continuousAttributeSize() const override;
    [[nodiscard]] vector<double> continuousAttributes() const override;
    [[nodiscard]] bool isDiscrete() const override {return false;}
    [[nodiscard]] bool isContinuous() const override {return false;};
    [[nodiscard]] bool isDiscreteIndexed() const override {return true;};
    [[nodiscard]] bool isBinary() const override {return false;};
};


#endif //CLASSIFICATION_DISCRETEINDEXEDATTRIBUTE_H
