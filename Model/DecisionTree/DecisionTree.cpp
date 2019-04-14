//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#include "DecisionTree.h"
#include "../../Instance/CompositeInstance.h"

/**
 * The predict method  performs prediction on the root node of given instance, and if it is null, it returns the possible class labels.
 * Otherwise it returns the returned class labels.
 *
 * @param instance Instance make prediction.
 * @return Possible class labels.
 */
string DecisionTree::predict(Instance *instance) {
    string predictedClass = root.predict(instance);
    if (predictedClass == "" && instance->isComposite()) {
        predictedClass = ((CompositeInstance*) instance)->getPossibleClassLabels().at(0);
    }
    return predictedClass;
}

/**
 * Constructor that sets root node of the decision tree.
 *
 * @param root DecisionNode type input.
 */
DecisionTree::DecisionTree(DecisionNode root) {
    this->root = root;
}

/**
 * The prune method takes an {@link InstanceList} and  performs pruning to the root node.
 *
 * @param pruneSet {@link InstanceList} to perform pruning.
 */
void DecisionTree::prune(InstanceList pruneSet) {
    pruneNode(root, pruneSet);
}

/**
 * The prune method takes a {@link DecisionNode} and an {@link InstanceList} as inputs. It checks the classification performance
 * of given InstanceList before pruning, i.e making a node leaf, and after pruning. If the after performance is better than the
 * before performance it prune the given InstanceList from the tree.
 *
 * @param tree     DecisionTree that will be pruned if conditions hold.
 * @param pruneSet Small subset of tree that will be removed from tree.
 */
void DecisionTree::pruneNode(DecisionNode decisionNode, InstanceList pruneSet) {
    if (decisionNode.isLeaf())
        return;
    ClassificationPerformance* before = testClassifier(pruneSet);
    decisionNode.setLeaf(true);
    ClassificationPerformance* after = testClassifier(pruneSet);
    if (after->getAccuracy() < before->getAccuracy()) {
        decisionNode.setLeaf(false);
        for (DecisionNode node : decisionNode.getChildren()) {
            pruneNode(node, pruneSet);
        }
    }
}

void DecisionTree::serialize(ostream &outputFile) {

}
