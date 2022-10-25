//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_QDAMODEL_H
#define CLASSIFICATION_QDAMODEL_H


#include "LdaModel.h"

class QdaModel : public LdaModel{
private:
    map<string, Matrix> W;
public:
    double calculateMetric(Instance* instance, const string& Ci) const override;
    explicit QdaModel(ifstream& inputFile);
    QdaModel(const DiscreteDistribution& priorDistribution, const map<string, Matrix>& W, const map<string, Vector>& w, const map<string, double>& w0);
    void serialize(ostream &outputFile) override;
};


#endif //CLASSIFICATION_QDAMODEL_H
