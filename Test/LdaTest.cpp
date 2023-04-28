//
// Created by Olcay Taner YILDIZ on 10.01.2021.
//

#include "catch.hpp"
#include "../src/DataSet/DataSet.h"
#include "../src/Classifier/Lda.h"

TEST_CASE("LdaTest") {
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
    Lda lda = Lda();
    SECTION("train"){
        InstanceList instanceList = iris.getInstanceList();
        lda.train(instanceList, nullptr);
        REQUIRE_THAT(2.00, Catch::Matchers::WithinAbs(100 * lda.test(iris.getInstanceList())->getErrorRate(), 0.01));
        instanceList = bupa.getInstanceList();
        lda.train(instanceList, nullptr);
        REQUIRE_THAT(29.57, Catch::Matchers::WithinAbs(100 * lda.test(bupa.getInstanceList())->getErrorRate(), 0.01));
        instanceList = dermatology.getInstanceList();
        lda.train(instanceList, nullptr);
        REQUIRE_THAT(1.91, Catch::Matchers::WithinAbs(100 * lda.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    };
    SECTION("load"){
        lda.loadModel("models/lda-iris.txt");
        REQUIRE_THAT(2.00, Catch::Matchers::WithinAbs(100 * lda.test(iris.getInstanceList())->getErrorRate(), 0.01));
        lda.loadModel("models/lda-bupa.txt");
        REQUIRE_THAT(29.57, Catch::Matchers::WithinAbs(100 * lda.test(bupa.getInstanceList())->getErrorRate(), 0.01));
        lda.loadModel("models/lda-dermatology.txt");
        REQUIRE_THAT(1.91, Catch::Matchers::WithinAbs(100 * lda.test(dermatology.getInstanceList())->getErrorRate(), 0.01));
    }
}