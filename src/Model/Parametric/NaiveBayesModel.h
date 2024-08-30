//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_NAIVEBAYESMODEL_H
#define CLASSIFICATION_NAIVEBAYESMODEL_H


#include "GaussianModel.h"
#include "../../InstanceList/Partition.h"

class NaiveBayesModel : public GaussianModel {
private:
    map<string, Vector> classMeans;
    map<string, Vector> classDeviations;
    map<string, vector<DiscreteDistribution>> classAttributeDistributions;
    double logLikelihoodContinuous(const string& classLabel, Instance* instance) const;
    double logLikelihoodDiscrete(const string& classLabel, Instance* instance) const;
    void trainContinuousVersion(const DiscreteDistribution& priorDistribution, const Partition& classLists);
    void trainDiscreteVersion(const DiscreteDistribution& priorDistribution, const Partition& classLists);
protected:
    double calculateMetric(Instance* instance, const string& Ci) const override;
    void load(ifstream& inputFile);
public:
    NaiveBayesModel() = default;
    explicit NaiveBayesModel(ifstream& inputFile);
    NaiveBayesModel(const DiscreteDistribution& priorDistribution, const map<string, Vector>& classMeans, const map<string, Vector>& classDeviations);
    NaiveBayesModel(const DiscreteDistribution& priorDistribution, const map<string, vector<DiscreteDistribution>>& classAttributeDistributions);
    void serialize(ostream &outputFile) override;
    void train(InstanceList& trainSet, Parameter* parameters) override;
    void loadModel(const string& fileName) override;
};


#endif //CLASSIFICATION_NAIVEBAYESMODEL_H
