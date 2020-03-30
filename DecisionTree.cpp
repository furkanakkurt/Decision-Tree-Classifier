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
        //cout << "predict data " << predict( data[i] ) << " labels[i] " << labels[i] << endl;
        if ( predict( data[i] ) == labels[i] ) {
            ++truePredictions;
        }
    }

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
    
    getline(file, lineString);

	file.clear();
	file.seekg(0, ios::beg);
    //calculating the feature size by the first line 

    featureSize = ( lineString.size() - 1  ) / 2;
    for ( int i = 0; i < numSamples; i++ ) {
        tmpData[i] = new bool[featureSize];
    }

    int index = 0;
    while ( !( file.eof() ) ) {
        getline(file, lineString);
        int j = 0;
        for ( int i = 0; i < lineString.size(); i += 2 ) {
            tmpData[index][j] = lineString[i] - '0';
            j++;
        }

        labels[index] = lineString[lineString.size()-2] - '0';
        index++;
    }

    //cout << "label[0] " << labels[2] << endl;

    file.close();
    const bool * const * data = tmpData;  
  
    //cout << "labels " << labels[2] << endl;
    double testResult = test((const bool**)data, labels, numSamples);
    for ( int i = 0; i < numSamples; i++ ) {
        delete [] data[i];
    }

    delete [] data;
    delete [] labels;

    return testResult;
}

int DecisionTree::predict(const bool* data ) {
    
    DecisionTreeNode * nodePtr = root;
    //cout << "feature " << nodePtr->getFeature() << endl;
    while ( nodePtr->getRightChild() != NULL && nodePtr->getLeftChild() != NULL ) {
        //cout << "node feature " << nodePtr->getFeature() << endl;ü
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

    bool * featuresTemp = new bool[numFeatures];
    bool * samplesTemp = new bool[numSamples];

    for ( int i = 0; i < numFeatures; i++ ) {
        featuresTemp[i] = 0;
    }

    for ( int i = 0; i < numFeatures; i++ ) {
        samplesTemp[i] = 1;
    }

    // for ( int i = numFeatures; i < numSamples; i++ ) {
    //     samplesTemp[i] = 0;
    // }

    //cout << data[0][19]  << " sasa" << endl;
    root = new DecisionTreeNode();  //initializing the root

    train( root, data, labels, samplesTemp, featuresTemp, numSamples, numFeatures );
    
    delete [] featuresTemp;
    delete [] samplesTemp;
}


void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures) {

    bool ** tmpData = new bool*[numSamples];
    int * labels = new int[numSamples];


    for ( int i = 0; i < numSamples; i++ ) {
        tmpData[i] = new bool[numFeatures];
    }

    ifstream file;
    file.open(fileName);

    string lineString;
    int index = 0;
    while ( !( file.eof() ) ) {
        getline(file, lineString);
        int j = 0;
        for ( int i = 0; i < lineString.size(); i += 2 ) {
            tmpData[index][j] = lineString[i] - '0';
            j++;
        }

        //cout << "label " << lineString[lineString.size()-2] << endl;
        labels[index] = lineString[lineString.size()-2] - '0';
        index++;
    }

    const bool * const * tmp = tmpData; 
    // cout << "numfeatures " << numFeatures << endl;
    // cout << "element " << tmpData[0][30] << endl;
    //cout << "zero " << labels[0] << " one " << labels[1] << endl;
    // cout << "printing " << endl;
    train((const bool**)tmp, labels, numSamples, numFeatures);
    
    for ( int i = 0; i < numSamples; i++ ) {
        //cout << "counter " << i << endl;
        //delete [] tmpData[i];
    }
    
    //delete [] tmpData;
    //delete [] labels;

    file.close();   
}


void DecisionTree::train(DecisionTreeNode * rootNode, const bool** data,
               const int* labels, bool* samplesUsed, bool* featuresUsed,
               const int numSamples, const int numFeatures) {
    
	int curLabel = -1;
    int prevLabel = -1;
    int pureValue = -1;
    bool isPure = 1;
    bool allUsed = 1;


    //Checks whether given sample split is pure
    //for ( int i = 1; i < numSamples && isPure == 1; i++ ) {
    for ( int i = 0; i < numSamples && isPure; i++ ) { 
        //cout << "sample " << samplesUsed[numSamples-1] << endl;
        //cout << endl;   
        if ( samplesUsed[i] ) {
            pureValue = labels[i];
            if ( curLabel != labels[i] ) {
                if ( curLabel == -1 ) {
                    curLabel = labels[i];
                }
                else {
                    prevLabel = curLabel;
                    curLabel = labels[i];
                    if ( prevLabel != curLabel ) {
                        isPure = 0;
                    }
                }
            }
            // else {
            //     prevLabel = curLabel;
            //     curLabel = labels[i];
            // }
        }
    } 

    // cout << "pure " << pureValue << endl;
    // cout << "cur " << curLabel << endl;
    // cout << "prev " << prevLabel << endl;
    if ( prevLabel == -1 ) {
        isPure = 1;
        rootNode->setFeature( pureValue );
        return;
    }

    for ( int i = 0; i < numFeatures; i++ ) {
        if ( !featuresUsed[i] ) {
            allUsed = 0;
        }
    }


    if ( allUsed ) {
        cout << "DEBUGGGGG " << endl;
        int classCount = 0;

        for ( int i = 0; i < numSamples; i++ ) {
            if ( samplesUsed[i] ) {
                if ( classCount < labels[i] ) {
                    classCount = labels[i];
                }
            }
        }

        int * classes = new int[classCount];

        for ( int i = 0; i < classCount; i++ ) {
            classes[i] = 0;
        }

        for ( int i = 0; i < numSamples; i++ ) {
            if ( samplesUsed[i] ) {
                int index = labels[i] - 1;
                ( classes[index] )++;
            }
        }

        int feature = 0;
        for ( int i = 0; i < classCount; i++ ) {
            if ( classes[feature] < classes[i] ) {
                feature = ++i;
            }
        }

        rootNode->setFeature( feature );
    }

    else {
        bool * samplesLeft = new bool[numSamples];
        bool * samplesRight = new bool[numSamples];
        double gainMost = 0;
        int featureToSelect = -1;

        for ( int i = 0; i < numFeatures; i++ ) {
            if ( !featuresUsed[i] ) {
                double gain = calculateInformationGain(data, labels, numSamples, numFeatures, samplesUsed, i);
                if ( gainMost < gain ) {
                    gainMost = gain;
                    featureToSelect = i;
                }
            }
        }

        featuresUsed[featureToSelect] = 1;

        for ( int i = 0; i < numSamples; i++ ) {
            if ( samplesUsed[i] ) {
                if ( !data[i][featureToSelect] ) {
                    samplesLeft[i] = samplesUsed[i];
                    samplesRight[i] = 0;
                }
                else {
                    samplesRight[i] = samplesUsed[i];
                    samplesLeft[i] = 0;
                }
            }
            else {
                samplesLeft[i] = samplesRight[i] = 0;
            }
        }

        rootNode->setFeature( featureToSelect );
        rootNode->insertLeftChild( new DecisionTreeNode() );
        rootNode->insertRightChild( new DecisionTreeNode() );
        
        train(rootNode->getLeftChild(), data, labels, samplesLeft, featuresUsed, numSamples, numFeatures);
        //cout << "debugg " << endl;   
		train(rootNode->getRightChild(), data, labels, samplesRight, featuresUsed, numSamples, numFeatures);
    
        delete [] samplesRight;
        delete [] samplesLeft;
    }
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
    cout << "classcount " << classCount << endl;
    int * classes = new int[classCount];
    int * leftClasses = new int[classCount];
    int * rightClasses = new int[classCount];

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

/**
void DecisionTree::train(DecisionTreeNode * rootNode, const bool** data,
               const int* labels, bool* samplesUsed, bool* featuresUsed,
               const int numSamples, const int numFeatures) {

    bool * leftSamples = new bool[numSamples];
    bool * rightSamples = new bool[numSamples];

    int * samples = new int[numSamples];

    int currentGainIndex = findMaxGain( data, labels, numSamples, numFeatures, samplesUsed );

    int index = 0;
    for ( int i = 0; i < numSamples; i++ ) {
        leftSamples[i] = rightSamples[i] = samplesUsed[i];
    }

    for ( int i = 0; i < numSamples; i++ ) {
        if ( samplesUsed[i] == 0 ) {
            samples[index++] = i;
        }
    }

    bool flagT = 1;
    bool flagF = 0;

    for ( int i = 0; i < index - 1; ++i ) {
        if ( labels[samples[i]] != labels[samples[i+1]] ) {
            flagT = 0;
            return;
        }
    }

    //cout << "currentgainindex " << currentGainIndex << endl;
    for ( int i = 0; i < numFeatures; ++i ) {
        if ( currentGainIndex < 0 ) {
            return;
        }
    }

    for ( int i = 0; i < numSamples; i++ ) {
        if ( samplesUsed[i] == 0 ) {
            featuresUsed[currentGainIndex] = 1;
            // if ( rootNode == nullptr ) {
            //     rootNode = new DecisionTreeNode();
            // }
            if ( rootNode->getFeature() == -1 ) {
                rootNode->setFeature( currentGainIndex );
            }
            if ( data[i][currentGainIndex] == 1 ) {
                rightSamples[i] = 1;
            }
            else {
                leftSamples[i] = 1;
            }
        }
    }

    cout << "insertleft " << endl;
    rootNode->insertLeftChild( new DecisionTreeNode() );
    cout << "inserright " << endl;
    rootNode->insertRightChild( new DecisionTreeNode() );
    train( rootNode->getLeftChild(), data, labels, leftSamples, featuresUsed, numSamples, numFeatures );
    train( rootNode->getRightChild(), data, labels, rightSamples, featuresUsed, numSamples, numFeatures );
}

int DecisionTree::findMaxGain( const bool ** data, const int * labels, const int numSamples,
                               const int numFeatures, bool * samplesUsed ) {

    double maxGain = 0;
    double gain = 0;
    int index = 0;
    
    // cout << "data " << endl;
    // for ( int i = 0; i < numSamples; i++ ) {
    //     for ( int j = 0; j < numFeatures; j++ ) {
    //         cout << "i: " << i << " j: " << j << " " << data[i][j] << endl;
    //     }
    // }
    //cout << "numfeatures " << numFeatures << endl; 
    for ( int i = 0; i < numFeatures; i++ ) {
        gain = calculateInformationGain( data, labels, numSamples, numFeatures, samplesUsed, i );
        cout << "gain   " << gain << endl;
        // cout << "numsamples   " << numSamples << endl;
        // cout << "numfeatures   " << numFeatures << endl;
        // cout << "samples: " << endl;
        if ( maxGain < gain ) {
            maxGain = gain;
            index = i;
        }
    }

    cout << "index in findmax " << index << endl;
    return index;
} 
*/