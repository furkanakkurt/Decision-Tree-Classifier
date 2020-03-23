//#include "DecisionTreeNode.h"

class DecisionTree {

private:

public:
    double calculateEntropy( const int * classCounts, const int numClasses);
    double calculateInformationGain(const bool** data, const int* labels,
                                    const int numSamples, const int numFeatures, 
                                    const bool* usedSamples, const int featureId);
};