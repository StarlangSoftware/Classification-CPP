//
// Created by Olcay Taner Yıldız on 15.02.2019.
//

#ifndef CLASSIFICATION_ALPHASTATUSTYPE_H
#define CLASSIFICATION_ALPHASTATUSTYPE_H


enum class AlphaStatusType {
    /**
     * Lower bound value of Alpha.
     */
            LOWER_BOUND,
    /**
     * Upper bound value of Alpha.
     */
            UPPER_BOUND,
    /**
     * Free value of Alpha.
     */
            FREE
};


#endif //CLASSIFICATION_ALPHASTATUSTYPE_H
