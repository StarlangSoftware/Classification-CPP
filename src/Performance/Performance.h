//
// Created by olcay on 31.01.2019.
//

#ifndef CLASSIFICATION_PERFORMANCE_H
#define CLASSIFICATION_PERFORMANCE_H


class Performance {
protected:
    double errorRate;
public:
    explicit Performance(double errorRate);
    [[nodiscard]] double getErrorRate() const;
    [[nodiscard]] virtual bool containsDetails() const;
    [[nodiscard]] virtual bool isClassification() const;
};


#endif //CLASSIFICATION_PERFORMANCE_H
