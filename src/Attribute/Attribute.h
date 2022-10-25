//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#ifndef CLASSIFICATION_ATTRIBUTE_H
#define CLASSIFICATION_ATTRIBUTE_H

#include <vector>
using namespace std;

class Attribute {
public:
    virtual int continuousAttributeSize() const = 0;
    virtual vector<double> continuousAttributes() const = 0;
    virtual string to_string() const = 0;
    virtual bool isDiscrete() const = 0;
    virtual bool isContinuous() const = 0;
    virtual bool isDiscreteIndexed() const = 0;
    virtual bool isBinary() const = 0;
};


#endif //CLASSIFICATION_ATTRIBUTE_H
