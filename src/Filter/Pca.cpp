//
// Created by Olcay Taner Yıldız on 4.02.2019.
//

#include <VectorSizeMismatch.h>
#include "Pca.h"
#include "MatrixNotSymmetric.h"
#include "../Attribute/ContinuousAttribute.h"

/**
 * Constructor that sets the dataSet and covariance explained. Then calls train method.
 *
 * @param dataSet             DataSet that will bu used.
 * @param covarianceExplained Number that shows the explained covariance.
 */
Pca::Pca(const DataSet& dataSet, double covarianceExplained) : TrainedFeatureFilter(dataSet) {
    this->covarianceExplained = covarianceExplained;
    train();
}

/**
 * Constructor that sets the dataSet and dimension. Then calls train method.
 *
 * @param dataSet            DataSet that will bu used.
 * @param numberOfDimensions Dimension number.
 */
Pca::Pca(const DataSet& dataSet, int numberOfDimensions) : TrainedFeatureFilter(dataSet) {
    this->numberOfDimensions = numberOfDimensions;
    train();
}

/**
 * Constructor that sets the dataSet and dimension. Then calls train method.
 *
 * @param dataSet DataSet that will bu used.
 */
Pca::Pca(const DataSet& dataSet) : TrainedFeatureFilter(dataSet) {
    train();
}

/**
 * The removeUnnecessaryEigenvectors methods takes an ArrayList of Eigenvectors. It first calculates the summation
 * of eigenValues. Then it finds the eigenvectors which have lesser summation than covarianceExplained and removes these
 * eigenvectors.
 */
void Pca::removeUnnecessaryEigenvectors() {
    double sum = 0.0, currentSum = 0.0;
    for (const Eigenvector& eigenvector : eigenvectors) {
        sum += eigenvector.getEigenValue();
    }
    vector<Eigenvector>::iterator item;
    while (item != eigenvectors.end()) {
        if (currentSum / sum < covarianceExplained) {
            currentSum += item->getEigenValue();
        } else {
            break;
        }
    }
    eigenvectors.erase(item, eigenvectors.end());
}

/**
 * The removeAllEigenvectorsExceptTheMostImportantK method takes an ArrayList of Eigenvectors and removes the
 * surplus eigenvectors when the number of eigenvectors is greater than the dimension.
 */
void Pca::removeAllEigenvectorsExceptTheMostImportantK() {
    eigenvectors.erase(eigenvectors.begin() + numberOfDimensions, eigenvectors.end());
}

/**
 * The train method creates an averageVector from continuousAttributeAverage and a covariance Matrix from that averageVector.
 * Then finds the eigenvectors of that covariance matrix and removes its unnecessary eigenvectors.
 */
void Pca::train() {
    Vector averageVector = Vector(dataSet.getInstanceList().continuousAttributeAverage());
    Matrix covariance = dataSet.getInstanceList().covariance(averageVector);
    try {
        eigenvectors = covariance.characteristics();
        if (numberOfDimensions != -1) {
            removeAllEigenvectorsExceptTheMostImportantK();
        } else {
            removeUnnecessaryEigenvectors();
        }
    } catch (MatrixNotSymmetric& matrixNotSymmetric) {
    }
}

/**
 * The convertInstance method takes an Instance as an input and creates a {@link java.util.Vector} attributes from continuousAttributes.
 * After removing all attributes of given instance, it then adds new ContinuousAttribute by using the dot
 * product of attributes Vector and the eigenvectors.
 *
 * @param instance Instance that will be converted to ContinuousAttribute by using eigenvectors.
 */
void Pca::convertInstance(Instance* instance) {
    Vector attributes = Vector(instance->continuousAttributes());
    instance->removeAllAttributes();
    for (const Eigenvector &eigenvector : eigenvectors) {
        try {
            instance->addAttribute(new ContinuousAttribute(attributes.dotProduct(eigenvector)));
        } catch (VectorSizeMismatch& vectorSizeMismatch) {
        }
    }
}

/**
 * The convertDataDefinition method gets the data definitions of the dataSet and removes all the attributes. Then adds
 * new attributes as CONTINUOUS.
 */
void Pca::convertDataDefinition() {
    DataDefinition dataDefinition = dataSet.getDataDefinition();
    dataDefinition.removeAllAttributes();
    for (int i = 0; i < eigenvectors.size(); i++) {
        dataDefinition.addAttribute(AttributeType::CONTINUOUS);
    }
}
