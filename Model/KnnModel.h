//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#ifndef CLASSIFICATION_KNNMODEL_H
#define CLASSIFICATION_KNNMODEL_H


#include "../Instance/Instance.h"
#include "KnnInstance.h"
#include "../InstanceList/InstanceList.h"
#include "../DistanceMetric/DistanceMetric.h"
#include "Model.h"

class KnnModel : public Model{
private:
    InstanceList data;
    int k;
    DistanceMetric* distanceMetric;
public:
    explicit KnnModel(ifstream& inputFile);
    KnnModel(InstanceList& data, int k, DistanceMetric* distanceMetric);
    string predict(Instance* instance) override;
    InstanceList nearestNeighbors(Instance* instance);
    void serialize(ostream &outputFile) override;
};

#endif //CLASSIFICATION_KNNMODEL_H
