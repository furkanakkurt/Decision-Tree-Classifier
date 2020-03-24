//#include "DecisionTreeNode.h"
#include "DecisionTreeNode.h"

class DecisionTree {

private:
    DecisionTreeNode * root;

public:
    ~DecisionTree();
    void DecisionTree::train(const bool**, const int*, const int, const int);
    void DecisionTree::train(const string, const int, const int);
    int DecisionTree::predict(const bool*);
    double DecisionTree::test(const bool**, const int*, const int);
    double DecisionTree::test(const string, const int);
    void DecisionTree::print();
    double calculateEntropy( const int * classCounts, const int numClasses);
    double calculateInformationGain(const bool** data, const int* labels,
                                    const int numSamples, const int numFeatures, 
                                    const bool* usedSamples, const int featureId);
};