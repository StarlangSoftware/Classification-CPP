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
    [[nodiscard]] int continuousAttributeSize() const override;
    [[nodiscard]] vector<double> continuousAttributes() const override;
    [[nodiscard]] bool isDiscrete() const override {return true;}
    [[nodiscard]] bool isContinuous() const override {return false;};
    [[nodiscard]] bool isDiscreteIndexed() const override {return false;};
    [[nodiscard]] bool isBinary() const override {return false;};
    [[nodiscard]] string getValue() const;
    [[nodiscard]] string to_string() const override;
};


#endif //CLASSIFICATION_DISCRETEATTRIBUTE_H
