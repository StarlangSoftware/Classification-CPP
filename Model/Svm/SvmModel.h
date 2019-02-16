//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#ifndef CLASSIFICATION_SVMMODEL_H
#define CLASSIFICATION_SVMMODEL_H
#include "../ValidatedModel.h"
#include "../../Parameter/SvmParameter.h"
#include "Problem.h"
#include "SolutionInfo.h"

class SvmModel : public ValidatedModel{
private:
    DiscreteDistribution classDistribution;
    vector<double> rho;
    vector<int> numberOfSupportVectors;
    vector<NodeList> supportVectors;
    vector<vector<double>> supportVectorCoefficients;
    SvmParameter* parameter;
    int numberOfClasses, numberOfProblems;
    vector<int> groupClasses();
    SolutionInfo solveSingle(Problem problem);
    vector<double> predictValues(NodeList x);
public:
    SvmModel(InstanceList& trainSet, SvmParameter* parameter);
    string predict(Instance* instance) override;
};


#endif //CLASSIFICATION_SVMMODEL_H
