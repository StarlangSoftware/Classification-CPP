//
// Created by Olcay Taner Yıldız on 9.02.2019.
//

#include "ValidatedModel.h"

/**
 * The testClassifier method takes an InstanceList as an input and returns an accuracy value as ClassificationPerformance.
 *
 * @param data InstanceList to test.
 * @return Accuracy value as ClassificationPerformance.
 */
ClassificationPerformance *ValidatedModel::testClassifier(InstanceList data) {
    double total = data.size();
    int count = 0;
    for (int i = 0; i < data.size(); i++) {
        if (data.get(i)->getClassLabel() == predict(data.get(i))) {
            count++;
        }
    }
    return new ClassificationPerformance(count / total);
}

void ValidatedModel::serialize(ostream &outputFile) {
}
