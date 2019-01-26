//
// Created by Olcay Taner Yıldız on 26.01.2019.
//

#ifndef CLASSIFICATION_COMPOSITEINSTANCE_H
#define CLASSIFICATION_COMPOSITEINSTANCE_H


#include "Instance.h"

class CompositeInstance : public Instance {
private:
    vector<string> possibleClassLabels;
public:
    CompositeInstance(string classLabel);
    CompositeInstance(string classLabel, vector<Attribute*> attributes);
    CompositeInstance(vector<string> possibleLabels);
    CompositeInstance(string classLabel, vector<Attribute*> attributes, vector<string> possibleClassLabels);
    vector<string> getPossibleClassLabels();
    void setPossibleClassLabels(vector<string> possibleClassLabels);
    string to_string();
};


#endif //CLASSIFICATION_COMPOSITEINSTANCE_H
