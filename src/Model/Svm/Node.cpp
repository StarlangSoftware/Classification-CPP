//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#include <fstream>
#include "Node.h"

/**
 * Constructor that sets the value of index and value.
 *
 * @param index Index of the node.
 * @param value Value of the node.
 */
Node::Node(int index, double value) {
    this->index = index;
    this->value = value;
}

/**
 * The clone method creates a new Node as a clone.
 *
 * @return New Node.
 */
Node Node::clone() const{
    return Node(index, value);
}

/**
 * The getIndex method returns the index of a Node.
 *
 * @return The index of a Node.
 */
int Node::getIndex() const{
    return index;
}

/**
 * The getValue method returns the value of a Node.
 *
 * @return The value of a Node.
 */
double Node::getValue() const{
    return value;
}

void Node::serialize(ostream &outputFile) {
    outputFile << index << "\n";
    outputFile << value << "\n";
}

Node::Node(ifstream &inputFile) {
    inputFile >> index;
    inputFile >> value;
}
