//
// Created by Olcay Taner YILDIZ on 10.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/Dummy.h"

TEST_CASE("DummyTest-testTrain") {
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
    Dummy dummy = Dummy();
    InstanceList instanceList = iris.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(66.67, Catch::Matchers::WithinAbs(100 * dummy.test(iris.getInstanceList())->getErrorRate(), 0.01));
    instanceList = bupa.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(42.03, Catch::Matchers::WithinAbs(100 * dummy.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    instanceList = dermatology.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(69.40, Catch::Matchers::WithinAbs(100 * dummy.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    instanceList = car.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(29.98, Catch::Matchers::WithinAbs(100 * dummy.test(car.getInstanceList())->getErrorRate(), 0.01));
    instanceList = tictactoe.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(34.66, Catch::Matchers::WithinAbs(100 * dummy.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
    instanceList = nursery.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(66.67, Catch::Matchers::WithinAbs(100 * dummy.test(nursery.getInstanceList())->getErrorRate(), 0.01));
    instanceList = chess.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(83.77, Catch::Matchers::WithinAbs(100 * dummy.test(chess.getInstanceList())->getErrorRate(), 0.01));
}