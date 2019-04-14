//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#ifndef CLASSIFICATION_INSTANCE_H
#define CLASSIFICATION_INSTANCE_H
#include <string>
#include <vector>
#include <Vector.h>
#include "../Attribute/Attribute.h"
#include "../FeatureSelection/FeatureSubSet.h"
#include "../Model/Svm/NodeList.h"

using namespace std;

class Instance {
private:
    string classLabel;
    vector<Attribute*> attributes;
public:
    Instance(string classLabel, vector<Attribute*> attributes);
    explicit Instance(string classLabel);
    ~Instance();
    void addAttribute(string value);
    void addAttribute(double value);
    void addAttribute(Attribute* attribute);
    void addVectorAttribute(Vector vector);
    void removeAttribute(int index);
    void removeAllAttributes();
    Attribute* getAttribute(int index);
    int attributeSize();
    int continuousAttributeSize();
    vector<double> continuousAttributes();
    string getClassLabel();
    virtual vector<string> getPossibleClassLabels();
    virtual string to_string();
    Vector toVector();
    NodeList toNodeList();
    Instance* getSubSetOfFeatures(FeatureSubSet featureSubSet);
    void serialize(ostream &outputFile);
    virtual bool isComposite(){return false;};
    bool operator<(const Instance &anotherInstance) const{
        return (classLabel < anotherInstance.classLabel);
    }
};


#endif //CLASSIFICATION_INSTANCE_H
