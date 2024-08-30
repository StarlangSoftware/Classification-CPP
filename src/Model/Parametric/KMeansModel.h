//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#ifndef CLASSIFICATION_KMEANSMODELS_H
#define CLASSIFICATION_KMEANSMODELS_H


#include "GaussianModel.h"
#include "../../DistanceMetric/DistanceMetric.h"

class KMeansModel : public GaussianModel{
private:
    InstanceList classMeans;
    DistanceMetric* distanceMetric;
public:
    KMeansModel() = default;
    explicit KMeansModel(ifstream& inputFile);
    KMeansModel(const DiscreteDistribution& priorDistribution, const InstanceList& classMeans, DistanceMetric* distanceMetric);
    void serialize(ostream &outputFile) override;
    void train(InstanceList& trainSet, Parameter* parameters) override;
    void loadModel(const string& fileName) override;
protected:
    double calculateMetric(Instance* instance, const string& Ci) const override;
    void load(ifstream& inputFile);
};


#endif //CLASSIFICATION_KMEANSMODELS_H
