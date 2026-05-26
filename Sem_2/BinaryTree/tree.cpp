#include "tree.h"
#include <algorithm>

BinarySearchTree::BinarySearchTree() : root(nullptr) {}

BinarySearchTree::~BinarySearchTree() {
    clear();
}

void BinarySearchTree::insert(TreeNode *&node, int key, int value) {
    if (node == nullptr) {
        node = new TreeNode(key, value);
    }
    else if (key < node->key) {
        insert(node->left, key, value);
    }
    else if (key > node->key) {
        insert(node->right, key, value);
    }
}

void BinarySearchTree::insert(int key, int value) {
    insert(root, key, value);
}

TreeNode* BinarySearchTree::findMin(TreeNode *node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

TreeNode* BinarySearchTree::remove(TreeNode *node, int key) {
    if (!node) {
        return nullptr;
    }

    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
        if (!node->left) {
            TreeNode *rightChild = node->right;
            delete node;
            return rightChild;
        }
        else if (!node->right) {
            TreeNode *leftChild = node->left;
            delete node;
            return leftChild;
        }
        else {
            TreeNode *minNode = findMin(node->right);
            node->key = minNode->key;
            node->value = minNode->value;
            node->right = remove(node->right, minNode->key);
        }
    }
    return node;
}

bool BinarySearchTree::remove(int key) {
    int dummy;
    if (!search(key, dummy)) {
        return false;
    }
    root = remove(root, key);
    return true;
}

bool BinarySearchTree::search(TreeNode *node, int key, int &value) const {
    if (!node) {
        return false;
    }
    if (key == node->key) {
        value = node->value;
        return true;
    }
    if (key < node->key) {
        return search(node->left, key, value);
    }
    return search(node->right, key, value);
}

bool BinarySearchTree::search(int key, int &value) const {
    return search(root, key, value);
}

void BinarySearchTree::preOrder(TreeNode *node, QList<QString> &result) const {
    if (node) {
        result.append(QString("%1: %2").arg(node->key).arg(node->value));
        preOrder(node->left, result);
        preOrder(node->right, result);
    }
}

QList<QString> BinarySearchTree::preOrder() const {
    QList<QString> result;
    preOrder(root, result);
    return result;
}

void BinarySearchTree::inOrder(TreeNode *node, QList<QString> &result) const {
    if (node) {
        inOrder(node->left, result);
        result.append(QString("%1: %2").arg(node->key).arg(node->value));
        inOrder(node->right, result);
    }
}

QList<QString> BinarySearchTree::inOrder() const {
    QList<QString> result;
    inOrder(root, result);
    return result;
}

void BinarySearchTree::postOrder(TreeNode *node, QList<QString> &result) const {
    if (node) {
        postOrder(node->left, result);
        postOrder(node->right, result);
        result.append(QString("%1: %2").arg(node->key).arg(node->value));
    }
}

QList<QString> BinarySearchTree::postOrder() const {
    QList<QString> result;
    postOrder(root, result);
    return result;
}

void BinarySearchTree::getSortedNodes(TreeNode *node, QList<TreeNode*> &nodes) const {
    if (node) {
        getSortedNodes(node->left, nodes);
        nodes.append(node);
        getSortedNodes(node->right, nodes);
    }
}

TreeNode* BinarySearchTree::buildBalanced(const QList<TreeNode*> &nodes, int start, int end) {
    if (start > end) {
        return nullptr;
    }
    int mid = (start + end) / 2;
    TreeNode *node = new TreeNode(nodes[mid]->key, nodes[mid]->value);
    node->left = buildBalanced(nodes, start, mid - 1);
    node->right = buildBalanced(nodes, mid + 1, end);
    return node;
}

void BinarySearchTree::balance() {
    QList<TreeNode*> nodes;
    getSortedNodes(root, nodes);
    clear();
    root = buildBalanced(nodes, 0, nodes.size() - 1);
}

void BinarySearchTree::clear(TreeNode *node) {
    if (node) {
        clear(node->left);
        clear(node->right);
        delete node;
    }
}

void BinarySearchTree::clear() {
    clear(root);
    root = nullptr;
}

int BinarySearchTree::countNodes(TreeNode *node) const {
    if (!node) {
        return 0;
    }
    return 1 + countNodes(node->left) + countNodes(node->right);
}

int BinarySearchTree::sumValues(TreeNode *node) const {
    if (!node) {
        return 0;
    }
    return node->value + sumValues(node->left) + sumValues(node->right);
}

double BinarySearchTree::average() const {
    int cnt = countNodes(root);
    if (cnt == 0) {
        return 0.0;
    }
    return static_cast<double>(sumValues(root)) / cnt;
}

void BinarySearchTree::findMinValue(TreeNode *node, int &minVal) const {
    if (!node) return;
    if (node->value < minVal) {
        minVal = node->value;
    }
    findMinValue(node->left, minVal);
    findMinValue(node->right, minVal);
}

int BinarySearchTree::findMinValue() const {
    if (!root) {
        return 0;
    }
    int minVal = root->value;
    findMinValue(root, minVal);
    return minVal;
}

void BinarySearchTree::createBalanced(const QList<int> &keys, const QList<int> &values) {
    clear();
    if (keys.isEmpty() || keys.size() != values.size()) return;

    QList<TreeNode*> nodes;
    for (int i = 0; i < keys.size(); ++i) {
        nodes.append(new TreeNode(keys[i], values[i]));
    }
    std::sort(nodes.begin(), nodes.end(), [](TreeNode *a, TreeNode *b) {
        return a->key < b->key;
    });
    root = buildBalanced(nodes, 0, nodes.size() - 1);
}