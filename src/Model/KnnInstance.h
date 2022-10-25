//
// Created by Olcay Taner Yıldız on 10.02.2019.
//

#ifndef CLASSIFICATION_KNNINSTANCE_H
#define CLASSIFICATION_KNNINSTANCE_H
#include "../Instance/Instance.h"

class KnnInstance {
private:
    double distance;
    Instance* instance;
public:
    KnnInstance(Instance* instance, double distance);
    string to_string() const;
    double getDistance() const;
    Instance* getInstance() const;
};


#endif //CLASSIFICATION_KNNINSTANCE_H
