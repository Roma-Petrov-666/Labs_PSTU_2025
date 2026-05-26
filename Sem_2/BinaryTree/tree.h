#ifndef TREE_H
#define TREE_H

#include <QList>
#include <QString>

struct TreeNode {
    int key;
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int k, int v) : key(k), value(v), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    TreeNode *root;

    bool search(TreeNode *node, int key, int &value) const;
    TreeNode* remove(TreeNode *node, int key);
    TreeNode* findMin(TreeNode *node);
    TreeNode* buildBalanced(const QList<TreeNode*> &nodes, int start, int end);
    void preOrder(TreeNode *node, QList<QString> &result) const;
    void inOrder(TreeNode *node, QList<QString> &result) const;
    void postOrder(TreeNode *node, QList<QString> &result) const;
    void getSortedNodes(TreeNode *node, QList<TreeNode*> &nodes) const;
    void insert(TreeNode *&node, int key, int value);
    void clear(TreeNode *node);
    void findMinValue(TreeNode *node, int &minVal) const;

public:
    BinarySearchTree();
    ~BinarySearchTree();

    void insert(int key, int value);
    void balance();
    void clear();
    bool remove(int key);
    bool search(int key, int &value) const;
    QList<QString> preOrder() const;
    QList<QString> inOrder() const;
    QList<QString> postOrder() const;
    TreeNode* getRoot() const { return root; }
    int countNodes(TreeNode *node) const;
    int sumValues(TreeNode *node) const;
    double average() const;

    int findMinValue() const;
    void createBalanced(const QList<int> &keys, const QList<int> &values);
};

#endif