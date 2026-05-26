#ifndef TREEWIDGET_H
#define TREEWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QResizeEvent>
#include "tree.h"

class TreeWidget : public QGraphicsView {
    Q_OBJECT
public:
    explicit TreeWidget(QWidget *parent = nullptr);
    void setTree(BinarySearchTree *bst);
    void drawTree();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    BinarySearchTree *tree;
    QGraphicsScene *scene;
    void drawNode(TreeNode *node, QPointF pos, double xOffset, double yOffset, int level);
};

#endif