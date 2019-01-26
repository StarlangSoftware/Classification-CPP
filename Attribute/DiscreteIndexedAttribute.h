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
    int continuousAttributeSize();
    vector<double> continuousAttributes();
};


#endif //CLASSIFICATION_DISCRETEINDEXEDATTRIBUTE_H
