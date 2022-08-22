//
// Created by Olcay Taner YILDIZ on 11.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/RandomForest.h"
#include "../src/Parameter/RandomForestParameter.h"

TEST_CASE("RandomForestTest-testTrain") {
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
    attributeTypes.clear();
    for (int i = 0; i < 8; i++) {
        attributeTypes.emplace_back(AttributeType::DISCRETE);
    }
    dataDefinition = DataDefinition(attributeTypes);
    nursery = DataSet(dataDefinition, ",", "nursery.data");
    RandomForest randomForest = RandomForest();
    auto* randomForestParameter = new RandomForestParameter(1, 100, 35);
    InstanceList instanceList = iris.getInstanceList();
    randomForest.train(instanceList, randomForestParameter);
    REQUIRE_THAT(2.0, Catch::Matchers::WithinAbs(100 * randomForest.test(iris.getInstanceList())->getErrorRate(), 0.01));
    instanceList = bupa.getInstanceList();
    randomForest.train(instanceList, randomForestParameter);
    REQUIRE_THAT(42.03, Catch::Matchers::WithinAbs(100 * randomForest.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    instanceList = dermatology.getInstanceList();
    randomForest.train(instanceList, randomForestParameter);
    REQUIRE_THAT(2.46, Catch::Matchers::WithinAbs(100 * randomForest.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    instanceList = car.getInstanceList();
    randomForest.train(instanceList, randomForestParameter);
    REQUIRE_THAT(0.0, Catch::Matchers::WithinAbs(100 * randomForest.test(car.getInstanceList())->getErrorRate(), 0.01));
    instanceList = tictactoe.getInstanceList();
    randomForest.train(instanceList, randomForestParameter);
    REQUIRE_THAT(0.0, Catch::Matchers::WithinAbs(100 * randomForest.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
    instanceList = nursery.getInstanceList();
    randomForest.train(instanceList, randomForestParameter);
    REQUIRE_THAT(0.0, Catch::Matchers::WithinAbs(100 * randomForest.test(nursery.getInstanceList())->getErrorRate(), 0.01));
}