//
// Created by Olcay Taner YILDIZ on 10.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Model/Parametric/KMeansModel.h"
#include "../src/Parameter/KMeansParameter.h"

TEST_CASE("KMeansTest-testTrain") {
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
    auto* kMeansParameter = new KMeansParameter(1);
    SECTION("train") {
        KMeansModel kMeans = KMeansModel();
        InstanceList instanceList = iris.getInstanceList();
        kMeans.train(instanceList, kMeansParameter);
        REQUIRE_THAT(7.33, Catch::Matchers::WithinAbs(100 * kMeans.test(iris.getInstanceList())->getErrorRate(), 0.01));
        kMeans = KMeansModel();
        instanceList = bupa.getInstanceList();
        kMeans.train(instanceList, kMeansParameter);
        REQUIRE_THAT(43.77, Catch::Matchers::WithinAbs(100 * kMeans.test(bupa.getInstanceList())->getErrorRate(), 0.01));
        kMeans = KMeansModel();
        instanceList = dermatology.getInstanceList();
        kMeans.train(instanceList, kMeansParameter);
        REQUIRE_THAT(45.08, Catch::Matchers::WithinAbs(100 * kMeans.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
        kMeans = KMeansModel();
        instanceList = car.getInstanceList();
        kMeans.train(instanceList, kMeansParameter);
        REQUIRE_THAT(56.71, Catch::Matchers::WithinAbs(100 * kMeans.test(car.getInstanceList())->getErrorRate(), 0.01));
        kMeans = KMeansModel();
        instanceList = tictactoe.getInstanceList();
        kMeans.train(instanceList, kMeansParameter);
        REQUIRE_THAT(31.00, Catch::Matchers::WithinAbs(100 * kMeans.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
        kMeans = KMeansModel();
        instanceList = nursery.getInstanceList();
        kMeans.train(instanceList, kMeansParameter);
        REQUIRE_THAT(45.00, Catch::Matchers::WithinAbs(100 * kMeans.test(nursery.getInstanceList())->getErrorRate(), 0.01));
        kMeans = KMeansModel();
        instanceList = chess.getInstanceList();
        kMeans.train(instanceList, kMeansParameter);
        REQUIRE_THAT(83.25, Catch::Matchers::WithinAbs(100 * kMeans.test(chess.getInstanceList())->getErrorRate(), 0.01));
    }
    SECTION("load") {
        KMeansModel kMeans = KMeansModel();
        kMeans.loadModel("models/kmeans-iris.txt");
        REQUIRE_THAT(7.33, Catch::Matchers::WithinAbs(100 * kMeans.test(iris.getInstanceList())->getErrorRate(), 0.01));
        kMeans = KMeansModel();
        kMeans.loadModel("models/kmeans-bupa.txt");
        REQUIRE_THAT(43.77, Catch::Matchers::WithinAbs(100 * kMeans.test(bupa.getInstanceList())->getErrorRate(), 0.01));
        kMeans = KMeansModel();
        kMeans.loadModel("models/kmeans-dermatology.txt");
        REQUIRE_THAT(45.08, Catch::Matchers::WithinAbs(100 * kMeans.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
        kMeans = KMeansModel();
        kMeans.loadModel("models/kmeans-car.txt");
        REQUIRE_THAT(56.71, Catch::Matchers::WithinAbs(100 * kMeans.test(car.getInstanceList())->getErrorRate(), 0.01));
        kMeans = KMeansModel();
        kMeans.loadModel("models/kmeans-tictactoe.txt");
        REQUIRE_THAT(31.00, Catch::Matchers::WithinAbs(100 * kMeans.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
    }
}