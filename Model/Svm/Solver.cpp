//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#include <cmath>
#include <cfloat>
#include "Solver.h"
#include "QMatrix.h"

Solver::Solver(int l, vector<double> b, vector<double> y, SvmParameter *parameter, Problem problem) {
    this->parameter = parameter;
    this->l = l;
    this->Q = QMatrix(move(problem), parameter, y);
    this->b = move(b);
    this->y = y;
    C = parameter->getC();
}

SolutionInfo Solver::solve() {
    vector<double> Qi;
    vector<double> Qj;
    double alphaI, oldAlphaI, oldAlphaJ, delta, diff, sum, deltaAlphaI, deltaAlphaJ;
    int counter, i, j;
    bool upperBoundI, upperBoundJ;
    alpha.reserve(l);
    for (i = 0; i < l; i++){
        alpha[i] = 0.0;
    }
    alphaStatus.reserve(l);
    for (i = 0; i < l; i++){
        updateAlphaStatus(i);
    }
    activeSet.reserve(l);
    for (i = 0; i < l; i++){
        activeSet[i] = i;
    }
    activeSize = l;
    G.reserve(l);
    GBar.reserve(l);
    for (i = 0; i < l; i++){
        G[i] = b[i];
        GBar[i] = 0;
    }
    for (i = 0; i < l; i++){
        if (!isLowerBound(i)){
            Qi = getQ(i, l);
            alphaI = alpha[i];
            for (j = 0; j < l; j++){
                G[j] += alphaI * Qi[j];
            }
            if (isUpperBound(i)){
                for (j = 0; j < l; j++){
                    GBar[j] += C * Qi[j];
                }
            }
        }
    }
    counter = fmin(l, 1000) + 1;
    while (true){
        if (--counter == 0){
            counter = fmin(l, 1000);
            if (parameter->isShrinking()){
                doShrinking();
            }
        }
        int* out = new int[2];
        if (selectWorkingSet(out)){
            reconstructGradient();
            activeSize = l;
            if (selectWorkingSet(out)){
                break;
            } else {
                counter = 1;
            }
        }
        i = out[0];
        j = out[1];
        Qi = getQ(i, activeSize);
        Qj = getQ(j, activeSize);
        oldAlphaI = alpha[i];
        oldAlphaJ = alpha[j];
        if (y[i] != y[j]){
            delta = (-G[i] - G[j]) / fmax(Qi[i] + Qj[j] + 2 * Qi[j], 0.0);
            diff = alpha[i] - alpha[j];
            alpha[i] += delta;
            alpha[j] += delta;
            if (diff > 0){
                if (alpha[j] < 0){
                    alpha[j] = 0;
                    alpha[i] = diff;
                }
                if (alpha[i] > C){
                    alpha[i] = C;
                    alpha[j] = C - diff;
                }
            } else {
                if (alpha[i] < 0){
                    alpha[i] = 0;
                    alpha[j] = -diff;
                }
                if (alpha[j] > C){
                    alpha[j] = C;
                    alpha[i] = C + diff;
                }
            }
        } else {
            delta = (G[i] - G[j]) / fmax(Qi[i] + Qj[j] - 2 * Qi[j], 0.0);
            sum = alpha[i] + alpha[j];
            alpha[i] -= delta;
            alpha[j] += delta;
            if (sum > C){
                if (alpha[i] > C){
                    alpha[i] = C;
                    alpha[j] = sum - C;
                }
                if (alpha[j] > C){
                    alpha[j] = C;
                    alpha[i] = sum - C;
                }
            } else {
                if (alpha[j] < 0){
                    alpha[j] = 0;
                    alpha[i] = sum;
                }
                if (alpha[i] < 0){
                    alpha[i] = 0;
                    alpha[j] = sum;
                }
            }
        }
        deltaAlphaI = alpha[i] - oldAlphaI;
        deltaAlphaJ = alpha[j] - oldAlphaJ;
        for (int k = 0; k < activeSize; k++){
            G[k] += Qi[k] * deltaAlphaI + Qj[k] * deltaAlphaJ;
        }
        upperBoundI = isUpperBound(i);
        upperBoundJ = isUpperBound(j);
        updateAlphaStatus(i);
        updateAlphaStatus(j);
        if (upperBoundI != isUpperBound(i)){
            Qi = getQ(i, l);
            if (upperBoundI){
                for (int k = 0; k < l; k++){
                    GBar[k] -= C * Qi[k];
                }
            } else {
                for (int k = 0; k < l; k++){
                    GBar[k] += C * Qi[k];
                }
            }
        }
        if (upperBoundJ != isUpperBound(j)){
            Qj = getQ(j, l);
            if (upperBoundJ){
                for (int k = 0; k < l; k++){
                    GBar[k] -= C * Qj[k];
                }
            } else {
                for (int k = 0; k < l; k++){
                    GBar[k] += C * Qj[k];
                }
            }
        }
    }
    for (i = 0; i < l; i++){
        alpha[activeSet[i]] = alpha[i];
    }
    return SolutionInfo(calculateRho(), alpha);
}

void Solver::updateAlphaStatus(int i) {
    if (alpha[i] >= C){
        alphaStatus[i] = AlphaStatusType::UPPER_BOUND;
    } else {
        if (alpha[i] <= 0){
            alphaStatus[i] = AlphaStatusType::LOWER_BOUND;
        } else {
            alphaStatus[i] = AlphaStatusType::FREE;
        }
    }
}

bool Solver::isUpperBound(int i) {
    return alphaStatus[i] == AlphaStatusType::UPPER_BOUND;
}

bool Solver::isLowerBound(int i) {
    return alphaStatus[i] == AlphaStatusType::LOWER_BOUND;
}

bool Solver::isFree(int i) {
    return alphaStatus[i] == AlphaStatusType::FREE;
}

vector<double> Solver::getQ(int i, int length) {
    return Q.getQ(i, length);
}

void Solver::swapIndex(int i, int j) {
    Q.swapIndex(i, j);
    swap(y[i], y[j]);
    swap(G[i], G[j]);
    swap(alpha[i], alpha[j]);
    swap(b[i], b[j]);
    swap(GBar[i], GBar[j]);
    swap(activeSet[i], activeSet[j]);
    swap(alphaStatus[i], alphaStatus[j]);
}

void Solver::reconstructGradient() {
    vector<double> Qi;
    double alphaI;
    if (activeSize == l){
        return;
    }
    for (int i = activeSize; i < l; i++){
        G[i] = GBar[i] + b[i];
    }
    for (int i = 0; i < activeSize; i++){
        if (isFree(i)){
            Qi = getQ(i, l);
            alphaI = alpha[i];
            for (int j = activeSize; j < l; j++){
                G[j] += alphaI * Qi[j];
            }
        }
    }
}

bool Solver::selectWorkingSet(int out[]) {
    double GMax[] = {-DBL_MAX, -DBL_MAX};
    for (int i = 0; i < activeSize; i++){
        if (y[i] == 1){
            if (!isUpperBound(i)){
                if (-G[i] >= GMax[0]){
                    GMax[0] = -G[i];
                    out[0] = i;
                }
            }
            if (!isLowerBound(i)){
                if (G[i] >= GMax[1]){
                    GMax[1] = G[i];
                    out[1] = i;
                }
            }
        } else {
            if (!isUpperBound(i)){
                if (-G[i] >= GMax[1]){
                    GMax[1] = -G[i];
                    out[1] = i;
                }
            }
            if (!isLowerBound(i)){
                if (G[i] >= GMax[0]){
                    GMax[0] = G[i];
                    out[0] = i;
                }
            }
        }
    }
    if (GMax[0] + GMax[1] < 0.001){
        return true;
    }
    return false;
}

double Solver::calculateRho() {
    double upperBound = DBL_MAX, lowerBound = -DBL_MAX, sumFree = 0, yG;
    int numberOfFree = 0;
    for (int i = 0; i < activeSize; i++){
        yG = y[i] * G[i];
        if (isLowerBound(i)){
            if (y[i] > 0){
                upperBound = fmin(upperBound, yG);
            } else {
                lowerBound = fmax(lowerBound, yG);
            }
        } else {
            if (isUpperBound(i)){
                if (y[i] < 0){
                    upperBound = fmin(upperBound, yG);
                } else {
                    lowerBound = fmax(lowerBound, yG);
                }
            } else {
                numberOfFree++;
                sumFree += yG;
            }
        }
    }
    if (numberOfFree > 0){
        return sumFree / numberOfFree;
    } else {
        return (upperBound + lowerBound) / 2;
    }
}

void Solver::doShrinking() {
    double* Gm = new double[2];
    int* out = new int[2];
    if (selectWorkingSet(out)){
        return;
    }
    Gm[0] = -y[out[1]] * G[out[1]];
    Gm[1] = y[out[0]] * G[out[0]];
    for (int k = 0; k < activeSize; k++){
        if (isLowerBound(k)){
            if (y[k] == 1) {
                if (-G[k] >= Gm[0]) {
                    continue;
                }
            } else {
                if (-G[k] >= Gm[1]){
                    continue;
                }
            }
        } else {
            if (isUpperBound(k)){
                if (y[k] == 1){
                    if (G[k] >= Gm[1]){
                        continue;
                    }
                } else {
                    if (G[k] >= Gm[0]){
                        continue;
                    }
                }
            } else {
                continue;
            }
        }
        activeSize--;
        swapIndex(k, activeSize);
        k--;
    }
    if (unshrinked || -(Gm[0] + Gm[1]) > 0.001 * 10){
        return;
    }
    unshrinked = true;
    reconstructGradient();
    for (int k = l - 1; k >= activeSize; k--){
        if (isLowerBound(k)){
            if (y[k] == 1) {
                if (-G[k] < Gm[0]) {
                    continue;
                }
            } else {
                if (-G[k] < Gm[1]){
                    continue;
                }
            }
        } else {
            if (isUpperBound(k)){
                if (y[k] == 1){
                    if (G[k] < Gm[1]){
                        continue;
                    }
                } else {
                    if (G[k] < Gm[0]){
                        continue;
                    }
                }
            } else {
                continue;
            }
        }
        swapIndex(k, activeSize);
        activeSize++;
        k++;
    }
}
