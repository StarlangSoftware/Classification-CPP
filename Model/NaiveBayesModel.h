//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_NAIVEBAYESMODEL_H
#define CLASSIFICATION_NAIVEBAYESMODEL_H


#include "GaussianModel.h"

class NaiveBayesModel : public GaussianModel {
private:
    map<string, Vector> classMeans;
    map<string, Vector> classDeviations;
    map<string, vector<DiscreteDistribution>> classAttributeDistributions;
    double logLikelihoodContinuous(string classLabel, Instance* instance);
    double logLikelihoodDiscrete(string classLabel, Instance* instance);
protected:
    double calculateMetric(Instance* instance, string Ci) override;
public:
    NaiveBayesModel(DiscreteDistribution priorDistribution, map<string, Vector> classMeans, map<string, Vector> classDeviations);
    NaiveBayesModel(DiscreteDistribution priorDistribution, map<string, vector<DiscreteDistribution>> classAttributeDistributions);
    void serialize(ostream &outputFile) override;
};


#endif //CLASSIFICATION_NAIVEBAYESMODEL_H
