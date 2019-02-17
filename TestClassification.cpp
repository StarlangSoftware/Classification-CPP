//
// Created by Olcay Taner Yıldız on 26.01.2019.
//

#include <iostream>
#include "Instance/Instance.h"
#include "Attribute/ContinuousAttribute.h"
#include "Attribute/DiscreteIndexedAttribute.h"
#include "Parameter/Parameter.h"
#include "Parameter/LinearPerceptronParameter.h"
#include "Parameter/MultiLayerPerceptronParameter.h"
#include "Parameter/DeepNetworkParameter.h"
#include "DataSet/DataSet.h"
#include "Classifier/Classifier.h"
#include "Classifier/Dummy.h"
#include "Experiment/StratifiedKFoldRun.h"
#include "Classifier/RandomClassifier.h"
#include "Classifier/Lda.h"
#include "Classifier/Qda.h"
#include "Classifier/NaiveBayes.h"
#include "Classifier/KMeans.h"
#include "Parameter/KMeansParameter.h"
#include "Classifier/Knn.h"
#include "Parameter/KnnParameter.h"
#include "Classifier/LinearPerceptron.h"
#include "Classifier/MultiLayerPerceptron.h"
#include "Classifier/DeepNetwork.h"
#include "Classifier/Svm.h"
#include "Parameter/SvmParameter.h"
#include "Classifier/C45.h"
#include "Parameter/C45Parameter.h"

Parameter* defaultParameter() { return new Parameter(1);}

Parameter* linearPerceptron(){
    return new LinearPerceptronParameter(1, 0.1, 0.95, 0.2, 10);
}

Parameter* multiLayerPerceptron(){
    return new MultiLayerPerceptronParameter(1, 0.1, 0.95, 0.2, 30, 5);
}

Parameter* deepNetwork(){
    vector<int> hiddens;
    hiddens.push_back(3);
    hiddens.push_back(5);
    return new DeepNetworkParameter(1, 0.5, 0.95, 0.2, 30, hiddens);
}

DataSet readIris(){
    vector<AttributeType> attributeTypes;
    attributeTypes.reserve(4);
    for (int i = 0; i < 4; i++){
        attributeTypes.push_back(AttributeType::CONTINUOUS);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    return DataSet(dataDefinition, ",", "iris.data");
}

DataSet readBupa(){
    vector<AttributeType> attributeTypes;
    attributeTypes.reserve(6);
    for (int i = 0; i < 6; i++){
        attributeTypes.push_back(AttributeType::CONTINUOUS);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    return DataSet(dataDefinition, ",", "bupa.data");
}

DataSet readDermatology(){
    vector<AttributeType> attributeTypes;
    attributeTypes.reserve(34);
    for (int i = 0; i < 34; i++){
        attributeTypes.push_back(AttributeType::CONTINUOUS);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    return DataSet(dataDefinition, ",", "dermatology.data");
}

DataSet readRingnorm(){
    vector<AttributeType> attributeTypes;
    attributeTypes.reserve(20);
    for (int i = 0; i < 20; i++){
        attributeTypes.push_back(AttributeType::CONTINUOUS);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    return DataSet(dataDefinition, ",", "ringnorm.data");
}

DataSet readTwonorm(){
    vector<AttributeType> attributeTypes;
    attributeTypes.reserve(20);
    for (int i = 0; i < 20; i++){
        attributeTypes.push_back(AttributeType::CONTINUOUS);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    return DataSet(dataDefinition, ",", "twonorm.data");
}

DataSet readCar(){
    vector<AttributeType> attributeTypes;
    attributeTypes.reserve(6);
    for (int i = 0; i < 6; i++){
        attributeTypes.push_back(AttributeType::DISCRETE);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    return DataSet(dataDefinition, ",", "car.data");
}

DataSet readNursery(){
    vector<AttributeType> attributeTypes;
    attributeTypes.reserve(8);
    for (int i = 0; i < 8; i++){
        attributeTypes.push_back(AttributeType::DISCRETE);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    return DataSet(dataDefinition, ",", "nursery.data");
}

DataSet readConnect4(){
    vector<AttributeType> attributeTypes;
    attributeTypes.reserve(42);
    for (int i = 0; i < 42; i++){
        attributeTypes.push_back(AttributeType::DISCRETE);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    return DataSet(dataDefinition, ",", "connect4.data");
}

DataSet readTicTacToe(){
    vector<AttributeType> attributeTypes;
    attributeTypes.reserve(9);
    for (int i = 0; i < 9; i++){
        attributeTypes.push_back(AttributeType::DISCRETE);
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    return DataSet(dataDefinition, ",", "tictactoe.data");
}

DataSet readChess(){
    vector<AttributeType> attributeTypes;
    for (int i = 0; i < 6; i++){
        if (i % 2 == 0){
            attributeTypes.push_back(AttributeType::DISCRETE);
        } else {
            attributeTypes.push_back(AttributeType::CONTINUOUS);
        }
    }
    DataDefinition dataDefinition = DataDefinition(attributeTypes);
    return DataSet(dataDefinition, ",", "chess.data");
}

int main(){
    DataSet dataSet = readIris();
    //DataSet dataSet = readCar();
    //DataSet dataSet = readDermatology();
    //DataSet dataSet = readTwonorm();
    Classifier* classifier = new C45();
    //vector<int> hiddenLayers;
    //hiddenLayers.push_back(10);
    Parameter* parameter = new C45Parameter(1, true, 0.2);
    StratifiedKFoldRun* run = new StratifiedKFoldRun(10);
    ExperimentPerformance* result;
    Experiment experiment = Experiment(classifier, parameter, dataSet);
    result = run->execute(experiment);
    cout << 100 * (result->meanClassificationPerformance()->getErrorRate());
}
