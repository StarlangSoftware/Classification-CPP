//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#ifndef CLASSIFICATION_KERNEL_H
#define CLASSIFICATION_KERNEL_H
#include <vector>
#include "NodeList.h"
#include "KernelType.h"
#include "../../Parameter/SvmParameter.h"

using namespace std;

class Kernel {
private:
    vector<NodeList> x;
    vector<double> xSquare;
    KernelType kernelType;
    int degree;
    double gamma;
    double coefficient0;
    double linear(int i, int j);
    double polynom(int i, int j);
    double rbf(int i, int j);
    double sigmoid(int i, int j);
public:
    Kernel(int l, vector<NodeList> x, KernelType kernelType, int degree, double gamma, double coefficient0);
    Kernel();
    void swapIndex(int i, int j);
    double function(int i, int j);
    static double function(NodeList x, NodeList y, SvmParameter* parameter);
};


#endif //CLASSIFICATION_KERNEL_H
