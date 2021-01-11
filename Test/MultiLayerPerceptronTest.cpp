//
// Created by Olcay Taner YILDIZ on 11.01.2021.
//

#include "catch.hpp"
#include "../DataSet/DataSet.h"
#include "../Classifier/MultiLayerPerceptron.h"
#include "../Parameter/MultiLayerPerceptronParameter.h"

TEST_CASE("MultiLayerPerceptronTest-testTrain") {
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
    MultiLayerPerceptron multiLayerPerceptron = MultiLayerPerceptron();
    InstanceList instanceList = iris.getInstanceList();
    MultiLayerPerceptronParameter* multiLayerPerceptronParameter = new MultiLayerPerceptronParameter(1, 0.1, 0.99, 0.2, 100, 3);
    multiLayerPerceptron.train(instanceList, multiLayerPerceptronParameter);
    REQUIRE_THAT(3.33, Catch::Matchers::WithinAbs(100 * multiLayerPerceptron.test(iris.getInstanceList())->getErrorRate(), 0.01));
    instanceList = bupa.getInstanceList();
    multiLayerPerceptronParameter = new MultiLayerPerceptronParameter(1, 0.01, 0.99, 0.2, 100, 30);
    multiLayerPerceptron.train(instanceList, multiLayerPerceptronParameter);
    REQUIRE_THAT(27.83, Catch::Matchers::WithinAbs(100 * multiLayerPerceptron.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    instanceList = dermatology.getInstanceList();
    multiLayerPerceptronParameter = new MultiLayerPerceptronParameter(1, 0.01, 0.99, 0.2, 100, 20);
    multiLayerPerceptron.train(instanceList, multiLayerPerceptronParameter);
    REQUIRE_THAT(2.46, Catch::Matchers::WithinAbs(100 * multiLayerPerceptron.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
}