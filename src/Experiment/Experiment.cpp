//
// Created by olcay on 6.02.2019.
//

#include "Experiment.h"

Experiment::Experiment(Classifier *classifier, Parameter *parameter, DataSet &dataSet) {
    this->classifier = classifier;
    this->parameter = parameter;
    this->dataSet = dataSet;
}

Classifier *Experiment::getClassifier() {
    return classifier;
}

Parameter *Experiment::getParameter() {
    return parameter;
}

DataSet Experiment::getDataSet() {
    return dataSet;
}

Experiment Experiment::featureSelectedExperiment(FeatureSubSet featureSubSet) {
    DataSet newDataSet = dataSet.getSubSetOfFeatures(featureSubSet);
    return Experiment(classifier, parameter, newDataSet);
}
