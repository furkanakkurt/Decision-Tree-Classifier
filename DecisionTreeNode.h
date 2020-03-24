class DecisionTreeNode {

private:
    DecisionTreeNode * leftPtr;
    DecisionTreeNode * rightPtr;
    int feature;
    bool isLeaf;

public:
    ~DecisionTreeNode();
    DecisionTreeNode( int nFeature );
    void insertRightChild( int nFeature );
    void insertLeftChild( int nFeature );
    bool hasChildren();


};