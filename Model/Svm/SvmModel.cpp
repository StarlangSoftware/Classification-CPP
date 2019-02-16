//
// Created by Olcay Taner Yıldız on 16.02.2019.
//
#include <cmath>
#include "SvmModel.h"
#include "SolutionInfo.h"
#include "Problem.h"
#include "Solver.h"

SvmModel::SvmModel(InstanceList &trainSet, SvmParameter *parameter) {
    vector<int> start;
    vector<int> nonZeroCount;
    vector<int> nonZeroStart;
    vector<string> classes;
    int l, nSV, si, ci, sj, cj, p, q, totalSupportVectors;
    vector<NodeList> x;
    vector<NodeList> subProblemX;
    vector<double> subProblemY;
    vector<bool> nonZero;
    vector<SolutionInfo> weights;
    this->parameter = parameter;
    trainSet.sort();
    Problem problem = Problem(trainSet);
    l = problem.getL();
    classDistribution = trainSet.classDistribution();
    numberOfClasses = classDistribution.size();
    classes = classDistribution.getItems();
    start = groupClasses();
    x.reserve(l);
    nonZero.reserve(l);
    for (int i = 0; i < l; i++){
        x[i] = problem.getX()[i];
        nonZero[i] = false;
    }
    p = 0;
    numberOfProblems = (numberOfClasses * (numberOfClasses - 1)) / 2;
    weights.reserve(numberOfProblems);
    for (int i = 0; i < numberOfClasses; i++){
        for (int j = i + 1; j < numberOfClasses; j++){
            si = start[i];
            sj = start[j];
            ci = classDistribution.getCount(classes[i]);
            cj = classDistribution.getCount(classes[j]);
            subProblemX.reserve(ci + cj);
            subProblemY.reserve(ci + cj);
            for (int k = 0; k < ci; k++){
                subProblemX[k] = x[si + k];
                subProblemY[k] = +1;
            }
            for (int k = 0; k < cj; k++){
                subProblemX[ci + k] = x[sj + k];
                subProblemY[ci + k] = -1;
            }
            weights[p] = solveSingle(Problem(subProblemX, subProblemY));
            for (int k = 0; k < ci; k++){
                if (!nonZero[si + k] && fabs(weights[p].getAlpha(k)) > 0){
                    nonZero[si + k] = true;
                }
            }
            for (int k = 0; k < cj; k++){
                if (!nonZero[sj + k] && fabs(weights[p].getAlpha(ci + k)) > 0){
                    nonZero[sj + k] = true;
                }
            }
            p++;
        }
    }
    rho.reserve(numberOfProblems);
    for (int i = 0; i < numberOfProblems; i++){
        rho[i] = weights[i].getRho();
    }
    totalSupportVectors = 0;
    nonZeroCount.reserve(numberOfClasses);
    numberOfSupportVectors.reserve(numberOfClasses);
    for (int i = 0; i < numberOfClasses; i++){
        nSV = 0;
        for (int j = 0; j < classDistribution.getCount(classes[i]); j++){
            if (nonZero[start[i] + j]){
                nSV++;
                totalSupportVectors++;
            }
        }
        numberOfSupportVectors[i] = nSV;
        nonZeroCount[i] = nSV;
    }
    supportVectors.reserve(totalSupportVectors);
    p = 0;
    for (int i = 0; i < l; i++){
        if (nonZero[i]){
            supportVectors[p] = x[i];
            p++;
        }
    }
    nonZeroStart.reserve(numberOfClasses);
    nonZeroStart[0] = 0;
    for (int i = 1; i < numberOfClasses; i++){
        nonZeroStart[i] = nonZeroStart[i - 1] + nonZeroCount[i - 1];
    }
    supportVectorCoefficients.reserve(numberOfClasses - 1);
    for (int i = 0; i < numberOfClasses - 1; i++){
        supportVectorCoefficients[i].reserve(totalSupportVectors);
    }
    p = 0;
    for (int i = 0; i < numberOfClasses; i++){
        for (int j = i + 1; j < numberOfClasses; j++){
            si = start[i];
            sj = start[j];
            ci = classDistribution.getCount(classes[i]);
            cj = classDistribution.getCount(classes[j]);
            q = nonZeroStart[i];
            for (int k = 0; k < ci; k++){
                if (nonZero[si + k]){
                    supportVectorCoefficients[j - 1][q] = weights[p].getAlpha(k);
                    q++;
                }
            }
            q = nonZeroStart[j];
            for (int k = 0; k < cj; k++){
                if (nonZero[sj + k]){
                    supportVectorCoefficients[i][q] = weights[p].getAlpha(ci + k);
                    q++;
                }
            }
            p++;
        }
    }
}

vector<int> SvmModel::groupClasses() {
    vector<int> start;
    vector<string> classes = classDistribution.getItems();
    start.reserve(numberOfClasses);
    start[0] = 0;
    for (int i = 1; i < numberOfClasses; i++){
        start[i] = start[i - 1] + classDistribution.getCount(classes[i - 1]);
    }
    return start;
}

SolutionInfo SvmModel::solveSingle(Problem problem) {
    vector<double> minusOnes;
    vector<double> y;
    minusOnes.reserve(problem.getL());
    y.reserve(problem.getL());
    for (int i = 0; i < problem.getL(); i++){
        minusOnes[i] = -1;
        if (problem.getY()[i] > 0){
            y[i] = 1;
        } else {
            y[i] = -1;
        }
    }
    Solver solver = Solver(problem.getL(), minusOnes, y, parameter, problem);
    SolutionInfo solutionInfo = solver.solve();
    for (int i = 0; i < problem.getL(); i++){
        solutionInfo.setAlpha(i, solutionInfo.getAlpha(i) * y[i]);
    }
    return solutionInfo;
}

vector<double> SvmModel::predictValues(NodeList x) {
    vector<int> start;
    int p, si, sj, ci, cj;
    int l = supportVectors.size();
    vector<double> coefficients1;
    vector<double> coefficients2;
    vector<double> kernelValues;
    kernelValues.reserve(l);
    vector<double> result;
    for (int i = 0; i < l; i++){
        kernelValues[i] = Kernel::function(x, supportVectors[i], parameter);
    }
    start.reserve(numberOfClasses);
    start[0] = 0;
    for (int i = 1; i < numberOfClasses; i++){
        start[i] = start[i - 1] + numberOfSupportVectors[i - 1];
    }
    result.reserve(numberOfProblems);
    p = 0;
    for (int i = 0; i < numberOfClasses; i++){
        for (int j = i + 1; j < numberOfClasses; j++){
            double sum = 0;
            si = start[i];
            sj = start[j];
            ci = numberOfSupportVectors[i];
            cj = numberOfSupportVectors[j];
            coefficients1 = supportVectorCoefficients[j - 1];
            coefficients2 = supportVectorCoefficients[i];
            for (int k = 0; k < ci; k++){
                sum += coefficients1[si + k] * kernelValues[si + k];
            }
            for (int k = 0; k < cj; k++){
                sum += coefficients2[sj + k] * kernelValues[sj + k];
            }
            sum -= rho[p];
            result[p] = sum;
            p++;
        }
    }
    return result;
}

string SvmModel::predict(Instance *instance) {
    int pos, maxIndex, maxVotes;
    vector<int> numberOfVotes;
    numberOfVotes.reserve(numberOfClasses);
    NodeList x = instance->toNodeList();
    vector<double> predictedValues = predictValues(x);
    for (int i = 0; i < numberOfClasses; i++){
        numberOfVotes[i] = 0;
    }
    pos = 0;
    for (int i = 0; i < numberOfClasses; i++){
        for (int j = i + 1; j < numberOfClasses; j++){
            if (predictedValues[pos] > 0){
                numberOfVotes[i]++;
            } else {
                numberOfVotes[j]++;
            }
            pos++;
        }
    }
    maxVotes = numberOfVotes[0];
    maxIndex = 0;
    for (int i = 1; i < numberOfClasses; i++){
        if (numberOfVotes[i] > maxVotes){
            maxIndex = i;
            maxVotes = numberOfVotes[i];
        }
    }
    vector<string> classes = classDistribution.getItems();
    return classes[maxIndex];
}
