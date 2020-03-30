#include "DecisionTreeNode.h"
#include <iostream>

using namespace std;

    DecisionTreeNode::DecisionTreeNode( int nFeature ) {
        feature = nFeature;
        leftChild = NULL;
        rightChild = NULL;
        isLeaf = true;
    }

    DecisionTreeNode::DecisionTreeNode() {
        feature = -1;
        leftChild = NULL;
        rightChild = NULL;
        isLeaf = true;
    }

    DecisionTreeNode::~DecisionTreeNode() {
        if ( rightChild ) {
            delete rightChild;
        }

        if ( leftChild ) {
            delete leftChild;
        }
    }

    void DecisionTreeNode::insertRightChild( DecisionTreeNode * nRightChild ) {
        //cout << "right" << endl;
        rightChild = nRightChild;
    }

    void DecisionTreeNode::insertLeftChild( DecisionTreeNode * nLeftChild ) {
        //cout << "left " << endl;
        leftChild = nLeftChild;
    }

    void DecisionTreeNode::setFeature( int nFeature ) {
        feature = nFeature;
    }
    
    int DecisionTreeNode::getFeature() {
        return feature;
    }

    DecisionTreeNode * DecisionTreeNode::getLeftChild() {
        return leftChild;
    }

    DecisionTreeNode * DecisionTreeNode::getRightChild() {
        return rightChild;
    }

    bool DecisionTreeNode::hasChildren() {
        if ( leftChild != NULL || rightChild != NULL ) {
            return true;
        } 
        return false;
    }

