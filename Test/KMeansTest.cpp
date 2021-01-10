//
// Created by Olcay Taner YILDIZ on 10.01.2021.
//

#include "catch.hpp"
#include "../DataSet/DataSet.h"
#include "../Classifier/KMeans.h"
#include "../Parameter/KMeansParameter.h"

TEST_CASE("KMeansTest-testTrain") {
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
    KMeans kMeans = KMeans();
    auto* kMeansParameter = new KMeansParameter(1);
    InstanceList instanceList = iris.getInstanceList();
    kMeans.train(instanceList, kMeansParameter);
    REQUIRE_THAT(7.33, Catch::Matchers::WithinAbs(100 * kMeans.test(iris.getInstanceList())->getErrorRate(), 0.01));
    instanceList = bupa.getInstanceList();
    kMeans.train(instanceList, kMeansParameter);
    REQUIRE_THAT(43.77, Catch::Matchers::WithinAbs(100 * kMeans.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    instanceList = dermatology.getInstanceList();
    kMeans.train(instanceList, kMeansParameter);
    REQUIRE_THAT(45.08, Catch::Matchers::WithinAbs(100 * kMeans.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    instanceList = car.getInstanceList();
    kMeans.train(instanceList, kMeansParameter);
    REQUIRE_THAT(56.71, Catch::Matchers::WithinAbs(100 * kMeans.test(car.getInstanceList())->getErrorRate(), 0.01));
    instanceList = tictactoe.getInstanceList();
    kMeans.train(instanceList, kMeansParameter);
    REQUIRE_THAT(31.00, Catch::Matchers::WithinAbs(100 * kMeans.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
    instanceList = nursery.getInstanceList();
    kMeans.train(instanceList, kMeansParameter);
    REQUIRE_THAT(45.00, Catch::Matchers::WithinAbs(100 * kMeans.test(nursery.getInstanceList())->getErrorRate(), 0.01));
    instanceList = chess.getInstanceList();
    kMeans.train(instanceList, kMeansParameter);
    REQUIRE_THAT(83.25, Catch::Matchers::WithinAbs(100 * kMeans.test(chess.getInstanceList())->getErrorRate(), 0.01));
}