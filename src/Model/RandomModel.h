//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_RANDOMMODEL_H
#define CLASSIFICATION_RANDOMMODEL_H
#include "Model.h"

class RandomModel : public Model{
private:
    int seed;
    vector<string> classLabels;
public:
    explicit RandomModel(ifstream& inputFile);
    explicit RandomModel(const vector<string>& classLabels);
    string predict(Instance* instance) override;
    map<string, double> predictProbability(Instance* instance) override;
    void serialize(ostream &outputFile) override;
};


#endif //CLASSIFICATION_RANDOMMODEL_H
