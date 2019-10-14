#include <iostream>
#include <algorithm>
#include "Node.cpp"
const int ALLOWED_IMBALANCE = 1;
class AVL_Tree {

public:

	//
	//default constructor
	//
	AVL_Tree(int* arr, int size)
		:root_(NULL)
	{

		for (int i = 0; i < size; i++) {
			insert(arr[i]);
		}
		show(root_);

	}

	//
	//destructor
	//
	~AVL_Tree() {
		//delete[] root_;
	}

	//
	//inserts new node into tree
	//
	void insert(int num) {
		insert(num, root_);
	}

	//
	//insert node in subtree with root t
	//
	void insert(int num, Node* & t) {
		if (t == NULL) {
			t = new Node(num, NULL, NULL);
		}
		else if (num < t->data_) {
			insert(num, t->left_);
		}
		else if (num > t->data_) {
			insert(num, t->right_);
		}

		balance(t);
	}

	//
	//balances the tree
	//
	void balance(Node* & t) {
		if (t == NULL) return;

		if (height(t->left_) - height(t->right_) > ALLOWED_IMBALANCE) {
			//case 1
			if (height(t->left_->left_) >= height(t->left_->right_)) {
				rotate_left(t);
			}
			//case 2
			else {
				double_rotate_left(t);
			}
		}
		else if (height(t->right_) - height(t->left_) > ALLOWED_IMBALANCE) {
			//case 4
			if (height(t->right_->right_) >= height(t->right_->left_)) {
				rotate_right(t);
			}
			//case 3
			else {
				double_rotate_right(t);
			}
		}

		t->height_ = std::max(height(t->left_), height(t->right_)) + 1;

	}

	//
	//rotate_left
	//
	//single rotation on left subtree of element t
	//
	void rotate_left(Node* & k2) {
		Node* k1 = k2->left_;
		k2->left_ = k1->right_;
		k1->right_ = k2;
		k2->height_ = std::max(height(k2->left_), height(k2->right_)) + 1;
		k1->height_ = std::max(height(k1->left_), k2->height_) + 1;
		k2 = k1;
	}

	//
	//rotate_right
	//
	//single rotation on right subtree of element t
	//
	void rotate_right(Node*& k1) {
		Node* k2 = k1->right_;
		k1->right_ = k2->left_;
		k2->left_ = k1;
		k1->height_ = std::max(height(k1->left_), height(k1->right_)) + 1;
		k2->height_ = std::max(height(k2->left_), k1->height_) + 1;
		k1 = k2;
	}

	//
	//double rotation on left subtree of element t
	//
	void double_rotate_left(Node*& k3) {
		rotate_right(k3->left_);
		rotate_left(k3);
	}

	//
	//double rotation on right subtree of element t
	//
	void double_rotate_right(Node*& k1) {
		rotate_left(k1->right_);
		rotate_right(k1);
	}

	//
	//returns height
	//
	int height(Node* t) {
		if (t == NULL) {
			return 0;
		}
		else {
			return t->height_;
		}
	}

	//
	//Traverses tree starting at node t, printing via method specified in class by instructor
	//
	void show(Node* t) {

		print_node(t);
		if (t->left_ != NULL) {
			show(t->left_);
		}
		if (t->right_ != NULL) {
			show(t->right_);
		}
	}

	//
	//prints tree members in order of Parent, left_child, right_child.
	//
	void print_node(Node* t) {

		std::cout << t->data_ << " ";
		if (t->left_ != NULL) {
			std::cout << t->left_->data_ << " ";
		}
		if (t->right_ != NULL) {
			std::cout << t->right_->data_;
		}
		std::cout << std::endl;

	}


private:
	Node* root_;

};