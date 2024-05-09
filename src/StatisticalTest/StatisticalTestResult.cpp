//
// Created by olcay on 31.01.2019.
//

#include "StatisticalTestResult.h"
#include "StatisticalTestNotApplicable.h"

/**
 * Constructor of the StatisticalTestResult. It sets the attribute values.
 * @param pValue p value of the statistical test result
 * @param onlyTwoTailed True, if this test applicable only two tailed tests, false otherwise.
 */
StatisticalTestResult::StatisticalTestResult(double pValue, bool onlyTwoTailed) {
    this->pValue = pValue;
    this->onlyTwoTailed = onlyTwoTailed;
}

/**
 * Returns reject or failed to reject, depending on the alpha level and p value of the statistical test that checks
 * one tailed null hypothesis such as mu1 < mu2. If p value is less than the alpha level, the test rejects the null
 * hypothesis. Otherwise, it fails to reject the null hypothesis.
 * @param alpha Alpha level of the test
 * @return If p value is less than the alpha level, the test rejects the null hypothesis. Otherwise, it fails to
 * reject the null hypothesis.
 */
StatisticalTestResultType StatisticalTestResult::oneTailed(double alpha) const{
    if (onlyTwoTailed){
        throw StatisticalTestNotApplicable("The test", "One tailed option is not available for this test. The distribution is one tailed distribution.");
    }
    if (pValue < alpha){
        return StatisticalTestResultType::REJECT;
    } else {
        return StatisticalTestResultType::FAILED_TO_REJECT;
    }
}

/**
 * Returns reject or failed to reject, depending on the alpha level and p value of the statistical test that checks
 * one tailed null hypothesis such as mu1 < mu2 or two tailed null hypothesis such as mu1 = mu2. If the null
 * hypothesis is two tailed, and p value is less than the alpha level, the test rejects the null hypothesis.
 * Otherwise, it fails to reject the null hypothesis. If the null  hypothesis is one tailed, and p value is less
 * than alpha / 2 or p value is larger than 1 - alpha / 2, the test  rejects the null  hypothesis. Otherwise, it
 * fails to reject the null hypothesis.
 * @param alpha Alpha level of the test
 * @return If the null  hypothesis is two tailed, and p value is less than the alpha level, the test rejects the
 * null hypothesis.  Otherwise, it fails to reject the null hypothesis. If the null  hypothesis is one tailed, and
 * p value is less  than alpha / 2 or p value is larger than 1 - alpha / 2, the test  rejects the null  hypothesis.
 * Otherwise, it  fails to reject the null hypothesis.
 */
StatisticalTestResultType StatisticalTestResult::twoTailed(double alpha) const{
    if (onlyTwoTailed){
        if (pValue < alpha){
            return StatisticalTestResultType::REJECT;
        } else {
            return StatisticalTestResultType::FAILED_TO_REJECT;
        }
    } else {
        if (pValue < alpha / 2 || pValue > 1 - alpha / 2){
            return StatisticalTestResultType::REJECT;
        } else {
            return StatisticalTestResultType::FAILED_TO_REJECT;
        }
    }
}

/**
 * Accessor for the p value of the statistical test result.
 * @return p value of the statistical test result
 */
double StatisticalTestResult::getPValue() const{
    return pValue;
}
