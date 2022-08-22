//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#ifndef CLASSIFICATION_KMEANS_H
#define CLASSIFICATION_KMEANS_H
#include "Classifier.h"

class KMeans : public Classifier {
public:
    void train(InstanceList& trainSet, Parameter* parameters) override;
};


#endif //CLASSIFICATION_KMEANS_H
