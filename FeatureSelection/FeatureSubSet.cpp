//
// Created by olcay on 13.02.2019.
//

#include "FeatureSubSet.h"

/**
 * A constructor that sets the indexList {@link vector}.
 *
 * @param indexList A vector consists of integer indices.
 */
FeatureSubSet::FeatureSubSet(vector<int> indexList) {
    this->indexList = move(indexList);
}

/**
 * A constructor that takes number of features as input and initializes indexList with these numbers.
 *
 * @param numberOfFeatures Indicates the indices of indexList.
 */
FeatureSubSet::FeatureSubSet(int numberOfFeatures) {
    for (int i = 0; i < numberOfFeatures; i++) {
        indexList.push_back(i);
    }
}

/**
 * A constructor that creates a new vector for indexList.
 */
FeatureSubSet::FeatureSubSet() {

}

/**
 * The clone method creates a new vector with the elements of indexList and returns it as a new FeatureSubSet.
 *
 * @return A new vector with the elements of indexList and returns it as a new FeatureSubSet.
 */
FeatureSubSet FeatureSubSet::clone() {
    vector<int> newIndexList;
    for (int index : indexList) {
        newIndexList.push_back(index);
    }
    return FeatureSubSet(newIndexList);
}

/**
 * The size method returns the size of the indexList.
 *
 * @return The size of the indexList.
 */
int FeatureSubSet::size() {
    return indexList.size();
}

/**
 * The get method returns the item of indexList at given index.
 *
 * @param index Index of the indexList to be accessed.
 * @return The item of indexList at given index.
 */
int FeatureSubSet::get(int index) {
    return indexList.at(index);
}

/**
 * The contains method returns True, if indexList contains given input number and False otherwise.
 *
 * @param featureNo Feature number that will be checked.
 * @return True, if indexList contains given input number.
 */
bool FeatureSubSet::contains(int featureNo) {
    return find(indexList.begin(), indexList.end(), featureNo) != indexList.end();
}

/**
 * The add method adds given Integer to the indexList.
 *
 * @param featureNo Integer that will be added to indexList.
 */
void FeatureSubSet::add(int featureNo) {
    indexList.push_back(featureNo);
}

/**
 * The remove method removes the item of indexList at the given index.
 *
 * @param index Index of the item that will be removed.
 */
void FeatureSubSet::remove(int index) {
    indexList.erase(indexList.begin() + index);
}
