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
    [[nodiscard]] bool isUpperBound(int i) const;
    [[nodiscard]] bool isLowerBound(int i) const;
    [[nodiscard]] bool isFree(int i) const;
    [[nodiscard]] vector<double> getQ(int i, int length) const;
    void swapIndex(int i, int j);
    void reconstructGradient();
    bool selectWorkingSet(int out[]);
    [[nodiscard]] double calculateRho() const;
    void doShrinking();
public:
    Solver(int l, const vector<double>& b, const vector<double>& y, SvmParameter* parameter, const Problem& problem);
    SolutionInfo solve();
};


#endif //CLASSIFICATION_SOLVER_H
