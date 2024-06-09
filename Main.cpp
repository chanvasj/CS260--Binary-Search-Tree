#include <iostream>
#include <vector>
#include <cassert>

class Node {
public:
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    void add(int value) {
        if (root == nullptr) {
            root = new Node(value);
        } else {
            add(root, value);
        }
    }

    void remove(int value) {
        root = remove(root, value);
    }

    int findMin() {
        Node* minNode = findMin(root);
        return minNode ? minNode->value : -1; // Return -1 if the tree is empty
    }

    std::vector<int> inOrderTraversal() {
        std::vector<int> result;
        inOrderTraversal(root, result);
        return result;
    }

private:
    Node* root;

    void add(Node* node, int value) {
        if (value <= node->value) {
            if (node->left == nullptr) {
                node->left = new Node(value);
            } else {
                add(node->left, value);
            }
        } else {
            if (node->right == nullptr) {
                node->right = new Node(value);
            } else {
                add(node->right, value);
            }
        }
    }

    Node* remove(Node* node, int value) {
        if (node == nullptr) {
            return node;
        }
        if (value < node->value) {
            node->left = remove(node->left, value);
        } else if (value > node->value) {
            node->right = remove(node->right, value);
        } else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->value = temp->value;
            node->right = remove(node->right, temp->value);
        }
        return node;
    }

    Node* findMin(Node* node) {
        Node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    void inOrderTraversal(Node* node, std::vector<int>& result) {
        if (node != nullptr) {
            inOrderTraversal(node->left, result);
            result.push_back(node->value);
            inOrderTraversal(node->right, result);
        }
    }
};

// Tests

void testAddFunction() {
    BinarySearchTree bst;
    bst.add(10);
    assert(bst.inOrderTraversal() == std::vector<int>{10});

    bst.add(5);
    bst.add(15);
    assert((bst.inOrderTraversal() == std::vector<int>{5, 10, 15}));

}

void testRemoveFunction() {
    BinarySearchTree bst;
    bst.add(10);
    bst.add(5);
    bst.add(15);
    bst.remove(5);
    assert((bst.inOrderTraversal() == std::vector<int>{10, 15}));

    bst.add(5);
    bst.add(12);
    bst.remove(15);
    assert((bst.inOrderTraversal() == std::vector<int>{5, 10, 12}));

}

void testInOrderTraversal() {
    BinarySearchTree bst;
    bst.add(10);
    bst.add(5);
    bst.add(15);
    assert((bst.inOrderTraversal() == std::vector<int>{5, 10, 15}));

    bst.add(3);
    bst.add(7);
    bst.add(12);
    bst.add(20);
    assert((bst.inOrderTraversal() == std::vector<int>{3, 5, 7, 10, 12, 15, 20}));
}

void testFindMin() {
    BinarySearchTree bst;
    bst.add(10);
    bst.add(5);
    bst.add(15);
    bst.add(3);
    bst.add(7);
    assert(bst.findMin() == 3);

    bst.remove(3);
    assert(bst.findMin() == 5);

    bst.remove(5);
    assert(bst.findMin() == 7);
}

int main() {
    testAddFunction();
    testRemoveFunction();
    testInOrderTraversal();
    testFindMin();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}