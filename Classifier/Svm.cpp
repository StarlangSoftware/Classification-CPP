//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#include "Svm.h"
#include "../Model/Svm/SvmModel.h"

/**
 * Training algorithm for Support Vector Machine classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters Parameters of the SVM classifier algorithm.
 */
void Svm::train(InstanceList &trainSet, Parameter *parameters) {
    model = new SvmModel(trainSet, (SvmParameter*) parameters);
}
