//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_RANDOMMODEL_H
#define CLASSIFICATION_RANDOMMODEL_H
#include "Model.h"

class RandomModel : public Model{
private:
    vector<string> classLabels;
public:
    explicit RandomModel(vector<string> classLabels);
    string predict(Instance* instance);
};


#endif //CLASSIFICATION_RANDOMMODEL_H
