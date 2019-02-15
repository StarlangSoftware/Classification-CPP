//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#include "Problem.h"

/**
 * A constructor that sets x, y and l with given inputs.
 *
 * @param x NodeList array.
 * @param y Double array.
 */
Problem::Problem(vector<NodeList> x, vector<double> y) {
    this->x = move(x);
    this->y = y;
    this->l = y.size();
}

/**
 * A constructor that takes an {@link InstanceList} as an input and sets l, x, and y from that InstanceList.
 *
 * @param instanceList InstanceList to use.
 */
Problem::Problem(InstanceList &instanceList) {
    Instance* instance;
    l = instanceList.size();
    for (int i = 0; i < instanceList.size(); i++) {
        instance = instanceList.get(i);
        x[i] = instance->toNodeList();
    }
}

/**
 * Accessor for l.
 *
 * @return L.
 */
int Problem::getL() {
    return l;
}

/**
 * Accessor for NodeList array x.
 *
 * @return x.
 */
vector<NodeList> Problem::getX() {
    return x;
}

/**
 * Accessor for double array y.
 *
 * @return y.
 */
vector<double> Problem::getY() {
    return y;
}
