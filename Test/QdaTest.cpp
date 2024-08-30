//
// Created by Olcay Taner YILDIZ on 10.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Model/Parametric/QdaModel.h"

TEST_CASE("QdaTest") {
    DataSet iris, bupa;
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
    SECTION("train"){
        QdaModel qda = QdaModel();
        InstanceList instanceList = iris.getInstanceList();
        qda.train(instanceList, nullptr);
        REQUIRE_THAT(2.00, Catch::Matchers::WithinAbs(100 * qda.test(iris.getInstanceList())->getErrorRate(), 0.01));
        qda = QdaModel();
        instanceList = bupa.getInstanceList();
        qda.train(instanceList, nullptr);
        REQUIRE_THAT(36.52, Catch::Matchers::WithinAbs(100 * qda.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    }
    SECTION("load"){
        QdaModel qda = QdaModel();
        qda.loadModel("models/qda-iris.txt");
        REQUIRE_THAT(2.00, Catch::Matchers::WithinAbs(100 * qda.test(iris.getInstanceList())->getErrorRate(), 0.01));
        qda = QdaModel();
        qda.loadModel("models/qda-bupa.txt");
        REQUIRE_THAT(36.52, Catch::Matchers::WithinAbs(100 * qda.test(bupa.getInstanceList())->getErrorRate(), 0.01));
    }
}