//
// Created by Olcay Taner Yıldız on 16.02.2019.
//

#include <fstream>
#include "DecisionTree.h"
#include "../../Instance/CompositeInstance.h"
#include "../../Model/DecisionTree/DecisionTree.h"
#include "../../Parameter/C45Parameter.h"
#include "../../InstanceList/Partition.h"

DecisionTree::~DecisionTree() {
    delete root;
}

/**
 * The predict method  performs prediction on the root node of given instance, and if it is null, it returns the possible class labels.
 * Otherwise it returns the returned class labels.
 *
 * @param instance Instance make prediction.
 * @return Possible class labels.
 */
string DecisionTree::predict(Instance *instance){
    string predictedClass = root->predict(instance);
    if (predictedClass.empty() && instance->isComposite()) {
        predictedClass = ((CompositeInstance*) instance)->getPossibleClassLabels().at(0);
    }
    return predictedClass;
}

/**
 * Constructor that sets root node of the decision tree.
 *
 * @param root DecisionNode type input.
 */
DecisionTree::DecisionTree(DecisionNode* root) {
    this->root = root;
}

/**
 * The prune method takes an InstanceList and  performs pruning to the root node.
 *
 * @param pruneSet InstanceList to perform pruning.
 */
void DecisionTree::prune(const InstanceList& pruneSet) {
    pruneNode(root, pruneSet);
}

/**
 * The prune method takes a DecisionNode and an InstanceList as inputs. It checks the classification performance
 * of given InstanceList before pruning, i.e making a node leaf, and after pruning. If the after performance is better than the
 * before performance it prune the given InstanceList from the tree.
 *
 * @param tree     DecisionTree that will be pruned if conditions hold.
 * @param pruneSet Small subset of tree that will be removed from tree.
 */
void DecisionTree::pruneNode(DecisionNode* decisionNode, const InstanceList& pruneSet) {
    if (decisionNode->isLeaf())
        return;
    ClassificationPerformance* before = testClassifier(pruneSet);
    decisionNode->setLeaf(true);
    ClassificationPerformance* after = testClassifier(pruneSet);
    if (after->getAccuracy() < before->getAccuracy()) {
        decisionNode->setLeaf(false);
        for (DecisionNode* node : decisionNode->getChildren()) {
            pruneNode(node, pruneSet);
        }
    }
}

/**
 * Prints the decision tree to an output file
 * @param outputFile Output file
 */
void DecisionTree::serialize(ostream &outputFile) {
    root->serialize(outputFile);
}

/**
 * Reads a decision tree from an input file
 * @param inputFile Input file
 */
DecisionTree::DecisionTree(ifstream &inputFile) {
    root = new DecisionNode(inputFile);
}

/**
 * Calculates the posterior probability distribution for the given instance according to Decision tree model.
 * @param instance Instance for which posterior probability distribution is calculated.
 * @return Posterior probability distribution for the given instance.
 */
map<string, double> DecisionTree::predictProbability(Instance *instance) {
    return root->predictProbabilityDistribution(instance);
}

/**
 * Training algorithm for C4.5 univariate decision tree classifier. 20 percent of the data are left aside for pruning
 * 80 percent of the data is used for constructing the tree.
 *
 * @param trainSet   Training data given to the algorithm.
 * @param parameters -
 */
void DecisionTree::train(InstanceList &trainSet, Parameter *parameters) {
    DecisionTree* tree;
    if (((C45Parameter*) parameters)->isPrune()) {
        Partition partition = Partition(trainSet, ((C45Parameter*) parameters)->getCrossValidationRatio(), parameters->getSeed(), true);
        root = new DecisionNode(*(partition.get(1)), DecisionCondition(), nullptr, false);
        prune(*(partition.get(0)));
    } else {
        root = new DecisionNode(trainSet, DecisionCondition(), nullptr, false);
    }
}

/**
 * Loads the decision tree model from an input file.
 * @param fileName File name of the decision tree model.
 */
void DecisionTree::loadModel(const string &fileName) {
    ifstream inputFile;
    inputFile.open(fileName, ifstream :: in);
    root = new DecisionNode(inputFile);
    inputFile.close();
}
