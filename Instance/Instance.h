//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#ifndef CLASSIFICATION_INSTANCE_H
#define CLASSIFICATION_INSTANCE_H
#include <string>
#include <vector>
#include <Vector.h>
#include "../Attribute/Attribute.h"

using namespace std;

class Instance {
private:
    string classLabel;
    vector<Attribute*> attributes;
public:
    Instance(string classLabel, vector<Attribute*> attributes);
    Instance(string classLabel);
    void addAttribute(string value);
    void addAttribute(double value);
    void addAttribute(Attribute* attribute);
    void addVectorAttribute(Vector vector);
};


#endif //CLASSIFICATION_INSTANCE_H
