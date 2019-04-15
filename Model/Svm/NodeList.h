//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#ifndef CLASSIFICATION_NODELIST_H
#define CLASSIFICATION_NODELIST_H

#include <vector>
#include "Node.h"
using namespace std;

class NodeList {
private:
    vector<Node> nodes;
public:
    explicit NodeList(ifstream& inputFile);
    explicit NodeList(vector<double> values);
    NodeList();
    NodeList clone();
    double dot(NodeList nodeList);
    Node get(int index);
    int size();
    void serialize(ostream &outputFile);
};


#endif //CLASSIFICATION_NODELIST_H
