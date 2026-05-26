#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QMap>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include "graph.h"

class NodeItem;
class EdgeItem;

class GraphWidget : public QGraphicsView {
    Q_OBJECT
public:
    explicit GraphWidget(Graph* graph, QWidget* parent = nullptr);
    void updateVisualization();

private:
    Graph* graph;
    QGraphicsScene* scene;
    QMap<int, NodeItem*> nodeItems;
    QMap<QPair<int,int>, EdgeItem*> edgeItems;
    QMap<int, QPointF> nodePositions;

    void drawNode(int id);
    void drawEdge(int from, int to);
    void assignNodePositions();
};

class NodeItem : public QGraphicsEllipseItem {
public:
    NodeItem(int id, QGraphicsItem* parent = nullptr);
    int id() const { return vertexId; }
private:
    int vertexId;
};

class EdgeItem : public QGraphicsLineItem {
public:
    EdgeItem(int from, int to, int weight, QGraphicsItem* parent = nullptr);
    void updatePosition(const QPointF& p1, const QPointF& p2);
    void setWeight(int w);
private:
    int from, to;
    QGraphicsTextItem* weightText;
};

#endif