#include "graphwidget.h"
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsTextItem>
#include <QPen>
#include <QBrush>
#include <QFont>
#include <cmath>
#include <QPointF>

// Для платформ, где M_PI не определена
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

static const int RADIUS = 30;
static const QColor NODE_COLOR = Qt::lightGray;
static const QColor NODE_BORDER = Qt::black;
static const QColor EDGE_COLOR = Qt::darkGray;

NodeItem::NodeItem(int id, QGraphicsItem* parent)
    : QGraphicsEllipseItem(-RADIUS, -RADIUS, 2*RADIUS, 2*RADIUS, parent), vertexId(id)
{
    setBrush(QBrush(NODE_COLOR));
    setPen(QPen(NODE_BORDER, 2));
    QGraphicsTextItem* text = new QGraphicsTextItem(QString::number(id), this);
    text->setFont(QFont("Arial", 12, QFont::Bold));
    text->setDefaultTextColor(Qt::black);
    text->setPos(-10, -10);
}

EdgeItem::EdgeItem(int from, int to, int weight, QGraphicsItem* parent)
    : QGraphicsLineItem(parent), from(from), to(to)
{
    setPen(QPen(EDGE_COLOR, 2));
    weightText = new QGraphicsTextItem(QString::number(weight), this);
    weightText->setFont(QFont("Arial", 10));
    weightText->setDefaultTextColor(Qt::blue);
    weightText->setPos(0, 0);
}

void EdgeItem::updatePosition(const QPointF& p1, const QPointF& p2)
{
    QLineF line(p1, p2);
    setLine(line);
    QPointF center = (p1 + p2) / 2;
    weightText->setPos(center.x() - 10, center.y() - 10);
}

void EdgeItem::setWeight(int w)
{
    weightText->setPlainText(QString::number(w));
}

GraphWidget::GraphWidget(Graph* graph, QWidget* parent)
    : QGraphicsView(parent), graph(graph)
{
    scene = new QGraphicsScene(this);
    setScene(scene);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::ScrollHandDrag);
    assignNodePositions();
    updateVisualization();
}

void GraphWidget::assignNodePositions()
{
    QList<int> vertices = graph->getVertices().values();
    if (vertices.isEmpty()) return;
    int n = vertices.size();
    double angleStep = 2 * M_PI / n;
    double radius = 200;
    QPointF center(300, 250);
    for (int i = 0; i < n; ++i) {
        double angle = i * angleStep;
        double x = center.x() + radius * cos(angle);
        double y = center.y() + radius * sin(angle);
        nodePositions[vertices[i]] = QPointF(x, y);
    }
}

void GraphWidget::drawNode(int id)
{
    if (!nodePositions.contains(id)) return;
    NodeItem* item = new NodeItem(id);
    item->setPos(nodePositions[id]);
    scene->addItem(item);
    nodeItems[id] = item;
}

void GraphWidget::drawEdge(int from, int to)
{
    if (!nodeItems.contains(from) || !nodeItems.contains(to)) return;
    int weight = graph->getWeight(from, to);
    if (weight == -1) weight = graph->getWeight(to, from);
    if (weight == -1) return;
    EdgeItem* edge = new EdgeItem(from, to, weight);
    edge->updatePosition(nodeItems[from]->pos(), nodeItems[to]->pos());
    scene->addItem(edge);
    edgeItems[{from, to}] = edge;
    edgeItems[{to, from}] = edge;
}

void GraphWidget::updateVisualization()
{
    scene->clear();
    nodeItems.clear();
    edgeItems.clear();
    assignNodePositions();
    QList<int> vertices = graph->getVertices().values();
    for (int v : vertices) drawNode(v);
    for (int from : vertices) {
        for (int to : graph->getNeighbors(from)) {
            if (from < to) drawEdge(from, to);
        }
    }
}