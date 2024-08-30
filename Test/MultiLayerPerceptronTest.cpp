//
// Created by Olcay Taner YILDIZ on 11.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Model/NeuralNetwork/MultiLayerPerceptronModel.h"

TEST_CASE("MultiLayerPerceptronTest") {
    DataSet iris, bupa, dermatology;
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
    auto* multiLayerPerceptronParameter = new MultiLayerPerceptronParameter(1, 0.1, 0.99, 0.2, 100, 3, ActivationFunction::SIGMOID);
    SECTION("train"){
        MultiLayerPerceptronModel multiLayerPerceptron = MultiLayerPerceptronModel();
        InstanceList instanceList = iris.getInstanceList();
        multiLayerPerceptron.train(instanceList, multiLayerPerceptronParameter);
        REQUIRE_THAT(3.33, Catch::Matchers::WithinAbs(100 * multiLayerPerceptron.test(iris.getInstanceList())->getErrorRate(), 0.01));
        multiLayerPerceptron = MultiLayerPerceptronModel();
        instanceList = bupa.getInstanceList();
        multiLayerPerceptronParameter = new MultiLayerPerceptronParameter(1, 0.01, 0.99, 0.2, 100, 30, ActivationFunction::SIGMOID);
        multiLayerPerceptron.train(instanceList, multiLayerPerceptronParameter);
        REQUIRE_THAT(30.43, Catch::Matchers::WithinAbs(100 * multiLayerPerceptron.test(bupa.getInstanceList())->getErrorRate(), 0.01));
        multiLayerPerceptron = MultiLayerPerceptronModel();
        instanceList = dermatology.getInstanceList();
        multiLayerPerceptronParameter = new MultiLayerPerceptronParameter(1, 0.01, 0.99, 0.2, 100, 20, ActivationFunction::SIGMOID);
        multiLayerPerceptron.train(instanceList, multiLayerPerceptronParameter);
        REQUIRE_THAT(2.73, Catch::Matchers::WithinAbs(100 * multiLayerPerceptron.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    }
    SECTION("load"){
        MultiLayerPerceptronModel multiLayerPerceptron = MultiLayerPerceptronModel();
        multiLayerPerceptron.loadModel("models/multiLayerPerceptron-iris.txt");
        REQUIRE_THAT(2.67, Catch::Matchers::WithinAbs(100 * multiLayerPerceptron.test(iris.getInstanceList())->getErrorRate(), 0.01));
        multiLayerPerceptron = MultiLayerPerceptronModel();
        multiLayerPerceptron.loadModel("models/multiLayerPerceptron-bupa.txt");
        REQUIRE_THAT(27.54, Catch::Matchers::WithinAbs(100 * multiLayerPerceptron.test(bupa.getInstanceList())->getErrorRate(), 0.01));
        multiLayerPerceptron = MultiLayerPerceptronModel();
        multiLayerPerceptron.loadModel("models/multiLayerPerceptron-dermatology.txt");
        REQUIRE_THAT(1.09, Catch::Matchers::WithinAbs(100 * multiLayerPerceptron.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    }
}