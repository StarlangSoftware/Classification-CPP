//
// Created by Olcay Taner Yıldız on 28.01.2019.
//

#ifndef CLASSIFICATION_PARAMETER_H
#define CLASSIFICATION_PARAMETER_H


class Parameter {
private:
    int seed;
public:
    explicit Parameter(int seed);
    virtual ~Parameter(){};
    int getSeed();
};


#endif //CLASSIFICATION_PARAMETER_H
