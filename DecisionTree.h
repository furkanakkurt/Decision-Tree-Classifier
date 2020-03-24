//#include "DecisionTreeNode.h"
#include "DecisionTreeNode.h"

class DecisionTree {

private:
    DecisionTreeNode * root;
    //In order to call the train function recursively
    void train(DecisionTreeNode * rootNode, const bool** data,
               const int* labels, bool* samplesUsed, bool* featuresUsed,
               const int numSamples, const int numFeatures);

public:
    ~DecisionTree();
    void DecisionTree::train(const bool** data, const int* labels, const int numSamples, const int numFeatures);
    void DecisionTree::train(const string fileName, const int numSamples, const int numFeatures);
    int DecisionTree::predict(const bool*);
    double DecisionTree::test(const bool**, const int*, const int);
    double DecisionTree::test(const string, const int);
    void DecisionTree::print();
    double calculateEntropy( const int * classCounts, const int numClasses);
    double calculateInformationGain(const bool** data, const int* labels,
                                    const int numSamples, const int numFeatures, 
                                    const bool* usedSamples, const int featureId);
};