#include <utility>

//
// Created by Olcay Taner Yıldız on 29.01.2019.
//

#include "MahalanobisDistance.h"
#include "MatrixRowMismatch.h"
#include "VectorSizeMismatch.h"

/**
 * Constructor for the MahalanobisDistance class. Basically sets the inverse of the covariance matrix.
 *
 * @param covarianceInverse Inverse of the covariance matrix.
 */
MahalanobisDistance::MahalanobisDistance(const Matrix& covarianceInverse) {
    this->covarianceInverse = covarianceInverse;
}

/**
 * Calculates Mahalanobis distance between two instances. (x^(1) - x^(2)) S (x^(1) - x^(2))^T
 *
 * @param instance1 First instance.
 * @param instance2 Second instance.
 * @return Mahalanobis distance between two instances.
 */
double MahalanobisDistance::distance(Instance *instance1, Instance *instance2) {
    Vector v1 = instance1->toVector();
    Vector v2 = instance2->toVector();
    try {
        v1.subtract(v2);
        Vector v3 = covarianceInverse.multiplyWithVectorFromLeft(v1);
        return v3.dotProduct(v1);
    } catch (MatrixRowMismatch& e) {
        return INT_MAX;
    } catch (VectorSizeMismatch& e){
        return INT_MAX;
    }
}
