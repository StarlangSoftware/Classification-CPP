//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#ifndef CLASSIFICATION_TREEENSEMBLEMODEL_H
#define CLASSIFICATION_TREEENSEMBLEMODEL_H
#include "../Model.h"
#include "../DecisionTree/DecisionTree.h"

class TreeEnsembleModel : public Model {
protected:
    vector<DecisionTree*> forest;
    void load(ifstream& inputFile);
public:
    TreeEnsembleModel() = default;
    string predict(Instance* instance) override;
    map<string, double> predictProbability(Instance* instance) override;
    explicit TreeEnsembleModel(ifstream& inputFile);
    explicit TreeEnsembleModel(const vector<DecisionTree*>& forest);
    void serialize(ostream &outputFile) override;
};


#endif //CLASSIFICATION_TREEENSEMBLEMODEL_H
