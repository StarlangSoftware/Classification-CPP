//
// Created by olcay on 6.02.2019.
//

#include "Experiment.h"

Experiment::Experiment(Classifier *classifier, Parameter *parameter, const DataSet &dataSet) {
    this->classifier = classifier;
    this->parameter = parameter;
    this->dataSet = dataSet;
}

Classifier *Experiment::getClassifier() const{
    return classifier;
}

Parameter *Experiment::getParameter() const{
    return parameter;
}

DataSet Experiment::getDataSet() const{
    return dataSet;
}

Experiment Experiment::featureSelectedExperiment(const FeatureSubSet& featureSubSet) {
    DataSet newDataSet = dataSet.getSubSetOfFeatures(featureSubSet);
    return Experiment(classifier, parameter, newDataSet);
}
