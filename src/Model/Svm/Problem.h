//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#ifndef CLASSIFICATION_PROBLEM_H
#define CLASSIFICATION_PROBLEM_H
#include <vector>
#include "NodeList.h"
#include "../../InstanceList/InstanceList.h"

using namespace std;

class Problem {
private:
    int l;
    vector<double> y;
    vector<NodeList> x;
public:
    Problem(vector<NodeList> x, vector<double> y);
    explicit Problem(InstanceList& instanceList);
    int getL();
    vector<NodeList> getX();
    vector<double> getY();
};


#endif //CLASSIFICATION_PROBLEM_H
