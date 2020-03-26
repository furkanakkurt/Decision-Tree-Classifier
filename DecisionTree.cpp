#include "DecisionTree.h"
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std; 

DecisionTree::~DecisionTree() {
    delete root;
}

void DecisionTree::printTree( DecisionTreeNode * root, int level ) {
    //Prints the tree using preorder traversal
    //Parent - Left Child - Right Child
    if ( root == NULL ) {
        return;
    }

    //Tabs will be printed out according to the level of the node
    for ( int i = 0; i < level; i++ ) {
        cout << "\t";
    }

    //If the node is leaf, print "class"
    if ( !root->hasChildren() ) {
        cout << "class= " << root->getFeature() << endl;
    }

    else {
        cout << root->getFeature() << endl;
    }

    printTree(root->getLeftChild(), level + 1 );
    printTree(root->getRightChild(), level + 1 );

}

void DecisionTree::print() {
    printTree( root, 0 );
}

double DecisionTree::test(const bool** data, const int* labels, const int numSamples) {

    int truePredictions = 0;

    for ( int i = 0; i < numSamples; i++ ) {
        if ( predict( data[i] ) == labels[i] ) {
            ++truePredictions;
        }
    }

    double testResult = double( truePredictions / numSamples );
    return testResult;
}

double DecisionTree::test(const string fileName, const int numSamples) {

    bool ** tempData = new bool*[numSamples];
    int * tempLabels = new int[numSamples];
    int featureSize = 0;
    string line;
    string lineNumber;
    ifstream inFile;                            //File as ifstream
    inFile.open( fileName );
    streampos fileBeginning = inFile.tellg(); 
    getline( inFile, lineNumber );
    inFile.seekg( fileBeginning );



    for ( int i = 0; i < numSamples; i++ ) {
        tempData[i] = new bool[featureSize];
    }
}

int DecisionTree::predict(const bool* data ) {
    DecisionTreeNode * nodePtr = root;
    int feature = 0;
    while ( root->hasChildren() ) {
        feature = nodePtr->getFeature();
        if ( data[feature] == 0 ) {
            nodePtr = nodePtr->getLeftChild();
        }
        else {
            nodePtr = nodePtr->getRightChild();
        }
    }

    return nodePtr->getFeature();
}


void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures) {

    bool featuresTemp[numFeatures] = {false};
    bool samplesTemp[numSamples] = {true};

    root = new DecisionTreeNode();  //initializing the root

    train( root, data, labels, samplesTemp, featuresTemp, numSamples, numFeatures);
}

void train(DecisionTreeNode * rootNode, const bool** data,
               const int* labels, bool* samplesUsed, bool* featuresUsed,
               const int numSamples, const int numFeatures) {

    
}

double DecisionTree::calculateEntropy( const int * classCounts, const int numClasses) {
    
    double entropy = 0;
    double totalClassCount = 0;

    for ( int i = 0; i < numClasses; i++ ) {
        totalClassCount += classCounts[i];
    }

    for ( int j = 0; j < numClasses; j++ ) {
        if ( classCounts[j] != 0 )      //Cannot calculate log(0)
            entropy += (double) ( ( classCounts[j] * log2(classCounts[j] / totalClassCount) ) / totalClassCount );
    }

    return entropy * -1;    
}

double DecisionTree::calculateInformationGain(const bool** data, const int* labels, const int numSamples, const int numFeatures, const bool* usedSamples, const int featureId) {

    //numSample = row
    //numFeature = column
    //0 < featureId < numFeatures - 1

    //Information gain wrt a particular split
    //IG(P,S) = H(P) - H(S)
    //H(P) = entropy of current node, H(S) = entropy after potential split

    //entropy of a split S is calculated as
    //H(S) = P(left)*H(left) + P(right)*H(right)
    //P(left,right) = Prob of choosing left or right child

    int classCount  = 0;    //We do need to find the class count for calculations         
    int sizeRight = 0;      //Size of classes array of right child
    int sizeLeft = 0;       //Size of classes array of left child

    double entropyNode = 0;     //H(P)
    double entropyLeft = 0;     //H(left)
    double entropyRight = 0;    //H(right)
    double probLeft = 0;        //P(left)
    double probRight = 0;       //P(right)

    //In order to find the classCount
    //We do also need to find whether the sample reach the node 
    for ( int i = 0; i < numSamples; i++ ) {
        if ( labels[i] > classCount ) {
            classCount = labels[i];
        }
    }
    
    //Array for classes and their counts e.g. {32,0,7}
    //Should be allocated dynamically?
    int classes[classCount] = {0};
    int leftClasses[classCount] = {0};
    int rightClasses[classCount] = {0};

    //In order to determine the number of samples of each class
    for ( int i = 0; i < numSamples; i++ ) {
        if ( !usedSamples[i] ) {
            if ( data[i][featureId] == 1 ) {
                rightClasses[labels[i]-1]++;
            }
            else {
                leftClasses[labels[i]-1]++;
            }
            classes[labels[i]-1]++;
        }
    }

    for ( int i = 0; i < classCount; i++ ) {
        sizeLeft += leftClasses[i];
        sizeRight += rightClasses[i];
    }

    //cout << sizeLeft << "\t" << sizeRight << endl;
    entropyNode = calculateEntropy(classes, classCount);             //H(P)
    entropyLeft = calculateEntropy(leftClasses, classCount);        //H(left)
    entropyRight = calculateEntropy(rightClasses, classCount);        //H(right)

    probLeft = double( sizeLeft ) / numSamples;     //P(left)
    probRight = double( sizeRight ) / numSamples;   //P(right)

    double entropySplit = probLeft * entropyLeft + probRight * entropyRight;    //H(S)
    double infoGain = entropyNode - entropySplit;                               //H(P) - H(S)

    return infoGain;
}