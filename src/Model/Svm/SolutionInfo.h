//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#ifndef CLASSIFICATION_SOLUTIONINFO_H
#define CLASSIFICATION_SOLUTIONINFO_H

#include <vector>
using namespace std;

class SolutionInfo {
private:
    double rho;
    vector<double> alpha;
public:
    SolutionInfo(double rho, const vector<double>& alpha);
    [[nodiscard]] double getRho() const;
    [[nodiscard]] double getAlpha(int index) const;
    void setAlpha(int index, double value);
};


#endif //CLASSIFICATION_SOLUTIONINFO_H
