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
    explicit FeatureSubSet(const vector<int>& indexList);
    explicit FeatureSubSet(int numberOfFeatures);
    FeatureSubSet();
    [[nodiscard]] FeatureSubSet clone() const;
    [[nodiscard]] int size() const;
    [[nodiscard]] int get(int index) const;
    [[nodiscard]] bool contains(int featureNo) const;
    void add(int featureNo);
    void remove(int index);
    bool operator==(const FeatureSubSet &anotherFeatureSubSet) const {
        return indexList == anotherFeatureSubSet.indexList;
    }
};


#endif //CLASSIFICATION_FEATURESUBSET_H
