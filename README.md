# Classification

## Classification Algorithms

1. Dummy: All test instances are assigned to the class with the maximum prior.
2. C45: The archetypal decision tree method.
3. Knn: K-Nearest Neighbor classification algorithm that uses the Euclidean distance.
4. Rocchio: Nearest-mean classification algorithm that uses the Euclidean distance.
5. Linear Perceptron: Linear perceptron with softmax outputs trained by gradient-descent to minimize cross-entropy.
6. Multi Layer Perceptron: Well-known multilayer perceptron classification algorithm.
7. Naive Bayes: Classic Naive Bayes classifier where each feature is assumed to be Gaussian distributed and each feature is independent from other features.
8. RandomForest: Random Forest method improves bagging idea with randomizing features at each decision node and called these random decision trees as weak learners. In the prediction time, these weak learners are combined using committee-based procedures.

For Developers
============
You can also see [Java](https://github.com/olcaytaner/Classification), [Python](https://github.com/olcaytaner/Classification-Py), or [C#](https://github.com/olcaytaner/Classification-CS) repository.

## Requirements

* [C++ Compiler](#cpp)
* [Git](#git)


### CPP
To check if you have compatible C++ Compiler installed,
* Open CLion IDE 
* Preferences >Build,Execution,Deployment > Toolchain  

### Git

Install the [latest version of Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).

## Download Code

In order to work on code, create a fork from GitHub page. 
Use Git for cloning the code to your local or below line for Ubuntu:

	git clone <your-fork-git-link>

A directory called Classification-CPP will be created. Or you can use below link for exploring the code:

	git clone https://github.com/olcaytaner/Classification-CPP.git

## Open project with CLion IDE

To import projects from Git with version control:

* Open CLion IDE , select Get From Version Control.

* In the Import window, click URL tab and paste github URL.

* Click open as Project.

Result: The imported project is listed in the Project Explorer view and files are loaded.


## Compile

**From IDE**

After being done with the downloading and opening project, select **Build Project** option from **Build** menu. After compilation process, user can run TestClassification.cpp .

Detailed Description
============
+ [Classification Algorithms](#classification-algorithms)
+ [Sampling Strategies](#sampling-strategies)
+ [Feature Selection](#feature-selection)
+ [Statistical Tests](#statistical-tests)

## Classification Algorithms

Algoritmaları eğitmek için

	void train(InstanceList trainSet, Parameter parameters)

Eğitilen modeli bir veri örneği üstünde sınamak için

	String predict(Instance instance)

Karar ağacı algoritması C45 sınıfında

Bagging algoritması Bagging sınıfında

Derin öğrenme algoritması DeepNetwork sınıfında

KMeans algoritması KMeans sınıfında

Doğrusal ve doğrusal olmayan çok katmanlı perceptron LinearPerceptron ve 
MultiLayerPerceptron sınıflarında

Naive Bayes algoritması NaiveBayes sınıfında

K en yakın komşu algoritması Knn sınıfında

Doğrusal kesme analizi algoritması Lda sınıfında

İkinci derece kesme analizi algoritması Qda sınıfında

Destek vektör makineleri algoritması Svm sınıfında

RandomForest ağaç tabanlı ensemble algoritması RandomForest sınıfında

Basit dummy ve rasgele sınıflandırıcı gibi temel iki sınıflandırıcı Dummy ve 
RandomClassifier sınıflarında

## Sampling Strategies

K katlı çapraz geçerleme deneyi yapmak için KFoldRun, KFoldRunSeparateTest, 
StratifiedKFoldRun, StratifiedKFoldRunSeparateTest

M tane K katlı çapraz geçerleme deneyi yapmak için MxKFoldRun, MxKFoldRunSeparateTest,
StratifiedMxKFoldRun, StratifiedMxKFoldRunSeparateTest

Bootstrap tipi deney yapmak için BootstrapRun

## Feature Selection

Pca tabanlı boyut azaltma için Pca sınıfı

Discrete değişkenleri Continuous değişkenlere çevirmek için DiscreteToContinuous sınıfı

Discrete değişkenleri binary değişkenlere değiştirmek için LaryToBinary sınıfı

## Statistical Tests

İstatistiksel testler için Combined5x2F, Combined5x2t, Paired5x2t, Pairedt, Sign sınıfları
