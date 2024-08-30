//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#ifndef CLASSIFICATION_KNNMODEL_H
#define CLASSIFICATION_KNNMODEL_H


#include "../../Instance/Instance.h"
#include "KnnInstance.h"
#include "../../InstanceList/InstanceList.h"
#include "../../DistanceMetric/DistanceMetric.h"
#include "../Model.h"

class KnnModel : public Model{
private:
    InstanceList data;
    int k;
    DistanceMetric* distanceMetric;
    void load(ifstream& inputFile);
public:
    KnnModel() = default;
    explicit KnnModel(ifstream& inputFile);
    KnnModel(const InstanceList& data, int k, DistanceMetric* distanceMetric);
    string predict(Instance* instance) override;
    map<string, double> predictProbability(Instance* instance) override;
    InstanceList nearestNeighbors(Instance* instance) const;
    void serialize(ostream &outputFile) override;
    void train(InstanceList& trainSet, Parameter* parameters) override;
    void loadModel(const string& fileName) override;
};

#endif //CLASSIFICATION_KNNMODEL_H
