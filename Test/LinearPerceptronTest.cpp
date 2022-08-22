//
// Created by Olcay Taner YILDIZ on 11.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/LinearPerceptron.h"
#include "../src/Parameter/LinearPerceptronParameter.h"

TEST_CASE("LinearPerceptronTest-testTrain") {
    DataSet iris, bupa, dermatology;
    vector<AttributeType> attributeTypes;
    for (int i = 0; i < 4; i++) {
        attributeTypes.emplace_back(AttributeType::CONTINUOUS);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    iris = DataSet(dataDefinition, ",", "iris.data");
    attributeTypes.clear();
    for (int i = 0; i < 6; i++) {
        attributeTypes.emplace_back(AttributeType::CONTINUOUS);
    }
    dataDefinition = DataDefinition(attributeTypes);
    bupa = DataSet(dataDefinition, ",", "bupa.data");
    attributeTypes.clear();
    for (int i = 0; i < 34; i++) {
        attributeTypes.emplace_back(AttributeType::CONTINUOUS);
    }
    dataDefinition = DataDefinition(attributeTypes);
    dermatology = DataSet(dataDefinition, ",", "dermatology.data");
    LinearPerceptron linearPerceptron = LinearPerceptron();
    InstanceList instanceList = iris.getInstanceList();
    auto* linearPerceptronParameter = new LinearPerceptronParameter(1, 0.1, 0.99, 0.2, 100);
    linearPerceptron.train(instanceList, linearPerceptronParameter);
    REQUIRE_THAT(2.67, Catch::Matchers::WithinAbs(100 * linearPerceptron.test(iris.getInstanceList())->getErrorRate(), 0.01));
    instanceList = bupa.getInstanceList();
    linearPerceptronParameter = new LinearPerceptronParameter(1, 0.001, 0.99, 0.2, 100);
    linearPerceptron.train(instanceList, linearPerceptronParameter);
    REQUIRE_THAT(26.96, Catch::Matchers::WithinAbs(100 * linearPerceptron.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    instanceList = dermatology.getInstanceList();
    linearPerceptronParameter = new LinearPerceptronParameter(1, 0.1, 0.99, 0.2, 100);
    linearPerceptron.train(instanceList, linearPerceptronParameter);
    REQUIRE_THAT(3.55, Catch::Matchers::WithinAbs(100 * linearPerceptron.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
}