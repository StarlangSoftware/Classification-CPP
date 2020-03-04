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
You can also see either [Python](https://github.com/olcaytaner/Classification-Py) 
or [Java](https://github.com/olcaytaner/Classification) repository.
## Requirements

* [Java Development Kit 8 or higher](#java), Open JDK or Oracle JDK
* [Maven](#maven)
* [Git](#git)

### Java 

To check if you have a compatible version of Java installed, use the following command:

    java -version
    
If you don't have a compatible version, you can download either [Oracle JDK](https://www.oracle.com/technetwork/java/javase/downloads/jdk8-downloads-2133151.html) or [OpenJDK](https://openjdk.java.net/install/)

### Maven
To check if you have Maven installed, use the following command:

    mvn --version
    
To install Maven, you can follow the instructions [here](https://maven.apache.org/install.html).      

### Git

Install the [latest version of Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).

## Download Code

In order to work on code, create a fork from GitHub page. 
Use Git for cloning the code to your local or below line for Ubuntu:

	git clone <your-fork-git-link>

A directory called DataStructure will be created. Or you can use below link for exploring the code:

	git clone https://github.com/olcaytaner/Classification-CPP.git

## Open project with NetBeans IDE

To import projects from Git with smart import:

* Click File > Import.

* In the Import window, click Projects from Git (with smart import) and click Next.

* In the Select Repository Source window, click Existing local repository or Clone URI.

* Step through the wizard and click Finish for the wizard to analyze the content of the project folder to find projects for import and import them in the IDE. 

Result: The imported project is listed in the Project Explorer view.


## Compile

**From IDE**

After being done with the downloading and Maven indexing, select **Build Project** option from **Build** menu. After compilation process, user can run Classification-CPP.
