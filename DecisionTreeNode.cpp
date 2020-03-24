#include "DecisionTreeNode.h"
#include <iostream>

using namespace std;

    DecisionTreeNode::DecisionTreeNode( int nFeature ) {
        feature = nFeature;
        leftPtr = NULL;
        rightPtr = NULL;
        isLeaf = true;
    }

    DecisionTreeNode::DecisionTreeNode() {
        feature = -1;
        leftPtr = NULL;
        rightPtr = NULL;
        isLeaf = true;
    }

    DecisionTreeNode::~DecisionTreeNode() {
        if ( rightPtr ) {
            delete rightPtr;
        }

        if ( leftPtr ) {
            delete leftPtr;
        }
    }

    void DecisionTreeNode::insertRightChild( int nFeature ) {
        DecisionTreeNode * right = new DecisionTreeNode(nFeature);
        rightPtr = right;
        isLeaf = false;
    }

    void DecisionTreeNode::insertLeftChild( int nFeature ) {
        DecisionTreeNode * left = new DecisionTreeNode(nFeature);
        leftPtr = left;
        isLeaf = false;
    }
    
    int DecisionTreeNode::getFeature() {
        return feature;
    }

    bool DecisionTreeNode::hasChildren() {
        if ( leftPtr != NULL || rightPtr != NULL ) {
            return true;
        } 
        return false;
    }