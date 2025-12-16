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
    [[nodiscard]] Node clone() const;
    [[nodiscard]] int getIndex() const;
    [[nodiscard]] double getValue() const;
    void serialize(ostream &outputFile);
};


#endif //CLASSIFICATION_NODE_H
