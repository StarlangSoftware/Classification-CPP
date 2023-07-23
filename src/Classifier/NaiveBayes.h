//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_NAIVEBAYES_H
#define CLASSIFICATION_NAIVEBAYES_H
#include "Classifier.h"
#include "../InstanceList/Partition.h"

class NaiveBayes : public Classifier{
private:
    void trainContinuousVersion(const DiscreteDistribution& priorDistribution, const Partition& classLists);
    void trainDiscreteVersion(const DiscreteDistribution& priorDistribution, const Partition& classLists);
public:
    void train(InstanceList& trainSet, Parameter* parameters) override;
    void loadModel(const string& fileName) override;
};


#endif //CLASSIFICATION_NAIVEBAYES_H
