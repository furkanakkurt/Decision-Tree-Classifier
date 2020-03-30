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
    void insertRightChild( DecisionTreeNode * dt );
    void insertLeftChild( DecisionTreeNode * dt );
    void setFeature( int nFeature );
    int getFeature();
    bool hasChildren();
    DecisionTreeNode * getLeftChild();
    DecisionTreeNode * getRightChild();

};