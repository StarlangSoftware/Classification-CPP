//
// Created by Olcay Taner Yıldız on 25.01.2019.
//

#ifndef CLASSIFICATION_INSTANCE_H
#define CLASSIFICATION_INSTANCE_H
#include <string>
#include <vector>
#include "Vector.h"
#include "../Attribute/Attribute.h"
#include "../FeatureSelection/FeatureSubSet.h"
#include "../Model/Svm/NodeList.h"

using namespace std;

class Instance {
private:
    string classLabel;
    vector<Attribute*> attributes;
public:
    Instance(const string& classLabel, const vector<Attribute*>& attributes);
    explicit Instance(const string& classLabel);
    ~Instance();
    void addAttribute(const string& value);
    void addAttribute(double value);
    void addAttribute(Attribute* attribute);
    void addVectorAttribute(const Vector& vector);
    void removeAttribute(int index);
    void removeAllAttributes();
    Attribute* getAttribute(int index) const;
    int attributeSize() const;
    int continuousAttributeSize() const;
    vector<double> continuousAttributes() const;
    string getClassLabel() const;
    virtual vector<string> getPossibleClassLabels() const;
    virtual string to_string() const;
    Vector toVector() const;
    NodeList toNodeList() const;
    Instance* getSubSetOfFeatures(const FeatureSubSet& featureSubSet) const;
    void serialize(ostream &outputFile);
    virtual bool isComposite() const{return false;};
    bool operator<(const Instance &anotherInstance) const{
        return (classLabel < anotherInstance.classLabel);
    }
};


#endif //CLASSIFICATION_INSTANCE_H
