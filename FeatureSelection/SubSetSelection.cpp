//
// Created by olcay on 13.02.2019.
//
#include <unordered_set>
#include "SubSetSelection.h"

/**
 * A constructor that sets the initial subset with given input.
 *
 * @param initialSubSet {@link FeatureSubSet} input.
 */
SubSetSelection::SubSetSelection(FeatureSubSet& initialSubSet) {
    this->initialSubSet = initialSubSet;
}

/**
 * The forward method starts with having no feature in the model. In each iteration, it keeps adding the features that are not currently listed.
 *
 * @param currentSubSetList ArrayList to add the FeatureSubsets.
 * @param current           FeatureSubset that will be added to currentSubSetList.
 * @param numberOfFeatures  The number of features to add the subset.
 */
void SubSetSelection::forward(vector<FeatureSubSet> currentSubSetList, FeatureSubSet &current, int numberOfFeatures) {
    for (int i = 0; i < numberOfFeatures; i++) {
        if (!current.contains(i)) {
            FeatureSubSet candidate = current.clone();
            candidate.add(i);
            currentSubSetList.push_back(candidate);
        }
    }
}

/**
 * The backward method starts with all the features and removes the least significant feature at each iteration.
 *
 * @param currentSubSetList ArrayList to add the FeatureSubsets.
 * @param current           FeatureSubset that will be added to currentSubSetList
 */
void SubSetSelection::backward(vector<FeatureSubSet> currentSubSetList, FeatureSubSet& current) {
    for (int i = 0; i < current.size(); i++) {
        FeatureSubSet candidate = current.clone();
        candidate.remove(i);
        currentSubSetList.push_back(candidate);
    }
}

/**
 * The execute method takes an {@link Experiment} and a {@link MultipleRun} as inputs. By selecting a candidateList from given
 * Experiment it tries to find a FeatureSubSet that gives best performance.
 *
 * @param multipleRun {@link MultipleRun} type input.
 * @param experiment  {@link Experiment} type input.
 * @return FeatureSubSet that gives best performance.
 */
FeatureSubSet SubSetSelection::execute(MultipleRun *multipleRun, Experiment experiment) {
    unordered_set<FeatureSubSet> processed;
    FeatureSubSet best = initialSubSet;
    processed.emplace(best);
    bool betterFound = true;
    ExperimentPerformance* bestPerformance = nullptr;
    ExperimentPerformance* currentPerformance;
    if (best.size() > 0){
        bestPerformance = multipleRun->execute(experiment.featureSelectedExperiment(best));
    }
    while (betterFound) {
        betterFound = false;
        vector<FeatureSubSet> candidateList = operatorToModify(best, experiment.getDataSet().getDataDefinition().attributeCount());
        for (FeatureSubSet candidateSubSet : candidateList) {
            if (processed.find(candidateSubSet) != processed.end()) {
                if (candidateSubSet.size() > 0){
                    currentPerformance = multipleRun->execute(experiment.featureSelectedExperiment(candidateSubSet));
                    if (bestPerformance == nullptr || currentPerformance->isBetter(bestPerformance)) {
                        best = candidateSubSet;
                        bestPerformance = currentPerformance;
                        betterFound = true;
                    }
                }
                processed.emplace(candidateSubSet);
            }
        }
    }
    return best;
}
