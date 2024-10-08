//
// Created by Olcay Taner Yıldız on 16.02.2019.
//
#include <cmath>
#include <fstream>
#include "SvmModel.h"
#include "SolutionInfo.h"
#include "Problem.h"
#include "Solver.h"
#include "../../Model/DiscreteFeaturesNotAllowed.h"

/**
 * Training algorithm for Support Vector Machine classifier.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters Parameters of the SVM classifier algorithm.
 */
void SvmModel::train(InstanceList &trainSet, Parameter *parameters) {
    if (!discreteCheck(trainSet.get(0))){
        throw DiscreteFeaturesNotAllowed();
    }
    parameter = (SvmParameter*) parameters;
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
        x.push_back(problem.getX()[i]);
        nonZero.push_back(false);
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
            subProblemX.resize(ci + cj);
            subProblemY.resize(ci + cj);
            for (int k = 0; k < ci; k++){
                subProblemX[k] = x[si + k];
                subProblemY[k] = +1;
            }
            for (int k = 0; k < cj; k++){
                subProblemX[ci + k] = x[sj + k];
                subProblemY[ci + k] = -1;
            }
            weights.push_back(solveSingle(Problem(subProblemX, subProblemY)));
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
        rho.push_back(weights[i].getRho());
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
        numberOfSupportVectors.push_back(nSV);
        nonZeroCount.push_back(nSV);
    }
    supportVectors.reserve(totalSupportVectors);
    p = 0;
    for (int i = 0; i < l; i++){
        if (nonZero[i]){
            supportVectors.push_back(x[i]);
            p++;
        }
    }
    nonZeroStart.reserve(numberOfClasses);
    nonZeroStart.push_back(0);
    for (int i = 1; i < numberOfClasses; i++){
        nonZeroStart.push_back(nonZeroStart[i - 1] + nonZeroCount[i - 1]);
    }
    supportVectorCoefficients.resize(numberOfClasses - 1);
    for (int i = 0; i < numberOfClasses - 1; i++){
        supportVectorCoefficients[i].resize(totalSupportVectors);
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

vector<int> SvmModel::groupClasses() const{
    vector<int> start;
    vector<string> classes = classDistribution.getItems();
    start.reserve(numberOfClasses);
    start.push_back(0);
    for (int i = 1; i < numberOfClasses; i++){
        start.push_back(start[i - 1] + classDistribution.getCount(classes[i - 1]));
    }
    return start;
}

SolutionInfo SvmModel::solveSingle(const Problem& problem) {
    vector<double> minusOnes(problem.getL(), -1.0);
    vector<double> y;
    y.reserve(problem.getL());
    for (int i = 0; i < problem.getL(); i++){
        if (problem.getY()[i] > 0){
            y.push_back(1);
        } else {
            y.push_back(-1);
        }
    }
    Solver solver = Solver(problem.getL(), minusOnes, y, parameter, problem);
    SolutionInfo solutionInfo = solver.solve();
    for (int i = 0; i < problem.getL(); i++){
        solutionInfo.setAlpha(i, solutionInfo.getAlpha(i) * y[i]);
    }
    return solutionInfo;
}

vector<double> SvmModel::predictValues(const NodeList& x) {
    vector<int> start;
    int p, si, sj, ci, cj;
    int l = supportVectors.size();
    vector<double> coefficients1;
    vector<double> coefficients2;
    vector<double> kernelValues;
    kernelValues.reserve(l);
    vector<double> result;
    for (int i = 0; i < l; i++){
        kernelValues.push_back(Kernel::function(x, supportVectors[i], parameter));
    }
    start.reserve(numberOfClasses);
    start.push_back(0);
    for (int i = 1; i < numberOfClasses; i++){
        start.push_back(start[i - 1] + numberOfSupportVectors[i - 1]);
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
            result.push_back(sum);
            p++;
        }
    }
    return result;
}

string SvmModel::predict(Instance *instance) {
    int pos, maxIndex, maxVotes;
    vector<int> numberOfVotes(numberOfClasses, 0);
    NodeList x = instance->toNodeList();
    vector<double> predictedValues = predictValues(x);
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

void SvmModel::serialize(ostream &outputFile) {
    outputFile << numberOfClasses << "\n";
    outputFile << numberOfProblems << "\n";
    classDistribution.serialize(outputFile);
    outputFile << rho.size() << "\n";
    for (double r : rho){
        outputFile << r << "\n";
    }
    outputFile << numberOfSupportVectors.size() << "\n";
    for (int s : numberOfSupportVectors){
        outputFile << s << "\n";
    }
    outputFile << supportVectors.size() << "\n";
    for (NodeList nodeList : supportVectors){
        nodeList.serialize(outputFile);
    }
    outputFile << supportVectorCoefficients.size() << "\n";
    for (const vector<double> &svc : supportVectorCoefficients){
        outputFile << svc.size() << "\n";
        for (double value : svc){
            outputFile << value << "\n";
        }
    }
}

SvmModel::SvmModel(ifstream &inputFile) {
    int size, s, size2;
    double r, value;
    inputFile >> numberOfClasses;
    inputFile >> numberOfProblems;
    classDistribution = DiscreteDistribution(inputFile);
    inputFile >> size;
    for (int i = 0; i < size; i++){
        inputFile >> r;
        rho.push_back(r);
    }
    inputFile >> size;
    for (int i = 0; i < size; i++){
        inputFile >> s;
        numberOfSupportVectors.push_back(s);
    }
    inputFile >> size;
    for (int i = 0; i < size; i++){
        NodeList nodeList = NodeList(inputFile);
        supportVectors.push_back(nodeList);
    }
    inputFile >> size;
    for (int i = 0; i < size; i++){
        inputFile >> size2;
        vector<double> svc;
        for (int j = 0; j < size2; j++){
            inputFile >> value;
            svc.push_back(value);
        }
        supportVectorCoefficients.push_back(svc);
    }
}
