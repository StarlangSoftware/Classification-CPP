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
    Problem(const vector<NodeList>& x, const vector<double>& y);
    explicit Problem(const InstanceList& instanceList);
    [[nodiscard]] int getL() const;
    [[nodiscard]] vector<NodeList> getX() const;
    [[nodiscard]] vector<double> getY() const;
};


#endif //CLASSIFICATION_PROBLEM_H
