#include "DecisionTree.h"
//#include "DecisionTreeNode.h"
#include <iostream>

using namespace std;

int main() {

    DecisionTree dt;
    int arr[3] = {32,0,7};
    cout << dt.calculateEntropy(arr, 3) << endl;
    return 0;
}