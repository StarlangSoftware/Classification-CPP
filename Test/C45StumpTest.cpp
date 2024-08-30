//
// Created by Olcay Taner YILDIZ on 10.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Model/DecisionTree/DecisionStump.h"

TEST_CASE("C45StumpTest-testTrain") {
    DataSet iris, car, chess, bupa, tictactoe, dermatology, nursery;
    vector<AttributeType> attributeTypes;
    for (int i = 0; i < 4; i++) {
        attributeTypes.emplace_back(AttributeType::CONTINUOUS);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    iris = DataSet(dataDefinition, ",", "datasets/iris.data");
    attributeTypes.clear();
    for (int i = 0; i < 6; i++) {
        attributeTypes.emplace_back(AttributeType::CONTINUOUS);
    }
    dataDefinition = DataDefinition(attributeTypes);
    bupa = DataSet(dataDefinition, ",", "datasets/bupa.data");
    attributeTypes.clear();
    for (int i = 0; i < 34; i++) {
        attributeTypes.emplace_back(AttributeType::CONTINUOUS);
    }
    dataDefinition = DataDefinition(attributeTypes);
    dermatology = DataSet(dataDefinition, ",", "datasets/dermatology.data");
    attributeTypes.clear();
    for (int i = 0; i < 6; i++) {
        attributeTypes.emplace_back(AttributeType::DISCRETE);
    }
    dataDefinition = DataDefinition(attributeTypes);
    car = DataSet(dataDefinition, ",", "datasets/car.data");
    attributeTypes.clear();
    for (int i = 0; i < 9; i++) {
        attributeTypes.emplace_back(AttributeType::DISCRETE);
    }
    dataDefinition = DataDefinition(attributeTypes);
    tictactoe = DataSet(dataDefinition, ",", "datasets/tictactoe.data");
    attributeTypes.clear();
    for (int i = 0; i < 8; i++) {
        attributeTypes.emplace_back(AttributeType::DISCRETE);
    }
    dataDefinition = DataDefinition(attributeTypes);
    nursery = DataSet(dataDefinition, ",", "datasets/nursery.data");
    attributeTypes.clear();
    for (int i = 0; i < 6; i++) {
        if (i % 2 == 0) {
            attributeTypes.emplace_back(AttributeType::DISCRETE);
        } else {
            attributeTypes.emplace_back(AttributeType::CONTINUOUS);
        }
    }
    dataDefinition = DataDefinition(attributeTypes);
    chess = DataSet(dataDefinition, ",", "datasets/chess.data");
    DecisionStump stump = DecisionStump();
    InstanceList instanceList = iris.getInstanceList();
    stump.train(instanceList, nullptr);
    REQUIRE_THAT(33.33, Catch::Matchers::WithinAbs(100 * stump.test(iris.getInstanceList())->getErrorRate(), 0.01));
    stump = DecisionStump();
    instanceList = bupa.getInstanceList();
    stump.train(instanceList, nullptr);
    REQUIRE_THAT(36.81, Catch::Matchers::WithinAbs(100 * stump.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    stump = DecisionStump();
    instanceList = dermatology.getInstanceList();
    stump.train(instanceList, nullptr);
    REQUIRE_THAT(49.73, Catch::Matchers::WithinAbs(100 * stump.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    stump = DecisionStump();
    instanceList = car.getInstanceList();
    stump.train(instanceList, nullptr);
    REQUIRE_THAT(29.98, Catch::Matchers::WithinAbs(100 * stump.test(car.getInstanceList())->getErrorRate(), 0.01));
    stump = DecisionStump();
    instanceList = tictactoe.getInstanceList();
    stump.train(instanceList, nullptr);
    REQUIRE_THAT(30.06, Catch::Matchers::WithinAbs(100 * stump.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
    stump = DecisionStump();
    instanceList = nursery.getInstanceList();
    stump.train(instanceList, nullptr);
    REQUIRE_THAT(29.03, Catch::Matchers::WithinAbs(100 * stump.test(nursery.getInstanceList())->getErrorRate(), 0.01));
    stump = DecisionStump();
    instanceList = chess.getInstanceList();
    stump.train(instanceList, nullptr);
    REQUIRE_THAT(80.92, Catch::Matchers::WithinAbs(100 * stump.test(chess.getInstanceList())->getErrorRate(), 0.01));
}