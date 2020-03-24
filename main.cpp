#include "DecisionTree.h"
//#include "DecisionTreeNode.h"
#include <iostream>

using namespace std;

int main() {

    DecisionTree dt;
    int arr22[3] = {1,0,0};
    //cout << dt.calculateEntropy(arr22, 3) << endl;


    bool a1[4] = {0, 1, 0, 0};
    bool a2[4] = {0, 1, 0, 0};
    bool a3[4] = {0, 1, 0, 0};
    bool a4[4] = {0, 0, 1, 0};
    const bool* arr[4]{a1, a2, a3, a4};
    const int labelsTmp[4] = {2, 2, 3, 1};
    const bool usedSamplesTmp[4] = {false, false, false, false};
    double result = dt.calculateInformationGain(arr, labelsTmp, 4, 4, usedSamplesTmp, 2);
    cout << result << endl;
    return 0;
}