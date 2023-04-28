//
// Created by Olcay Taner YILDIZ on 10.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/Knn.h"
#include "../src/Parameter/KnnParameter.h"
#include "../src/DistanceMetric/EuclidianDistance.h"

TEST_CASE("KnnTest") {
    DataSet iris, car, bupa, tictactoe, dermatology, nursery;
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
    Knn knn = Knn();
    auto* knnParameter = new KnnParameter(1, 3, new EuclidianDistance());
    SECTION("train"){
        InstanceList instanceList = iris.getInstanceList();
        knn.train(instanceList, knnParameter);
        REQUIRE_THAT(4.00, Catch::Matchers::WithinAbs(100 * knn.test(iris.getInstanceList())->getErrorRate(), 0.01));
        instanceList = bupa.getInstanceList();
        knn.train(instanceList, knnParameter);
        REQUIRE_THAT(19.42, Catch::Matchers::WithinAbs(100 * knn.test(bupa.getInstanceList())->getErrorRate(), 0.01));
        instanceList = dermatology.getInstanceList();
        knn.train(instanceList, knnParameter);
        REQUIRE_THAT(3.83, Catch::Matchers::WithinAbs(100 * knn.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
        instanceList = car.getInstanceList();
        knn.train(instanceList, knnParameter);
        REQUIRE_THAT(21.06, Catch::Matchers::WithinAbs(100 * knn.test(car.getInstanceList())->getErrorRate(), 0.01));
        instanceList = tictactoe.getInstanceList();
        knn.train(instanceList, knnParameter);
        REQUIRE_THAT(32.57, Catch::Matchers::WithinAbs(100 * knn.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
    }
    SECTION("load"){
        knn.loadModel("models/knn-iris.txt");
        REQUIRE_THAT(4.00, Catch::Matchers::WithinAbs(100 * knn.test(iris.getInstanceList())->getErrorRate(), 0.01));
        knn.loadModel("models/knn-bupa.txt");
        REQUIRE_THAT(19.42, Catch::Matchers::WithinAbs(100 * knn.test(bupa.getInstanceList())->getErrorRate(), 0.01));
        knn.loadModel("models/knn-dermatology.txt");
        REQUIRE_THAT(3.83, Catch::Matchers::WithinAbs(100 * knn.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
        knn.loadModel("models/knn-car.txt");
        REQUIRE_THAT(21.06, Catch::Matchers::WithinAbs(100 * knn.test(car.getInstanceList())->getErrorRate(), 0.01));
        knn.loadModel("models/knn-tictactoe.txt");
        REQUIRE_THAT(32.57, Catch::Matchers::WithinAbs(100 * knn.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
    }
}