//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#include <fstream>
#include "NodeList.h"

/**
 * Constructor that Creates an ArrayList of Nodes and initialize with the given values.
 *
 * @param values An ArrayList of values of nodes.
 */
NodeList::NodeList(vector<double> values) {
    for (int i = 0; i < values.size(); i++) {
        if (values.at(i) != 0) {
            nodes.emplace_back(Node(i, values.at(i)));
        }
    }
}

/**
 * An empty constructor.
 */
NodeList::NodeList() = default;

/**
 * The clone method creates a new {@link NodeList} and as the clone of the initial {@link NodeList}.
 *
 * @return A clone of the {@link NodeList}.
 */
NodeList NodeList::clone() {
    NodeList result = NodeList();
    for (auto &node : nodes) {
        result.nodes.emplace_back(node.clone());
    }
    return result;
}

/**
 * The dot method takes a {@link NodeList} as an input and returns the dot product of given {@link NodeList}
 * and initial NodeList.
 *
 * @param nodeList NodeList to find the dot product.
 * @return Dot product.
 */
double NodeList::dot(NodeList nodeList) {
    double sum = 0;
    int px = 0, py = 0;
    while (px < nodes.size() && py < nodeList.nodes.size()) {
        if (nodes.at(px).getIndex() == nodeList.nodes.at(py).getIndex()) {
            sum += nodes.at(px).getValue() * nodeList.nodes.at(py).getValue();
            px++;
            py++;
        } else {
            if (nodes.at(px).getIndex() > nodeList.nodes.at(py).getIndex()) {
                py++;
            } else {
                px++;
            }
        }
    }
    return sum;
}

/**
 * The get method returns the Node at given index.
 *
 * @param index Index to find a Node of the NodeList.
 * @return The Node at given index.
 */
Node NodeList::get(int index) {
    return nodes.at(index);
}

/**
 * The size method returns the size of the NodeList.
 *
 * @return The size of the NodeList.
 */
int NodeList::size() {
    return nodes.size();
}

void NodeList::serialize(ostream &outputFile) {
    outputFile << nodes.size() << "\n";
    for (Node node : nodes){
        node.serialize(outputFile);
    }
}

NodeList::NodeList(ifstream &inputFile) {
    int size;
    inputFile >> size;
    for (int i = 0; i < size; i++){
        Node node = Node(inputFile);
        nodes.push_back(node);
    }
}
