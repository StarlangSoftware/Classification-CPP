//
// Created by Olcay Taner YILDIZ on 10.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Parameter/C45Parameter.h"
#include "../src/Model/DecisionTree//DecisionTree.h"

TEST_CASE("C45Test") {
    DataSet iris, car, chess, bupa, tictactoe, dermatology, nursery, carIndexed, tictactoeIndexed;
    vector<AttributeType> attributeTypes;
    vector<vector<string>> attributeValueList;
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
    for (int i = 0; i < 6; i++) {
        attributeTypes.emplace_back(AttributeType::DISCRETE_INDEXED);
    }
    attributeValueList.clear();
    attributeValueList.push_back({"vhigh", "high", "low", "med"});
    attributeValueList.push_back({"vhigh", "high", "low", "med"});
    attributeValueList.push_back({"2", "3", "4", "5more"});
    attributeValueList.push_back({"2", "4", "more"});
    attributeValueList.push_back({"big", "med", "small"});
    attributeValueList.push_back({"high", "low", "med"});
    dataDefinition = DataDefinition(attributeTypes, attributeValueList);
    carIndexed = DataSet(dataDefinition, ",", "datasets/car.data");
    attributeTypes.clear();
    for (int i = 0; i < 9; i++) {
        attributeTypes.emplace_back(AttributeType::DISCRETE);
    }
    dataDefinition = DataDefinition(attributeTypes);
    tictactoe = DataSet(dataDefinition, ",", "datasets/tictactoe.data");
    attributeTypes.clear();
    attributeValueList.clear();
    for (int i = 0; i < 9; i++) {
        attributeTypes.emplace_back(AttributeType::DISCRETE_INDEXED);
        attributeValueList.push_back({"b", "o", "x"});
    }
    dataDefinition = DataDefinition(attributeTypes, attributeValueList);
    tictactoeIndexed = DataSet(dataDefinition, ",", "datasets/tictactoe.data");
    auto* c45Parameter = new C45Parameter(1, true, 0.2);
    SECTION("train"){
        DecisionTree c45 = DecisionTree();
        InstanceList instanceList = iris.getInstanceList();
        c45.train(instanceList, c45Parameter);
        REQUIRE_THAT(4.0, Catch::Matchers::WithinAbs(100 * c45.test(iris.getInstanceList())->getErrorRate(), 0.01));
        c45 = DecisionTree();
        instanceList = bupa.getInstanceList();
        c45.train(instanceList, c45Parameter);
        REQUIRE_THAT(22.60, Catch::Matchers::WithinAbs(100 * c45.test(bupa.getInstanceList())->getErrorRate(), 0.01));
        c45 = DecisionTree();
        instanceList = dermatology.getInstanceList();
        c45.train(instanceList, c45Parameter);
        REQUIRE_THAT(5.19, Catch::Matchers::WithinAbs(100 * c45.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
        c45 = DecisionTree();
        instanceList = car.getInstanceList();
        c45.train(instanceList, c45Parameter);
        REQUIRE_THAT(6.65, Catch::Matchers::WithinAbs(100 * c45.test(car.getInstanceList())->getErrorRate(), 0.01));
        c45 = DecisionTree();
        instanceList = tictactoe.getInstanceList();
        c45.train(instanceList, c45Parameter);
        REQUIRE_THAT(15.34, Catch::Matchers::WithinAbs(100 * c45.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
    }
    SECTION("load"){
        DecisionTree c45 = DecisionTree();
        c45.loadModel("models/c45-iris.txt");
        REQUIRE_THAT(4.00, Catch::Matchers::WithinAbs(100 * c45.test(iris.getInstanceList())->getErrorRate(), 0.01));
        c45 = DecisionTree();
        c45.loadModel("models/c45-bupa.txt");
        REQUIRE_THAT(42.03, Catch::Matchers::WithinAbs(100 * c45.test(bupa.getInstanceList())->getErrorRate(), 0.01));
        c45 = DecisionTree();
        c45.loadModel("models/c45-dermatology.txt");
        REQUIRE_THAT(2.19, Catch::Matchers::WithinAbs(100 * c45.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
        c45 = DecisionTree();
        c45.loadModel("models/c45-car.txt");
        REQUIRE_THAT(8.16, Catch::Matchers::WithinAbs(100 * c45.test(car.getInstanceList())->getErrorRate(), 0.01));
        c45 = DecisionTree();
        c45.loadModel("models/c45-carIndexed.txt");
        REQUIRE_THAT(3.36, Catch::Matchers::WithinAbs(100 * c45.test(carIndexed.getInstanceList())->getErrorRate(), 0.01));
        c45 = DecisionTree();
        c45.loadModel("models/c45-tictactoe.txt");
        REQUIRE_THAT(14.61, Catch::Matchers::WithinAbs(100 * c45.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
        c45 = DecisionTree();
        c45.loadModel("models/c45-tictactoeIndexed.txt");
        REQUIRE_THAT(4.49, Catch::Matchers::WithinAbs(100 * c45.test(tictactoeIndexed.getInstanceList())->getErrorRate(), 0.01));
    }
}