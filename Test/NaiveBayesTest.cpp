//
// Created by Olcay Taner YILDIZ on 10.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/NaiveBayes.h"

TEST_CASE("NaiveBayesTest-testTrain") {
    DataSet iris, car, bupa, tictactoe, dermatology, nursery;
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
    attributeTypes.clear();
    for (int i = 0; i < 6; i++) {
        attributeTypes.emplace_back(AttributeType::DISCRETE);
    }
    dataDefinition = DataDefinition(attributeTypes);
    car = DataSet(dataDefinition, ",", "car.data");
    attributeTypes.clear();
    for (int i = 0; i < 9; i++) {
        attributeTypes.emplace_back(AttributeType::DISCRETE);
    }
    dataDefinition = DataDefinition(attributeTypes);
    tictactoe = DataSet(dataDefinition, ",", "tictactoe.data");
    NaiveBayes naiveBayes = NaiveBayes();
    InstanceList instanceList = iris.getInstanceList();
    naiveBayes.train(instanceList, nullptr);
    REQUIRE_THAT(5.33, Catch::Matchers::WithinAbs(100 * naiveBayes.test(iris.getInstanceList())->getErrorRate(), 0.01));
    instanceList = bupa.getInstanceList();
    naiveBayes.train(instanceList, nullptr);
    REQUIRE_THAT(38.55, Catch::Matchers::WithinAbs(100 * naiveBayes.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    instanceList = dermatology.getInstanceList();
    naiveBayes.train(instanceList, nullptr);
    REQUIRE_THAT(69.40, Catch::Matchers::WithinAbs(100 * naiveBayes.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    instanceList = car.getInstanceList();
    naiveBayes.train(instanceList, nullptr);
    REQUIRE_THAT(12.91, Catch::Matchers::WithinAbs(100 * naiveBayes.test(car.getInstanceList())->getErrorRate(), 0.01));
    instanceList = tictactoe.getInstanceList();
    naiveBayes.train(instanceList, nullptr);
    REQUIRE_THAT(30.17, Catch::Matchers::WithinAbs(100 * naiveBayes.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
}