#include "DecisionTree.h"
//#include "DecisionTreeNode.h"
#include <iostream>

using namespace std;

int main() {

    DecisionTree d;

	const bool test[21]{ 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,1 ,0 ,0, 0, 0 ,0, 0, 1, 0, 0, 1, 1 };
	const bool test2[21]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
	
	const int a = 5;


	d.train("train_data.txt", 498, 21);
	double dd = d.test("test_data.txt", 473);
	cout << "Accuracy after training and testing: " << dd << endl;
	
	cout << "My prediction for { 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,1 ,0 ,0, 0, 0 ,0, 0, 1, 0, 0, 1, 1 } is class " << d.predict(test) << endl;
	cout << "My prediction for { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 } is class " << d.predict(test2) << endl;
	cout << endl;
	d.print();
    return 0;
}