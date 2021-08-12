//
// Created by Olcay Taner YILDIZ on 11.01.2021.
//

#include "catch.hpp"
#include "../DataSet/DataSet.h"
#include "../Classifier/DeepNetwork.h"
#include "../Parameter/DeepNetworkParameter.h"

TEST_CASE("DeepNetworkTest-testTrain") {
    DataSet iris, bupa, dermatology;
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
    DeepNetwork deepNetwork = DeepNetwork();
    InstanceList instanceList = iris.getInstanceList();
    auto* deepNetworkParameter = new DeepNetworkParameter(1, 0.1, 0.99, 0.2, 100, vector<int>({5, 5}), ActivationFunction::SIGMOID);
    deepNetwork.train(instanceList, deepNetworkParameter);
    REQUIRE_THAT(2.67, Catch::Matchers::WithinAbs(100 * deepNetwork.test(iris.getInstanceList())->getErrorRate(), 0.01));
    instanceList = bupa.getInstanceList();
    deepNetworkParameter = new DeepNetworkParameter(1, 0.01, 0.99, 0.2, 100, vector<int>({15, 15}), ActivationFunction::SIGMOID);
    deepNetwork.train(instanceList, deepNetworkParameter);
    REQUIRE_THAT(30.43, Catch::Matchers::WithinAbs(100 * deepNetwork.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    instanceList = dermatology.getInstanceList();
    deepNetworkParameter = new DeepNetworkParameter(1, 0.01, 0.99, 0.2, 100, vector<int>({20}), ActivationFunction::SIGMOID);
    deepNetwork.train(instanceList, deepNetworkParameter);
    REQUIRE_THAT(2.46, Catch::Matchers::WithinAbs(100 * deepNetwork.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
}