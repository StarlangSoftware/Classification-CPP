//
// Created by Olcay Taner Yıldız on 4.02.2019.
//

#ifndef CLASSIFICATION_LARYTOBINARY_H
#define CLASSIFICATION_LARYTOBINARY_H


#include "LaryFilter.h"

class LaryToBinary : public LaryFilter{
protected:
    void convertInstance(Instance* instance) override;
    void convertDataDefinition() override;
public:
    explicit LaryToBinary(DataSet& dataSet);
};


#endif //CLASSIFICATION_LARYTOBINARY_H
