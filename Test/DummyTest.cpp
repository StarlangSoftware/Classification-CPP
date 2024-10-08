//
// Created by Olcay Taner YILDIZ on 10.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Model/DummyModel.h"

TEST_CASE("DummyTest-testTrain") {
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
    DummyModel dummy = DummyModel();
    InstanceList instanceList = iris.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(66.67, Catch::Matchers::WithinAbs(100 * dummy.test(iris.getInstanceList())->getErrorRate(), 0.01));
    dummy = DummyModel();
    instanceList = bupa.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(42.03, Catch::Matchers::WithinAbs(100 * dummy.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    dummy = DummyModel();
    instanceList = dermatology.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(69.40, Catch::Matchers::WithinAbs(100 * dummy.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    dummy = DummyModel();
    instanceList = car.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(29.98, Catch::Matchers::WithinAbs(100 * dummy.test(car.getInstanceList())->getErrorRate(), 0.01));
    dummy = DummyModel();
    instanceList = tictactoe.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(34.66, Catch::Matchers::WithinAbs(100 * dummy.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
    dummy = DummyModel();
    instanceList = nursery.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(66.67, Catch::Matchers::WithinAbs(100 * dummy.test(nursery.getInstanceList())->getErrorRate(), 0.01));
    dummy = DummyModel();
    instanceList = chess.getInstanceList();
    dummy.train(instanceList, nullptr);
    REQUIRE_THAT(83.77, Catch::Matchers::WithinAbs(100 * dummy.test(chess.getInstanceList())->getErrorRate(), 0.01));
}