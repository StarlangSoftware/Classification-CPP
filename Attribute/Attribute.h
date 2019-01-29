//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#ifndef CLASSIFICATION_ATTRIBUTE_H
#define CLASSIFICATION_ATTRIBUTE_H

#include <vector>
using namespace std;

class Attribute {
public:
    virtual int continuousAttributeSize() = 0;
    virtual vector<double> continuousAttributes() = 0;
    virtual string to_string() = 0;
    virtual bool isDiscrete() = 0;
    virtual bool isContinuous() = 0;
    virtual bool isDiscreteIndexed() = 0;
    virtual bool isBinary() = 0;
};


#endif //CLASSIFICATION_ATTRIBUTE_H
