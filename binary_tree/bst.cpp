#include <limits>

#include "common.h"

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right)
	    : val(x), left(left), right(right) {}
};

class binarySearchTree {
public:
	// The correct solution for checking if a tree is a valid BST
	bool isValidBST(TreeNode *root) {
		// Use long long to handle edge cases with INT_MIN and INT_MAX
		return isValidBSTHelper(root, LLONG_MIN, LLONG_MAX);
	}

private:
	bool isValidBSTHelper(TreeNode *root, long long minVal, long long maxVal) {
		// Empty trees are valid BSTs
		if (root == nullptr) return true;

		// Current node's value must be in range (minVal, maxVal)
		if (root->val <= minVal || root->val >= maxVal) return false;

		// Left subtree values must be in range (minVal, root->val)
		// Right subtree values must be in range (root->val, maxVal)
		return isValidBSTHelper(root->left, minVal, root->val) &&
		       isValidBSTHelper(root->right, root->val, maxVal);
	}
};

int main() {
	binarySearchTree bst;

	// Test Case 1: Valid BST
	TreeNode *validRoot = new TreeNode(2);
	validRoot->left = new TreeNode(1);
	validRoot->right = new TreeNode(3);
	cout << "Test Case 1 (Valid BST): "
	     << (bst.isValidBST(validRoot) ? "Valid" : "Invalid") << endl;

	// Test Case 2: Invalid BST
	TreeNode *invalidRoot = new TreeNode(2);
	invalidRoot->left = new TreeNode(1);
	invalidRoot->right =
	    new TreeNode(1);  // Violates BST property (should be > 2)
	cout << "Test Case 2 (Invalid BST): "
	     << (bst.isValidBST(invalidRoot) ? "Valid" : "Invalid") << endl;

	// Test Case 3: More complex valid BST
	TreeNode *complexRoot = new TreeNode(5);
	complexRoot->left = new TreeNode(3);
	complexRoot->right = new TreeNode(7);
	complexRoot->left->left = new TreeNode(2);
	complexRoot->left->right = new TreeNode(4);
	complexRoot->right->left = new TreeNode(6);
	complexRoot->right->right = new TreeNode(8);
	cout << "Test Case 3 (Complex Valid BST): "
	     << (bst.isValidBST(complexRoot) ? "Valid" : "Invalid") << endl;

	// Test Case 4: Tricky invalid case
	TreeNode *trickyRoot = new TreeNode(5);
	trickyRoot->left = new TreeNode(1);
	trickyRoot->right = new TreeNode(7);
	trickyRoot->right->left =
	    new TreeNode(3);  // Violates BST property (should be > 5)
	trickyRoot->right->right = new TreeNode(8);
	cout << "Test Case 4 (Tricky Invalid BST): "
	     << (bst.isValidBST(trickyRoot) ? "Valid" : "Invalid") << endl;

	// Clean up memory
	// For simplicity, not implementing full deletion logic here

	return 0;
}