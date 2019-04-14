//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_GAUSSIANMODEL_H
#define CLASSIFICATION_GAUSSIANMODEL_H


#include "ValidatedModel.h"

class GaussianModel : public ValidatedModel {
protected:
    DiscreteDistribution priorDistribution;
    /**
    * Abstract method calculateMetric takes an {@link Instance} and a String as inputs.
    *
    * @param instance {@link Instance} input.
    * @param Ci       String input.
    * @return A double value as metric.
    */
    virtual double calculateMetric(Instance* instance, string Ci) = 0;
public:
    GaussianModel() = default;
    explicit GaussianModel(ifstream& inputFile);
    string predict(Instance* instance) override;
    void serialize(ostream &outputFile) override;
};


#endif //CLASSIFICATION_GAUSSIANMODEL_H
