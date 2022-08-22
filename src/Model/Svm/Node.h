//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#ifndef CLASSIFICATION_NODE_H
#define CLASSIFICATION_NODE_H

#include <ostream>

using namespace std;

class Node {
private:
    int index;
    double value;
public:
    explicit Node(ifstream& inputFile);
    Node(int index, double value);
    Node clone();
    int getIndex();
    double getValue();
    void serialize(ostream &outputFile);
};


#endif //CLASSIFICATION_NODE_H
