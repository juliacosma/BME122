#include "avl-tree.h"
#include <cmath>
#include <stack>
#include <iostream>

using namespace std;

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

int AVLTree::depthBelow(Node *n)
{
    if(n == NULL) return 0;
    else return ::max(depthBelow(n -> left), depthBelow(n -> right)) + 1;
}

int AVLTree::Difference(Node *n) {
    return depthBelow(n -> left) - depthBelow(n -> right);
}

bool AVLTree::singleLeftRotation(Node *parentNode, bool isLeftChild)
{
    Node* T = NULL;
    if(parentNode == NULL) {
        T = BinarySearchTree::getRootNode();
    }
    else {
        if(isLeftChild) T = parentNode -> left;
        else T = parentNode -> right;
    }

    Node* S = T->right;
    Node* B = S->left;
    S->left = T;
    T->right = B;

    if(parentNode == NULL) {
        *BinarySearchTree::getRootNodeAddress() = S;
    }
    else {
        if(isLeftChild) parentNode -> left = S;
        else parentNode -> right = S;
    }
    return true;
}

bool AVLTree::singleRightRotation(Node *parentNode, bool isLeftChild)
{
    Node* T = NULL;
    if(parentNode == NULL) {
        T = BinarySearchTree::getRootNode();
    }
    else {
        if(isLeftChild) T = parentNode -> left;
        else T = parentNode -> right;
    }

    Node* S = T -> left;
    Node* B = S -> right;
    S -> right = T;
    T -> left = B;

    if(parentNode == NULL) {
        *BinarySearchTree::getRootNodeAddress() = S;
    }
    else {
        if(isLeftChild) parentNode -> left = S;
        else parentNode -> right = S;
    }
    return true;
}

bool AVLTree::leftRightRotation(Node *parentNode, bool isLeftChild)
{
    Node* T = NULL;
    if(parentNode == NULL) {
        T = BinarySearchTree::getRootNode();
    }
    else {
        if(isLeftChild) T = parentNode -> left;
        else T = parentNode -> right;
    }

    singleLeftRotation(T, true);
    singleRightRotation(parentNode, isLeftChild);

    return true;
}

bool AVLTree::rightLeftRotation(Node *parentNode, bool isLeftChild)
{
    Node* T = NULL;
    if(parentNode == NULL) {
        T = BinarySearchTree::getRootNode();
    }
    else {
        if(isLeftChild) T = parentNode -> left;
        else T = parentNode -> right;
    }

    singleRightRotation(T, false);
    singleLeftRotation(parentNode, isLeftChild);

    return true;
}

std::stack<BinarySearchTree::Node*> *AVLTree::pathToNodeStack(DataType val)
{
    std::stack<BinarySearchTree::Node*> *s = new stack<BinarySearchTree::Node*>;
    Node* temp = BinarySearchTree::getRootNode();
    while(temp -> val != val) {
        s->push(temp);
        if(temp -> val > val) {
            temp = temp -> left;
        }
        else if(temp -> val < val) {
            temp = temp -> right;
        }
    }
    return s;
}

bool AVLTree::updateNodeBalance(std::stack<BinarySearchTree::Node*> *pathToNode, DataType val)
{
    pathToNode = pathToNodeStack(val);

    while(!pathToNode -> empty()) {
        Node* parentNode = pathToNode -> top();
        Node* childNode = NULL;
        bool isLeftChild;
        if(parentNode -> val >= val) {
            childNode = parentNode -> left;
            isLeftChild = true;
        }
        else {
            childNode = parentNode -> right;
            isLeftChild = false;
        }

        int balanceFactor = Difference(childNode);
        if(balanceFactor > 1) {
            if(Difference(childNode -> left) > 0) {
                singleRightRotation(parentNode, isLeftChild);
            }
            else {
                leftRightRotation(parentNode, isLeftChild);
            }
        }
        else if(balanceFactor < -1) {
            if(Difference(childNode -> right) < 0) {
                singleLeftRotation(parentNode, isLeftChild);
            }
            else {
                rightLeftRotation(parentNode, isLeftChild);
            }
        }
        pathToNode -> pop();
    }

    //if rotated node is root
    Node* childNode = getRootNode();

    int balanceFactor = Difference(childNode);
    if(balanceFactor > 1) {
        if(Difference(childNode -> left) > 0) {
            singleRightRotation(NULL, true);
        }
        else {
            leftRightRotation(NULL, true);
        }
    }
    else if(balanceFactor < -1) {
        if(Difference(childNode -> right) < 0) {
            singleLeftRotation(NULL, true);
        }
        else {
            rightLeftRotation(NULL, true);
        }
    }

    return true;
}

bool AVLTree::updateNodeBalanceRemove(std::stack<BinarySearchTree::Node*> *pathToNode, DataType val)
{
    pathToNode = pathToNodeStack(val);

    while(!pathToNode -> empty()) {
        Node* parentNode = pathToNode -> top();
        Node* childNode = NULL;
        bool isLeftChild;
        if(parentNode -> val >= val) {
            childNode = parentNode -> left;
            isLeftChild = true;
        }
        else {
            childNode = parentNode -> right;
            isLeftChild = false;
        }

        int balanceFactor = Difference(childNode);
        if(balanceFactor > 1) {
            if(Difference(childNode -> left) >= 0) {
                singleRightRotation(parentNode, isLeftChild);
            }
            else {
                leftRightRotation(parentNode, isLeftChild);
            }
        }
        else if(balanceFactor < -1) {
            if(Difference(childNode -> right) <= 0) {
                singleLeftRotation(parentNode, isLeftChild);
            }
            else {
                rightLeftRotation(parentNode, isLeftChild);
            }
        }
        pathToNode -> pop();
    }

    //if rotated node is root
    Node* childNode = getRootNode();

    int balanceFactor = Difference(childNode);
    if(balanceFactor > 1) {
        if(Difference(childNode -> left) >= 0) {
            singleRightRotation(NULL, true);
        }
        else {
            leftRightRotation(NULL, true);
        }
    }
    else if(balanceFactor < -1) {
        if(Difference(childNode -> right) <= 0) {
            singleLeftRotation(NULL, true);
        }
        else {
            rightLeftRotation(NULL, true);
        }
    }

    return true;
}

bool AVLTree::insert(DataType val)
{
    BinarySearchTree::insert(val);
    return updateNodeBalance(pathToNodeStack(val), val);
}

bool AVLTree::remove(DataType val)
{
    DataType parentOfRemovedNode;
    stack<Node*> *s = pathToNodeStack(val);
    BinarySearchTree::remove(val);
    if(getRootNode() != NULL) {
        if(s -> empty()) {
            parentOfRemovedNode = getRootNode() -> val;
        }
        else {
            parentOfRemovedNode = s -> top() -> val;
        }
        return updateNodeBalanceRemove(pathToNodeStack(parentOfRemovedNode), parentOfRemovedNode);
    }
    else {
        return true;
    }
}
