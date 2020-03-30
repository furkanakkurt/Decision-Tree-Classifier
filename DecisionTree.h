//#include "DecisionTreeNode.h"
#include "DecisionTreeNode.h"
#include <string>   
using namespace std;

class DecisionTree {

private:
    DecisionTreeNode * root;
    //In order to call the train function recursively
    void train(DecisionTreeNode * rootNode, const bool** data,
               const int* labels, bool* samplesUsed, bool* featuresUsed,
               const int numSamples, const int numFeatures);
    void printTree( DecisionTreeNode * root, int level );
    int findMaxGain( const bool ** data, const int * labels, const int numSamples,
                               const int numFeatures, bool * samplesUsed );

public:
    ~DecisionTree();
    DecisionTree();
    void train(const bool** data, const int* labels, const int numSamples, const int numFeatures);
    void train(const string fileName, const int numSamples, const int numFeatures);
    int predict(const bool* data);
    double test(const bool** data, const int* labels, const int numSamples);
    double test(const string fileName, const int numSamples);
    void print();
    double calculateEntropy( const int * classCounts, const int numClasses);
    double calculateInformationGain(const bool** data, const int* labels,
                                    const int numSamples, const int numFeatures, 
                                    const bool* usedSamples, const int featureId);
};