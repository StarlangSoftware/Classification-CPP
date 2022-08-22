//
// Created by olcay on 12.02.2019.
//

#include "LinearPerceptron.h"
#include "../InstanceList/Partition.h"
#include "../Parameter/LinearPerceptronParameter.h"
#include "../Model/LinearPerceptronModel.h"
#include "DiscreteFeaturesNotAllowed.h"

/**
 * Training algorithm for the linear perceptron algorithm. 20 percent of the data is separated as cross-validation
 * data used for selecting the best weights. 80 percent of the data is used for training the linear perceptron with
 * gradient descent.
 *
 * @param trainSet   Training data given to the algorithm
 * @param parameters Parameters of the linear perceptron.
 */
void LinearPerceptron::train(InstanceList& trainSet, Parameter *parameters) {
    if (!discreteCheck(trainSet.get(0))){
        throw DiscreteFeaturesNotAllowed();
    }
    Partition partition = Partition(trainSet, ((LinearPerceptronParameter*) parameters)->getCrossValidationRatio(), parameters->getSeed(), true);
    model = new LinearPerceptronModel(*(partition.get(1)), *(partition.get(0)), (LinearPerceptronParameter*) parameters);
}
