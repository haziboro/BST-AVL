//Node struct for AVL Tree
struct Node {
	int data_;
	Node* left_;
	Node* right_;
	int height_;
	
	Node(int num, Node* lt, Node* rt, int h = 0)
		:data_(num), left_(lt), right_(rt), height_(h) {}
	friend class AVL_Tree;
};