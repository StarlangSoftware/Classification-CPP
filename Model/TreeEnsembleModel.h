//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#ifndef CLASSIFICATION_TREEENSEMBLEMODEL_H
#define CLASSIFICATION_TREEENSEMBLEMODEL_H
#include "Model.h"
#include "DecisionTree/DecisionTree.h"

class TreeEnsembleModel : public Model {
private:
    vector<DecisionTree> forest;
public:
    string predict(Instance* instance) override;
    explicit TreeEnsembleModel(ifstream& inputFile);
    explicit TreeEnsembleModel(vector<DecisionTree> forest);
    void serialize(ostream &outputFile) override;
};


#endif //CLASSIFICATION_TREEENSEMBLEMODEL_H
