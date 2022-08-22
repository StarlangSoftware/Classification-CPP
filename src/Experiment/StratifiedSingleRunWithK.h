//
// Created by Olcay Taner Yıldız on 7.02.2019.
//

#ifndef CLASSIFICATION_STRATIFIEDSINGLERUNWITHK_H
#define CLASSIFICATION_STRATIFIEDSINGLERUNWITHK_H


#include "SingleRunWithK.h"

class StratifiedSingleRunWithK : public SingleRunWithK {
public:
    explicit StratifiedSingleRunWithK(int K);
    Performance* execute(Experiment experiment) override;
};


#endif //CLASSIFICATION_STRATIFIEDSINGLERUNWITHK_H
