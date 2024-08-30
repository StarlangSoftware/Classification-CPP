//
// Created by Olcay Taner YILDIZ on 11.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Model/Ensemble/BaggingModel.h"

TEST_CASE("BaggingTest-testTrain") {
    DataSet iris, car, bupa, tictactoe, dermatology;
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
    BaggingModel bagging = BaggingModel();
    auto* baggingParameter = new BaggingParameter(1, 100);
    InstanceList instanceList = iris.getInstanceList();
    bagging.train(instanceList, baggingParameter);
    REQUIRE_THAT(0.0, Catch::Matchers::WithinAbs(100 * bagging.test(iris.getInstanceList())->getErrorRate(), 0.01));
    bagging = BaggingModel();
    instanceList = bupa.getInstanceList();
    bagging.train(instanceList, baggingParameter);
    REQUIRE_THAT(0.0, Catch::Matchers::WithinAbs(100 * bagging.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    bagging = BaggingModel();
    instanceList = dermatology.getInstanceList();
    bagging.train(instanceList, baggingParameter);
    REQUIRE_THAT(0.0, Catch::Matchers::WithinAbs(100 * bagging.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    bagging = BaggingModel();
    instanceList = car.getInstanceList();
    bagging.train(instanceList, baggingParameter);
    REQUIRE_THAT(0.0, Catch::Matchers::WithinAbs(100 * bagging.test(car.getInstanceList())->getErrorRate(), 0.01));
    bagging = BaggingModel();
    instanceList = tictactoe.getInstanceList();
    bagging.train(instanceList, baggingParameter);
    REQUIRE_THAT(0.0, Catch::Matchers::WithinAbs(100 * bagging.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
}