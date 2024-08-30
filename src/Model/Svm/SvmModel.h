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
    vector<int> groupClasses() const;
    SolutionInfo solveSingle(const Problem& problem);
    vector<double> predictValues(const NodeList& x);
public:
    explicit SvmModel(ifstream& inputFile);
    string predict(Instance* instance) override;
    void serialize(ostream &outputFile) override;
    void train(InstanceList& trainSet, Parameter* parameters) override;
};


#endif //CLASSIFICATION_SVMMODEL_H
