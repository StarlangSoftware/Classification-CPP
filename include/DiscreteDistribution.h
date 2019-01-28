//
// Created by Olcay Taner Yıldız on 30.11.2018.
//

#ifndef MATH_DISCRETEDISTRIBUTION_H
#define MATH_DISCRETEDISTRIBUTION_H
#include <map>
using namespace std;

class DiscreteDistribution : public map<string, int>{
private:
    double sum = 0;
public:
    DiscreteDistribution();
    void addItem(string item);
    void removeItem(string item);
    void addDistribution(DiscreteDistribution distribution);
    void removeDistribution(DiscreteDistribution distribution);
    double getSum();
    bool containsItem(string item);
    int getCount(string item);
    string getMaxItem();
    string getMaxItem(vector<string> includeTheseOnly);
    double getProbability(string item);
    double getProbabilityLaplaceSmoothing(string item);
    double entropy();
};


#endif //MATH_DISCRETEDISTRIBUTION_H
