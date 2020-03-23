#include "DecisionTree.h"
#include <cmath>

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

    double entropyNode;     //H(P)
    double entropySplit;    //H(S)

    int usedDataCount = 0;
    int classCount  = 0;
    int innerArray = 0;

    int sizeRight = 0;      //Size of classes array of right child
    int sizeLeft = 0;       //Size of classes array of left child

    //In order to find the classCount
    for ( int i = 0; i < numSamples; i++ ) {
        if ( usedSamples[i] ) {
            usedDataCount++;
            if ( labels[i] > classCount ) {
                classCount = labels[i];
            }
        }
    }
    
    //Array for classes and their counts e.g. {32,0,7}
    //Should be allocated dynamically?
    int classes[classCount] = {0};
    int leftClasses[classCount] = {0};
    int rightClasses[classCount] = {0};

    //These arrays are created 
    bool ** datasUsed = new bool*[usedDataCount];
    int * labelsUsed = new int[usedDataCount];


    //In order to fill in the two arrays created above
    for ( int j = 0; j < numSamples; j++ ) {
        if ( usedSamples[j] ) {
            //creating the array 
            datasUsed[innerArray] = new bool[numFeatures];
            //initializing the array elements
            for ( int k = 0; k < numFeatures; k++ ) {
                datasUsed[innerArray][k] = data[j][k];
            }
            labelsUsed[innerArray] = labels[j];
            ++innerArray;
        }
    }

    for ( int l = 0; l < usedDataCount; l++ ) {
        for ( int m = 0; m < classCount; m++ ) {
            if (labelsUsed[l] == m + 1 ) {
                classes[m] += 1;
            }
        }

        if (datasUsed[l][featureId] == 0 ) {
            for ( int n = 0; n < classCount; n++ ) {
                if (labelsUsed[l] == n + 1 ) {
                    leftClasses[n] += 1;
                }
            }
            ++sizeLeft;
        }

        else {
            for ( int o = 0; o < classCount; o++ ) {
               if ( labelsUsed[l] == o + 1 ) {
                   rightClasses[o] += 1;
               } 
            }
            ++sizeRight;
        }
    }

    for ( int p = 0; p < usedDataCount; p++ ) {
        delete [] datasUsed[p];
    }

    delete [] datasUsed;
    delete [] labelsUsed;

    entropyNode = calculateEntropy(classes, classCount);
    double entropyLeft = calculateEntropy(rightClasses, classCount);    //H(left)
    double entropyRight = calculateEntropy(leftClasses, classCount);    //H(right)

    double probLeft = sizeLeft / usedDataCount;     //P(left)
    double probRight = sizeRight / usedDataCount;   //P(right) 

    entropySplit = probLeft * entropyLeft + probRight * entropyRight;
    return entropyNode - entropySplit;
}