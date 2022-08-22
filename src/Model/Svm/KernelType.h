//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#ifndef CLASSIFICATION_KERNELTYPE_H
#define CLASSIFICATION_KERNELTYPE_H


enum class KernelType {
    /**
     * Linear Kernel.
     */
            LINEAR,
    /**
     * Polynomial Kernel.
     */
            POLYNOM,
    /**
     * Gaussian radial basis function Kernel.
     */
            RBF,
    /**
     * Sigmoid Kernel.
     */
            SIGMOID
};


#endif //CLASSIFICATION_KERNELTYPE_H
