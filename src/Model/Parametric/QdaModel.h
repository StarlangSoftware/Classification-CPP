//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_QDAMODEL_H
#define CLASSIFICATION_QDAMODEL_H


#include "LdaModel.h"

class QdaModel : public LdaModel{
private:
    map<string, Matrix> W;
protected:
    void load(ifstream& inputFile);
public:
    QdaModel() = default;
    explicit QdaModel(ifstream& inputFile);
    double calculateMetric(Instance* instance, const string& Ci) const override;
    void train(InstanceList& trainSet, Parameter* parameters) override;
    void loadModel(const string& fileName) override;
};


#endif //CLASSIFICATION_QDAMODEL_H
