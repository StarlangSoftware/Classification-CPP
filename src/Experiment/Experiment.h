//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_EXPERIMENT_H
#define CLASSIFICATION_EXPERIMENT_H


#include "../Model/Model.h"
#include "../Parameter/Parameter.h"
#include "../DataSet/DataSet.h"
#include "../FeatureSelection/FeatureSubSet.h"

class Experiment {
private:
    Model* model;
    Parameter* parameter;
    DataSet dataSet;
public:
    Experiment(Model* model, Parameter* parameter, const DataSet& dataSet);
    Model* getModel() const;
    Parameter* getParameter() const;
    DataSet getDataSet() const;
    Experiment featureSelectedExperiment(const FeatureSubSet& featureSubSet);
};


#endif //CLASSIFICATION_EXPERIMENT_H
