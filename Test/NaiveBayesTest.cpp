//
// Created by Olcay Taner YILDIZ on 10.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Model/Parametric/NaiveBayesModel.h"

TEST_CASE("NaiveBayesTest") {
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
    SECTION("train"){
        NaiveBayesModel naiveBayes = NaiveBayesModel();
        InstanceList instanceList = iris.getInstanceList();
        naiveBayes.train(instanceList, nullptr);
        REQUIRE_THAT(5.33, Catch::Matchers::WithinAbs(100 * naiveBayes.test(iris.getInstanceList())->getErrorRate(), 0.01));
        naiveBayes = NaiveBayesModel();
        instanceList = bupa.getInstanceList();
        naiveBayes.train(instanceList, nullptr);
        REQUIRE_THAT(38.55, Catch::Matchers::WithinAbs(100 * naiveBayes.test(bupa.getInstanceList())->getErrorRate(), 0.01));
        naiveBayes = NaiveBayesModel();
        instanceList = dermatology.getInstanceList();
        naiveBayes.train(instanceList, nullptr);
        REQUIRE_THAT(69.40, Catch::Matchers::WithinAbs(100 * naiveBayes.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
        naiveBayes = NaiveBayesModel();
        instanceList = car.getInstanceList();
        naiveBayes.train(instanceList, nullptr);
        REQUIRE_THAT(12.91, Catch::Matchers::WithinAbs(100 * naiveBayes.test(car.getInstanceList())->getErrorRate(), 0.01));
        naiveBayes = NaiveBayesModel();
        instanceList = tictactoe.getInstanceList();
        naiveBayes.train(instanceList, nullptr);
        REQUIRE_THAT(30.17, Catch::Matchers::WithinAbs(100 * naiveBayes.test(tictactoe.getInstanceList())->getErrorRate(), 0.01));
    }
    SECTION("load"){
        NaiveBayesModel naiveBayes = NaiveBayesModel();
        naiveBayes.loadModel("models/naiveBayes-iris.txt");
        REQUIRE_THAT(5.33, Catch::Matchers::WithinAbs(100 * naiveBayes.test(iris.getInstanceList())->getErrorRate(), 0.01));
        naiveBayes = NaiveBayesModel();
        naiveBayes.loadModel("models/naiveBayes-bupa.txt");
        REQUIRE_THAT(38.55, Catch::Matchers::WithinAbs(100 * naiveBayes.test(bupa.getInstanceList())->getErrorRate(), 0.01));
        naiveBayes = NaiveBayesModel();
        naiveBayes.loadModel("models/naiveBayes-dermatology.txt");
        REQUIRE_THAT(69.40, Catch::Matchers::WithinAbs(100 * naiveBayes.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    }
}