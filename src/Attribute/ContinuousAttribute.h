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
    [[nodiscard]] double getValue() const;
    [[nodiscard]] int continuousAttributeSize() const override;
    [[nodiscard]] vector<double> continuousAttributes() const override;
    void setValue(double _value);
    [[nodiscard]] string to_string() const override;
    [[nodiscard]] bool isDiscrete() const override {return false;}
    [[nodiscard]] bool isContinuous() const override {return true;};
    [[nodiscard]] bool isDiscreteIndexed() const override {return false;};
    [[nodiscard]] bool isBinary() const override {return false;};
};


#endif //CLASSIFICATION_CONTINUOUSATTRIBUTE_H
