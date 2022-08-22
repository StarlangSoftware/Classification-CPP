//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#ifndef CLASSIFICATION_VALIDATEDMODEL_H
#define CLASSIFICATION_VALIDATEDMODEL_H


#include "Model.h"
#include "../Performance/ClassificationPerformance.h"
#include "../InstanceList/InstanceList.h"

class ValidatedModel : public Model {
public:
    ClassificationPerformance* testClassifier(InstanceList data);
    void serialize(ostream &outputFile) override;
};


#endif //CLASSIFICATION_VALIDATEDMODEL_H
