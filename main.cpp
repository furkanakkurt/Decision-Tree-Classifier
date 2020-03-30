#include "DecisionTree.h"
//#include "DecisionTreeNode.h"
#include <iostream>

using namespace std;

int main() {

    DecisionTree d;

	const bool test[21]{ 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,1 ,0 ,0, 0, 0 ,0, 0, 1, 0, 0, 1, 1 };
	const bool test2[21]{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 };
	
	const int a = 5;

	//bool* a0 = new bool[5]{0,0,1,0,1};
	//bool* a1 = new bool[5]{ 1,0,1,0,1 };
	//bool* a2 = new bool[5]{ 1,1,0,1,0 };
	//bool* a3 = new bool[5]{ 0,0,1,1,0 };
	//const bool* const* data = new bool* [4]{a0,a1,a2,a3};
	//const int* labels = new int[4]{2,2,2,1};
	//d.train((const bool**)data, labels, 4, 5);
	d.train("train_data.txt", 498, 21);
	
	cout << "Accuracy after training and testing: " << d.test("test_data.txt", 473) << endl;
	
	cout << "My prediction for { 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,1 ,0 ,0, 0, 0 ,0, 0, 1, 0, 0, 1, 1 } is class " << d.predict(test) << endl;
	cout << "My prediction for { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1 } is class " << d.predict(test2) << endl;
	cout << endl;
	d.print();
    return 0;
}