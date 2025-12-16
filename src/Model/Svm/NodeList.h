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
    explicit NodeList(const vector<double>& values);
    NodeList();
    [[nodiscard]] NodeList clone() const;
    [[nodiscard]] double dot(const NodeList& nodeList) const;
    [[nodiscard]] Node get(int index) const;
    [[nodiscard]] int size() const;
    void serialize(ostream &outputFile);
};


#endif //CLASSIFICATION_NODELIST_H
