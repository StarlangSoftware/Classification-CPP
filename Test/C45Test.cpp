//
// Created by Olcay Taner YILDIZ on 10.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/C45.h"
#include "../src/Parameter/C45Parameter.h"

TEST_CASE("C45Test-testTrain") {
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
    C45 c45 = C45();
    C45Parameter* c45Parameter = new C45Parameter(1, true, 0.2);
    InstanceList instanceList = iris.getInstanceList();
    c45.train(instanceList, c45Parameter);
    REQUIRE_THAT(4.00, Catch::Matchers::WithinAbs(100 * c45.test(iris.getInstanceList())->getErrorRate(), 0.01));
    instanceList = bupa.getInstanceList();
    c45.train(instanceList, c45Parameter);
    REQUIRE_THAT(42.03, Catch::Matchers::WithinAbs(100 * c45.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    instanceList = dermatology.getInstanceList();
    c45.train(instanceList, c45Parameter);
    REQUIRE_THAT(14.75, Catch::Matchers::WithinAbs(100 * c45.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    instanceList = car.getInstanceList();
    c45.train(instanceList, c45Parameter);
    REQUIRE_THAT(1.27, Catch::Matchers::WithinAbs(100 * c45.test(car.getInstanceList())->getErrorRate(), 0.01));
    instanceList = tictactoe.getInstanceList();
    c45.train(instanceList, c45Parameter);
    REQUIRE_THAT(3.24, Catch::Matchers::WithinAbs(100 * c45.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
    instanceList = nursery.getInstanceList();
    c45.train(instanceList, c45Parameter);
    REQUIRE_THAT(0.31, Catch::Matchers::WithinAbs(100 * c45.test(nursery.getInstanceList())->getErrorRate(), 0.01));
    instanceList = chess.getInstanceList();
    c45.train(instanceList, c45Parameter);
    REQUIRE_THAT(47.59, Catch::Matchers::WithinAbs(100 * c45.test(chess.getInstanceList())->getErrorRate(), 0.01));
}