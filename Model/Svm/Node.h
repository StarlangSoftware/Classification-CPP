//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#ifndef CLASSIFICATION_NODE_H
#define CLASSIFICATION_NODE_H

class Node {
private:
    int index;
    double value;
public:
    Node(int index, double value);
    Node clone();
    int getIndex();
    double getValue();
};


#endif //CLASSIFICATION_NODE_H
