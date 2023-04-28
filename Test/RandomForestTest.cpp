//
// Created by Olcay Taner YILDIZ on 11.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/RandomForest.h"
#include "../src/Parameter/RandomForestParameter.h"

TEST_CASE("RandomForestTest-testTrain1") {
    DataSet iris;
    vector<AttributeType> attributeTypes;
    for (int i = 0; i < 4; i++) {
        attributeTypes.emplace_back(AttributeType::CONTINUOUS);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    iris = DataSet(dataDefinition, ",", "datasets/iris.data");
    RandomForest randomForest = RandomForest();
    auto* randomForestParameter = new RandomForestParameter(1, 100, 35);
    InstanceList instanceList = iris.getInstanceList();
    randomForest.train(instanceList, randomForestParameter);
    REQUIRE_THAT(0.0, Catch::Matchers::WithinAbs(100 * randomForest.test(iris.getInstanceList())->getErrorRate(), 0.01));
}

TEST_CASE("RandomForestTest-testTrain2") {
    DataSet bupa;
    vector<AttributeType> attributeTypes;
    for (int i = 0; i < 6; i++) {
        attributeTypes.emplace_back(AttributeType::CONTINUOUS);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    bupa = DataSet(dataDefinition, ",", "datasets/bupa.data");
    RandomForest randomForest = RandomForest();
    auto* randomForestParameter = new RandomForestParameter(1, 100, 35);
    InstanceList instanceList = bupa.getInstanceList();
    randomForest.train(instanceList, randomForestParameter);
    REQUIRE_THAT(0.0, Catch::Matchers::WithinAbs(100 * randomForest.test(bupa.getInstanceList())->getErrorRate(), 0.01));
}

TEST_CASE("RandomForestTest-testTrain3") {
    DataSet dermatology;
    vector<AttributeType> attributeTypes;
    for (int i = 0; i < 34; i++) {
        attributeTypes.emplace_back(AttributeType::CONTINUOUS);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    dermatology = DataSet(dataDefinition, ",", "datasets/dermatology.data");
    RandomForest randomForest = RandomForest();
    auto* randomForestParameter = new RandomForestParameter(1, 100, 35);
    InstanceList instanceList = dermatology.getInstanceList();
    randomForest.train(instanceList, randomForestParameter);
    REQUIRE_THAT(0.0, Catch::Matchers::WithinAbs(100 * randomForest.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
}

TEST_CASE("RandomForestTest-testTrain4") {
    DataSet car;
    vector<AttributeType> attributeTypes;
    for (int i = 0; i < 6; i++) {
        attributeTypes.emplace_back(AttributeType::DISCRETE);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    car = DataSet(dataDefinition, ",", "datasets/car.data");
    RandomForest randomForest = RandomForest();
    auto* randomForestParameter = new RandomForestParameter(1, 100, 35);
    InstanceList instanceList = car.getInstanceList();
    randomForest.train(instanceList, randomForestParameter);
    REQUIRE_THAT(0.0, Catch::Matchers::WithinAbs(100 * randomForest.test(car.getInstanceList())->getErrorRate(), 0.01));
}

TEST_CASE("RandomForestTest-testTrain5") {
    DataSet tictactoe;
    vector<AttributeType> attributeTypes;
    for (int i = 0; i < 9; i++) {
        attributeTypes.emplace_back(AttributeType::DISCRETE);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    tictactoe = DataSet(dataDefinition, ",", "datasets/tictactoe.data");
    RandomForest randomForest = RandomForest();
    auto* randomForestParameter = new RandomForestParameter(1, 100, 35);
    InstanceList instanceList = tictactoe.getInstanceList();
    randomForest.train(instanceList, randomForestParameter);
    REQUIRE_THAT(0.0, Catch::Matchers::WithinAbs(100 * randomForest.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
}