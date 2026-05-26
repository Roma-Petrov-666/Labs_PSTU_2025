#include "treewidget.h"
#include <QPen>
#include <QBrush>

TreeWidget::TreeWidget(QWidget *parent) : QGraphicsView(parent), tree(nullptr) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
}

void TreeWidget::setTree(BinarySearchTree *bst) {
    tree = bst;
}

void TreeWidget::drawTree() {
    scene->clear();
    if (!tree || !tree->getRoot()) return;

    int width = viewport()->width();
    int height = viewport()->height();
    double startX = width / 2.0;
    double startY = 40;
    double xOffset = width / 4.0;
    double yOffset = 60;

    drawNode(tree->getRoot(), QPointF(startX, startY), xOffset, yOffset, 0);
}

void TreeWidget::drawNode(TreeNode *node, QPointF pos, double xOffset, double yOffset, int level) {
    if (!node) return;

    QPen pen(Qt::black);
    QBrush brush(Qt::lightGray);
    scene->addEllipse(pos.x() - 20, pos.y() - 20, 40, 40, pen, brush);
    QString text = QString("%1\n%2").arg(node->key).arg(node->value);
    scene->addText(text)->setPos(pos.x() - 15, pos.y() - 12);

    if (node->left) {
        QPointF leftPos(pos.x() - xOffset, pos.y() + yOffset);
        scene->addLine(pos.x(), pos.y(), leftPos.x(), leftPos.y(), QPen(Qt::black));
        drawNode(node->left, leftPos, xOffset / 2, yOffset, level + 1);
    }
    if (node->right) {
        QPointF rightPos(pos.x() + xOffset, pos.y() + yOffset);
        scene->addLine(pos.x(), pos.y(), rightPos.x(), rightPos.y(), QPen(Qt::black));
        drawNode(node->right, rightPos, xOffset / 2, yOffset, level + 1);
    }
}

void TreeWidget::resizeEvent(QResizeEvent *event) {
    QGraphicsView::resizeEvent(event);
    drawTree();
}