//
// Created by olcay on 13.02.2019.
//

#ifndef CLASSIFICATION_FEATURESUBSET_H
#define CLASSIFICATION_FEATURESUBSET_H

#include <vector>
using namespace std;

class FeatureSubSet {
private:
    vector<int> indexList;
public:
    explicit FeatureSubSet(vector<int> indexList);
    FeatureSubSet(int numberOfFeatures);
    FeatureSubSet();
    FeatureSubSet clone();
    int size();
    int get(int index);
    bool contains(int featureNo);
    void add(int featureNo);
    void remove(int index);
    bool operator==(const FeatureSubSet &anotherFeatureSubSet){
        return indexList == anotherFeatureSubSet.indexList;
    }
};


#endif //CLASSIFICATION_FEATURESUBSET_H
