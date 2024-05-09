//
// Created by olcay on 6.02.2019.
//

#include "Experiment.h"

/**
 * Constructor for a specific machine learning experiment
 * @param classifier Classifier used in the machine learning experiment
 * @param parameter Parameter(s) of the classifier.
 * @param dataSet DataSet on which the classifier is run.
 */
Experiment::Experiment(Classifier *classifier, Parameter *parameter, const DataSet &dataSet) {
    this->classifier = classifier;
    this->parameter = parameter;
    this->dataSet = dataSet;
}

/**
 * Accessor for the classifier attribute.
 * @return Classifier attribute.
 */
Classifier *Experiment::getClassifier() const{
    return classifier;
}

/**
 * Accessor for the parameter attribute.
 * @return Parameter attribute.
 */
Parameter *Experiment::getParameter() const{
    return parameter;
}

/**
 * Accessor for the dataSet attribute.
 * @return DataSet attribute.
 */
DataSet Experiment::getDataSet() const{
    return dataSet;
}

/**
 * Construct and returns a feature selection experiment.
 * @param featureSubSet Feature subset used in the feature selection experiment
 * @return Experiment constructed
 */
Experiment Experiment::featureSelectedExperiment(const FeatureSubSet& featureSubSet) {
    DataSet newDataSet = dataSet.getSubSetOfFeatures(featureSubSet);
    return Experiment(classifier, parameter, newDataSet);
}
