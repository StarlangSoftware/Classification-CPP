//
// Created by Olcay Taner Yıldız on 4.02.2019.
//

#ifndef CLASSIFICATION_PCA_H
#define CLASSIFICATION_PCA_H


#include "TrainedFeatureFilter.h"

class Pca : public TrainedFeatureFilter{
private:
    double covarianceExplained = 0.99;
    vector<Eigenvector> eigenvectors;
    int numberOfDimensions = -1;
    void removeUnnecessaryEigenvectors(vector<Eigenvector> eigenvectors);
    void removeAllEigenvectorsExceptTheMostImportantK(vector<Eigenvector> eigenvectors);
public:
    Pca(DataSet dataSet, double covarianceExplained);
    Pca(DataSet dataSet, int numberOfDimensions);
    explicit Pca(DataSet dataSet);
    void train() override;
protected:
    void convertInstance(Instance* instance) override;
    void convertDataDefinition() override;
};


#endif //CLASSIFICATION_PCA_H
