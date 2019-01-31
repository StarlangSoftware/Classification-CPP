//
// Created by Olcay Taner Yıldız on 26.11.2018.
//

#ifndef MATH_DISTRIBUTION_H
#define MATH_DISTRIBUTION_H


class Distribution {
    constexpr static double Z_MAX = 6.0;
    constexpr static double Z_EPSILON = 0.000001;
    constexpr static double CHI_EPSILON = 0.000001;
    constexpr static double CHI_MAX = 99999.0;
    constexpr static double LOG_SQRT_PI = 0.5723649429247000870717135;
    constexpr static double I_SQRT_PI = 0.5641895835477562869480795;
    constexpr static double BIGX = 200.0;
    constexpr static double I_PI = 0.3183098861837906715377675;
    constexpr static double F_EPSILON = 0.000001;
    constexpr static double F_MAX = 9999.0;
private:
    static double ex(double x);
public:
    static double beta(double* x, int size);
    static double gammaLn(double x);
    static double zNormal(double z);
    static double zInverse(double p);
    static double chiSquare(double x, int freedom);
    static double chiSquareInverse(double p, int freedom);
    static double fDistribution(double F, int freedom1, int freedom2);
    static double fDistributionInverse(double p, int freedom1, int freedom2);
    static double tDistribution(double T, int freedom);
    static double tDistributionInverse(double p, int freedom);
};


#endif //MATH_DISTRIBUTION_H
