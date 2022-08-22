//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#ifndef CLASSIFICATION_SOLVER_H
#define CLASSIFICATION_SOLVER_H

#include "../../Parameter/SvmParameter.h"
#include "AlphaStatusType.h"
#include "QMatrix.h"
#include "SolutionInfo.h"

class Solver {
private:
    int activeSize;
    vector<double> y;
    vector<double> alpha;
    vector<double> G;
    vector<AlphaStatusType> alphaStatus;
    QMatrix Q;
    double C;
    vector<double> b;
    vector<int> activeSet;
    vector<double> GBar;
    int l;
    bool unshrinked = false;
    SvmParameter* parameter;
    void updateAlphaStatus(int i);
    bool isUpperBound(int i);
    bool isLowerBound(int i);
    bool isFree(int i);
    vector<double> getQ(int i, int length);
    void swapIndex(int i, int j);
    void reconstructGradient();
    bool selectWorkingSet(int out[]);
    double calculateRho();
    void doShrinking();
public:
    Solver(int l, vector<double> b, vector<double> y, SvmParameter* parameter, Problem problem);
    SolutionInfo solve();
};


#endif //CLASSIFICATION_SOLVER_H
