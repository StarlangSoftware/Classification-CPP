//
// Created by olcay on 6.02.2019.
//

#ifndef CLASSIFICATION_EXPERIMENT_H
#define CLASSIFICATION_EXPERIMENT_H


#include "../Classifier/Classifier.h"
#include "../Parameter/Parameter.h"
#include "../DataSet/DataSet.h"

class Experiment {
private:
    Classifier* classifier;
    Parameter* parameter;
    DataSet dataSet;
public:
    Experiment(Classifier* classifier, Parameter* parameter, DataSet& dataSet);
    Classifier* getClassifier();
    Parameter* getParameter();
    DataSet getDataSet();
};


#endif //CLASSIFICATION_EXPERIMENT_H
