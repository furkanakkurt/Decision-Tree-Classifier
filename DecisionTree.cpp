#include "DecisionTree.h"
#include <cmath>
#include <iostream>
#include <fstream>
#include <string>

using namespace std; 

DecisionTree::DecisionTree() {
    root = NULL;
}

DecisionTree::~DecisionTree() {
    delete root;
}


void DecisionTree::printTree( DecisionTreeNode * rootNode, int level ) {
    //Prints the tree using preorder traversal
    //Parent - Left Child - Right Childı
    if ( rootNode == NULL ) {
        return;
    }

    printTree(rootNode->getRightChild(), level + 1 );
    //Tabs will be printed out according to the level of the node
    for ( int i = 0; i < level; i++ ) {
        cout << "\t";
    }

    //If the node is leaf, print "class"
    if ( !(rootNode->hasChildren()) ) {
        cout << "class= " << rootNode->getFeature() << endl;
    }

    else {
        cout << rootNode->getFeature() << endl;
    }


    printTree(rootNode->getLeftChild(), level + 1 );
//    cout << "\t" << rootNode->getFeature() << endl;
//    cout << rootNode->getLeftChild()->getFeature();
//    cout << "\t\t" << rootNode->getRightChild()->getFeature();
}

void DecisionTree::print() {
    printTree( root, 0 );
}

double DecisionTree::test(const bool** data, const int* labels, const int numSamples) {

    int truePredictions = 0;

    for ( int i = 0; i < numSamples; i++ ) {
        //cout << "predict data " << predict( data[i] ) << " labels[i] " << labels[i] << endl;
        //cout << "predict " << predict(data[i]) << " label " << labels[i] << endl;
        const bool * tmp = data[i];
        if ( predict( tmp ) == labels[i] ) {
            ++truePredictions;
        }
    }

    // 471 - 473 
    //cout << endl << "truepredic " << truePredictions << " numsamples " << numSamples << endl; 
    double testResult = double(truePredictions) / numSamples;
    return testResult;
}

//Auxiliary function for the above test function, parses a txt file 
double DecisionTree::test(const string fileName, const int numSamples) {

    bool ** tmpData = new bool*[numSamples];
    int * labels = new int[numSamples]; 

    ifstream file;
    file.open(fileName);
    string lineString;
    int featureSize = 0;
    // getline(file, lineString);
    // cout << "linefirst: " << lineString << endl;
	// file.clear();
	// file.seekg(0, ios::beg);
    // getline(file,lineString);
    // cout << "linefirsts: " << lineString << endl;
    // featureSize = ( lineString.size() - 1  ) / 2;
            
    for ( int i = 0; i < numSamples; i++ ) {
        tmpData[i] = new bool[featureSize];
    }

    int index = 0;
    while (  index < numSamples && getline(file, lineString) ) {
        
        //getline(file, lineString);
        //cout << "line" << index+1 << " is: " << lineString << endl;
        int j = 0;
        int lineSize = lineString.size();
        featureSize = ( lineSize - 1 ) / 2; 
        for ( int i = 0; i < lineSize; i += 2 ) {
            tmpData[index][j] = lineString[i] - '0';
            j++;
        }
        labels[index] = lineString[lineSize-2] - '0';
        //cout << "label: " << labels[index] << endl;
        index++;

    }

    //cout << "label[0] " << labels[2] << endl;
    file.close();  
    //cout << "labels " << labels[2] << endl;
    double testResult = test((const bool**)tmpData, labels, numSamples);
    for ( int i = 0; i < numSamples; i++ ) {
        delete [] tmpData[i];
    }

    delete [] tmpData;
    delete [] labels;

    return testResult;
}

int DecisionTree::predict(const bool* data ) {
    
    DecisionTreeNode * nodePtr = root;
    //cout << "feature " << nodePtr->getFeature() << endl;
    while ( nodePtr->getRightChild() || nodePtr->getLeftChild() ) {
        //cout << "node feature " << nodePtr->getFeature() << endl;
        //cout << data[nodePtr->getFeature()] << endl;
        if ( data[nodePtr->getFeature()] == 0 ) {
            nodePtr = nodePtr->getLeftChild();
        }
        else {
            nodePtr = nodePtr->getRightChild();
        }
    }

    //cout << "node feature " << nodePtr->getFeature() << endl;
    return nodePtr->getFeature();
}


void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures) {

    bool * samplesUsed = new bool[numSamples];
    bool * featuresUsed = new bool[numFeatures];

    for ( int i = 0; i < numFeatures; i++ ) {
        featuresUsed[i] = 0;
    }

    for ( int i = 0; i < numSamples; i++ ) {
        samplesUsed[i] = 0;
    }

    root = new DecisionTreeNode();
    train( root, data, labels, samplesUsed, featuresUsed, numSamples, numFeatures );

    delete [] featuresUsed;
    delete [] samplesUsed;
}


void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures) {

    bool ** tmpData = new bool*[numSamples];
    //bool tmpData[numSamples][numFeatures];
    int * labels = new int[numSamples];
    int cond = 0;
    for ( int i = 0; i < numSamples; i++ ) {
        tmpData[i] = new bool[numFeatures];
    }

    ifstream file;
    file.open(fileName);

    string lineString;
    int index = 0;
    while ( index < numSamples && getline(file, lineString) ) {
        //cout << "index: " << index << endl;
        //getline(file, lineString);
        int j = 0;
        int lineSize = lineString.size();
        for ( int i = 0; i < lineSize; i += 2 ) {
            //cout << "linestring[" << i << "]: " << lineString[i] << endl;
            tmpData[index][j] = lineString[i] - '0';
            j++;
        }
        
        //cout << "label " << lineString[lineString.size()-2] << endl;
        labels[index] = lineString[lineSize-2] - '0';
        index++;
    }

    // for ( int i = 0; i <= numSamples+10; i ++ )
    //     cout <<"I: " << i << " " << labels[i] << endl;
    // cout << "numfeatures " << numFeatures << endl;
    // cout << "element " << tmpData[0][30] << endl;
    //cout << "zero " << labels[0] << " one " << labels[1] << endl;
    // cout << "printing " << endl;
    train((const bool**)tmpData, labels, numSamples, numFeatures);

    for ( int i = 0; i < numSamples; i++ ) {
        //cout << "ss" << endl; 
        delete [] tmpData[i];
    }
    
    delete [] tmpData;
    delete [] labels;

    file.close(); 
}

void DecisionTree::train(DecisionTreeNode * rootNode, const bool** data,
               const int* labels, bool* samplesUsed, bool* featuresUsed,
               const int numSamples, const int numFeatures) { 
    
    //DecisionTreeNode * node = rootNode;
    int * samplesTmp = new int[numSamples];
    int sampleNumber = 0;
    double maxGain = 0;
    int index = -1;
    for ( int i = 0; i < numFeatures; i++ ) {
        double currentGain = calculateInformationGain( data, labels, numSamples, numFeatures, samplesUsed, i );
        //cout << "Current gain " << currentGain << endl;
        if ( currentGain > maxGain ) {
            maxGain = currentGain;
            index = i;  //index where the most gain occurs
        }
    }
    
    //cout << "Index " << index << endl;
    bool * rightLeaf = new bool[numSamples];
    bool * leftLeaf = new bool[numSamples];

    bool flag = 1;

    for ( int i = 0; i < numSamples; i++ ) {
        leftLeaf[i] = samplesUsed[i];
        rightLeaf[i] = samplesUsed[i];
        if ( samplesUsed[i] == 0 ) {
            samplesTmp[sampleNumber] = i;
            sampleNumber++;
        }
    }

    for ( int i = 0; i < sampleNumber - 1; i++ ) {
        if ( labels[samplesTmp[i]] != labels[samplesTmp[++i]] ) {
            flag = 0;
        }
    }

    for ( int i = 0; i < numFeatures; i++ ) {
        if ( index < 0 || flag ) {
            rootNode->setFeature( labels[samplesTmp[0]] );
            delete [] leftLeaf;
            delete [] rightLeaf;   
            delete [] samplesTmp;
            return;
        }
    }

    for ( int i = 0; i < numSamples; i++ ) {
        if ( samplesUsed[i] == 0 ) {
            featuresUsed[index] = 1;
        }

        if ( data[i][index] ) {
            featuresUsed[index] = 1;
            leftLeaf[i] = 1;
        }

        else {
            featuresUsed[index] = 1;
            rightLeaf[i] = 1;
        }
    } 

    rootNode->setFeature( index );
    rootNode->insertLeftChild( new DecisionTreeNode() );
    rootNode->insertRightChild( new DecisionTreeNode() );
    train( rootNode->getLeftChild(), data, labels, leftLeaf, featuresUsed, numSamples, numFeatures );
    train( rootNode->getRightChild(), data, labels, rightLeaf, featuresUsed, numSamples, numFeatures );

    delete [] leftLeaf;
    delete [] rightLeaf;   
    delete [] samplesTmp;
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
    int * classes = new int[classCount];
    int * leftClasses = new int[classCount];
    int * rightClasses = new int[classCount];

    for ( int i = 0; i < classCount; i++ ) {
        classes[i] = 0;
        leftClasses[i] = 0;
        rightClasses[i] = 0;
    }

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

    delete [] classes;
    delete [] leftClasses;
    delete [] rightClasses;

    return infoGain;
}
