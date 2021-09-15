#include "binary-search-tree.h"
#include <iostream>
#include <queue>

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

using namespace std;

BinarySearchTree::Node::Node(DataType newval)
{
    left = NULL;
    right = NULL;
    val = newval;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    if(n == NULL) return 0;
    if(n -> left == NULL && n -> right == NULL) return 0;
    int leftDepth = getNodeDepth(n -> left);
    int rightDepth = getNodeDepth(n -> right);

    if(leftDepth > rightDepth) return leftDepth + 1;
    else return rightDepth + 1;
}

BinarySearchTree::BinarySearchTree()
{
    root_ = NULL;
    size_ = 0;
}

void BinarySearchTree::DestroyTree(Node *n)
{
    if(n) {
        DestroyTree(n -> left);
        DestroyTree(n -> right);
        delete n;
    }
}
BinarySearchTree::~BinarySearchTree()
{
    DestroyTree(root_);
}

unsigned int BinarySearchTree::size() const
{
    return size_;
}

DataType BinarySearchTree::max() const
{
    Node* temp = root_;
    DataType max = temp -> val;
    while(temp -> right != NULL) {
        temp = temp -> right;
        max = temp -> val;
    }
    return max;
}

DataType BinarySearchTree::min() const
{
    Node* temp = root_;
    DataType min = temp -> val;
    while(temp -> left != NULL) {
        temp = temp -> left;
        min = temp -> val;
    }
    return min;
}

unsigned int BinarySearchTree::depth() const
{
    getNodeDepth(root_);
}

void BinarySearchTree::PrintInOrder(Node* n) const
{
    if(n == NULL) return;
    PrintInOrder(n -> left);
    cout << n -> val;
    PrintInOrder(n -> right);
}

void BinarySearchTree::print() const
{
    PrintInOrder(root_);
}

bool BinarySearchTree::exists(DataType val) const
{
    if(size() == 0) return false;
    Node* temp = root_;
    while(temp != NULL) {
        if(temp -> val == val) {
            return true;
        }
        else if(temp -> val > val) {
            temp = temp -> left;
        }
        else if(temp -> val < val) {
            temp = temp -> right;
        }
    }
    return false;
}

Node* BinarySearchTree::getRootNode()
{
    return root_;
}

Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

bool BinarySearchTree::insert(DataType val)
{
    if (exists(val)) return false;
    Node* newNode = new Node(val);
    Node* temp = root_;

    if(root_ == NULL) {
        root_ = newNode;
        size_++;
        return true;
    }

    while(true) {
        if(temp -> val > val) {
            if(temp -> left == NULL) {
                temp -> left = newNode;
                size_++;
                return true;
            }
            temp = temp -> left;
        }
        else if (temp -> val < val) {
            if(temp -> right == NULL) {
                temp -> right = newNode;
                size_++;
                return true;
            }
            temp = temp -> right;
        }
    }
}

Node* findPredecessor(Node* ptr) {
    Node* predecessor = ptr -> left;
    while(predecessor -> right != NULL) {
        predecessor = predecessor -> right;
    }
    return predecessor;
}

bool BinarySearchTree::remove(DataType val)
{
    Node* parent = NULL;
    Node* temp = root_;

    if (!exists(val)) return false;

    //traverse tree to find target node
    while(temp != NULL && temp -> val != val) {
        parent = temp;
        if(temp -> val > val) temp = temp -> left;
        else if(temp -> val < val) temp = temp -> right;
    }

    //if only one node in tree
    if (size() == 1) {
        root_ = NULL;
        delete temp;
        size_--;
        return true;
    }

    //if node has no child
    else if(temp -> left == NULL && temp -> right == NULL) {
        if(temp != root_) {
            if(parent -> left == temp) {
                parent -> left = NULL;
            }
            else {
                parent -> right = NULL;
            }
        }
        else {
            root_ = NULL;
        }
        delete temp;
        size_--;
        return true;
    }

    //if node has two children, replace with predecessor
    else if (temp -> left && temp -> right){
        Node* predecessor = findPredecessor(temp);
        DataType swap = predecessor -> val;
        remove(predecessor -> val);
        temp -> val = swap;

        return true;
    }

    //if node has one child
    else {
        Node* child;
        if(temp -> left) {
            child = temp -> left;
        } else {
            child = temp -> right;
        }

        if(temp != root_) {
            if(temp == parent -> left) {
                parent -> left = child;
            }
            else {
                parent -> right = child;
            }
        }
        else {
            root_ = child;
        }
        delete temp;
        size_--;
        return true;
    }
}
