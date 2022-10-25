//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_LDAMODEL_H
#define CLASSIFICATION_LDAMODEL_H


#include "GaussianModel.h"

class LdaModel : public GaussianModel {
protected:
    map<string, double> w0;
    map<string, Vector> w;
    double calculateMetric(Instance* instance, const string& Ci) const override;
public:
    explicit LdaModel(ifstream& inputFile);
    LdaModel(const DiscreteDistribution& priorDistribution, const map<string, Vector>& w, const map<string, double>& w0);
    void serialize(ostream &outputFile) override;
};


#endif //CLASSIFICATION_LDAMODEL_H
