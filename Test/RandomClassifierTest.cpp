//
// Created by Olcay Taner YILDIZ on 10.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/RandomClassifier.h"

TEST_CASE("RandomClassifierTest-testTrain") {
    DataSet iris, car, chess, bupa, tictactoe, dermatology, nursery;
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
    attributeTypes.clear();
    for (int i = 0; i < 8; i++) {
        attributeTypes.emplace_back(AttributeType::DISCRETE);
    }
    dataDefinition = DataDefinition(attributeTypes);
    nursery = DataSet(dataDefinition, ",", "nursery.data");
    attributeTypes.clear();
    for (int i = 0; i < 6; i++) {
        if (i % 2 == 0) {
            attributeTypes.emplace_back(AttributeType::DISCRETE);
        } else {
            attributeTypes.emplace_back(AttributeType::CONTINUOUS);
        }
    }
    dataDefinition = DataDefinition(attributeTypes);
    chess = DataSet(dataDefinition, ",", "chess.data");
    RandomClassifier randomClassifier = RandomClassifier();
    InstanceList instanceList = iris.getInstanceList();
    Parameter* parameter = new Parameter(1);
    randomClassifier.train(instanceList, parameter);
    REQUIRE_THAT(69.33, Catch::Matchers::WithinAbs(100 * randomClassifier.test(iris.getInstanceList())->getErrorRate(), 0.01));
    instanceList = bupa.getInstanceList();
    randomClassifier.train(instanceList, parameter);
    REQUIRE_THAT(49.27, Catch::Matchers::WithinAbs(100 * randomClassifier.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    instanceList = dermatology.getInstanceList();
    randomClassifier.train(instanceList, parameter);
    REQUIRE_THAT(83.61, Catch::Matchers::WithinAbs(100 * randomClassifier.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    instanceList = car.getInstanceList();
    randomClassifier.train(instanceList, parameter);
    REQUIRE_THAT(75.46, Catch::Matchers::WithinAbs(100 * randomClassifier.test(car.getInstanceList())->getErrorRate(), 0.01));
    instanceList = tictactoe.getInstanceList();
    randomClassifier.train(instanceList, parameter);
    REQUIRE_THAT(53.24, Catch::Matchers::WithinAbs(100 * randomClassifier.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
    instanceList = nursery.getInstanceList();
    randomClassifier.train(instanceList, parameter);
    REQUIRE_THAT(80.05, Catch::Matchers::WithinAbs(100 * randomClassifier.test(nursery.getInstanceList())->getErrorRate(), 0.01));
    instanceList = chess.getInstanceList();
    randomClassifier.train(instanceList, parameter);
    REQUIRE_THAT(94.43, Catch::Matchers::WithinAbs(100 * randomClassifier.test(chess.getInstanceList())->getErrorRate(), 0.01));
}