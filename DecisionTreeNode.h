class DecisionTreeNode {

private:
    DecisionTreeNode * leftChild;
    DecisionTreeNode * rightChild;
    int feature;
    bool isLeaf;

public:
    ~DecisionTreeNode();
    DecisionTreeNode();
    DecisionTreeNode( int nFeature );
    void insertRightChild( int nFeature );
    void insertLeftChild( int nFeature );
    int getFeature();
    bool hasChildren();
    DecisionTreeNode * getLeftChild();
    DecisionTreeNode * getRightChild();

};