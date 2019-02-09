//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_NAIVEBAYES_H
#define CLASSIFICATION_NAIVEBAYES_H
#include "Classifier.h"
#include "../InstanceList/Partition.h"

class NaiveBayes : public Classifier{
private:
    void trainContinuousVersion(DiscreteDistribution priorDistribution, Partition classLists);
    void trainDiscreteVersion(DiscreteDistribution priorDistribution, Partition classLists);
public:
    void train(InstanceList& trainSet, Parameter* parameters);
};


#endif //CLASSIFICATION_NAIVEBAYES_H
