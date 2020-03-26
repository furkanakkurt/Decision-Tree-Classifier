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

    void DecisionTreeNode::insertRightChild( int nFeature ) {
        DecisionTreeNode * right = new DecisionTreeNode(nFeature);
        rightChild = right;
        isLeaf = false;
    }

    void DecisionTreeNode::insertLeftChild( int nFeature ) {
        DecisionTreeNode * left = new DecisionTreeNode( nFeature );
        leftChild = left;
        isLeaf = false;
    }
    
    int DecisionTreeNode::getFeature() {
        return feature;
    }

    bool DecisionTreeNode::hasChildren() {
        if ( leftChild != NULL || rightChild != NULL ) {
            return true;
        } 
        return false;
    }

    DecisionTreeNode * DecisionTreeNode::getLeftChild() {
        return leftChild;
    }

    DecisionTreeNode * DecisionTreeNode::getLeftChild() {
        return rightChild;
    }