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
    void load(ifstream& inputFile);
public:
    LdaModel() = default;
    explicit LdaModel(ifstream& inputFile);
    void serialize(ostream &outputFile) override;
    void train(InstanceList& trainSet, Parameter* parameters) override;
    void loadModel(const string& fileName) override;
};


#endif //CLASSIFICATION_LDAMODEL_H
