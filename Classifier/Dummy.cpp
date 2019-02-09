//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include "Dummy.h"
#include "../Model/DummyModel.h"

void Dummy::train(InstanceList &trainSet, Parameter *parameters) {
    model = new DummyModel(trainSet);
}
