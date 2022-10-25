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
    explicit CompositeInstance(const string& classLabel);
    CompositeInstance(const string& classLabel, const vector<Attribute*>& attributes);
    explicit CompositeInstance(const vector<string>& possibleLabels);
    CompositeInstance(const string& classLabel, const vector<Attribute*>& attributes, const vector<string>& possibleClassLabels);
    vector<string> getPossibleClassLabels() const override;
    void setPossibleClassLabels(const vector<string>& _possibleClassLabels);
    bool isComposite() const override{return true;};
    string to_string() const override;
};


#endif //CLASSIFICATION_COMPOSITEINSTANCE_H
