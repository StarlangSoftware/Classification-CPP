//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include <fstream>
#include "Dummy.h"
#include "../Model/DummyModel.h"

void Dummy::train(InstanceList &trainSet, Parameter *parameters) {
    model = new DummyModel(trainSet);
}

void Dummy::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    model = new DummyModel(inputFile);
    inputFile.close();
}
