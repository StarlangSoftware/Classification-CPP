//
// Created by Olcay Taner Yıldız on 14.02.2019.
//

#ifndef CLASSIFICATION_MULTILAYERPERCEPTRONMODEL_H
#define CLASSIFICATION_MULTILAYERPERCEPTRONMODEL_H

#include "LinearPerceptronModel.h"
#include "../Parameter/MultiLayerPerceptronParameter.h"

class MultiLayerPerceptronModel : public LinearPerceptronModel {
protected:
    void calculateOutput() override;
private:
    Matrix V = Matrix(0);
    ActivationFunction activationFunction;
    void allocateWeights(int H, default_random_engine randomEngine);
public:
    explicit MultiLayerPerceptronModel(ifstream& inputFile);
    MultiLayerPerceptronModel(InstanceList& trainSet, const InstanceList& validationSet, MultiLayerPerceptronParameter* parameters);
    void serialize(ostream &outputFile) override;
};


#endif //CLASSIFICATION_MULTILAYERPERCEPTRONMODEL_H
