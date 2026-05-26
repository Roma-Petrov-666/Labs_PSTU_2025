#include "graphwidget.h"
#include <QMouseEvent>
#include <QPen>
#include <QBrush>
#include <cmath>
#include <QGraphicsTextItem>
#include <QPainterPath>

GraphWidget::GraphWidget(QWidget *parent)
    : QGraphicsView(parent), m_graph(nullptr), m_scene(new QGraphicsScene(this)),
      m_draggingVertex(false), m_draggedVertexId(-1)
{
    setScene(m_scene);
    setRenderHint(QPainter::Antialiasing);
    setDragMode(QGraphicsView::NoDrag);
}

void GraphWidget::setGraph(Graph *g) {
    m_graph = g;
    updateView();
}

void GraphWidget::drawArrow(const QPointF &from, const QPointF &to, const QColor &color, double offset,
                            QGraphicsLineItem **outLine, QGraphicsPolygonItem **outArrow) {
    QLineF line(from, to);
    double angle = std::atan2(-line.dy(), line.dx());
    QPointF arrowP1 = line.pointAt(0.9) + QPointF( sin(angle + M_PI/3) * 10, cos(angle + M_PI/3) * 10 );
    QPointF arrowP2 = line.pointAt(0.9) + QPointF( sin(angle + M_PI - M_PI/3) * 10, cos(angle + M_PI - M_PI/3) * 10 );

    QPointF perp(-line.dy(), line.dx());
    double len = std::sqrt(perp.x()*perp.x() + perp.y()*perp.y());
    if (len > 1e-6) perp /= len;
    QPointF shift = perp * offset;

    QGraphicsLineItem *lineItem = m_scene->addLine(QLineF(from + shift, to + shift), QPen(color, 2));
    QPolygonF arrowHead;
    arrowHead << (line.pointAt(0.9) + shift);
    arrowHead << arrowP1 + shift;
    arrowHead << arrowP2 + shift;
    QGraphicsPolygonItem *arrowItem = m_scene->addPolygon(arrowHead, QPen(color, 1), QBrush(color));
    if (outLine) *outLine = lineItem;
    if (outArrow) *outArrow = arrowItem;
}

void GraphWidget::highlightPath(const QVector<int> &pathIds) {

    for (auto it = m_edgeGraphics.begin(); it != m_edgeGraphics.end(); ++it) {
        it.value().line->setPen(QPen(Qt::black, 2));
        it.value().arrow->setBrush(QBrush(Qt::black));
        it.value().arrow->setPen(QPen(Qt::black, 1));
    }
    if (pathIds.size() < 2) return;
    for (int i = 0; i < pathIds.size() - 1; ++i) {
        int from = pathIds[i];
        int to = pathIds[i+1];
        int key = from * 10000 + to;
        if (m_edgeGraphics.contains(key)) {
            m_edgeGraphics[key].line->setPen(QPen(Qt::green, 3));
            m_edgeGraphics[key].arrow->setBrush(QBrush(Qt::green));
            m_edgeGraphics[key].arrow->setPen(QPen(Qt::green, 1));
        }
    }
}

void GraphWidget::updateView() {
    m_scene->clear();
    m_vertexItems.clear();
    m_edgeGraphics.clear();
    if (!m_graph) return;

    QSet<QPair<int,int>> edgeSet;
    for (const auto &e : m_graph->edges()) {
        edgeSet.insert(qMakePair(e.from, e.to));
    }

    for (const auto &e : m_graph->edges()) {
        int idx1 = m_graph->vertexIndex(e.from);
        int idx2 = m_graph->vertexIndex(e.to);
        if (idx1 == -1 || idx2 == -1) continue;
        QPointF p1 = m_graph->vertices()[idx1].pos;
        QPointF p2 = m_graph->vertices()[idx2].pos;

        bool hasReverse = edgeSet.contains(qMakePair(e.to, e.from));
        double offset = 0.0;
        if (hasReverse) {
            offset = (e.from < e.to) ? 8.0 : -8.0;
        }
        EdgeGraphics eg;
        drawArrow(p1, p2, Qt::black, offset, &eg.line, &eg.arrow);
        int key = e.from * 10000 + e.to;
        m_edgeGraphics[key] = eg;

        QLineF line(p1, p2);
        QPointF mid = line.pointAt(0.5);
        QPointF dir = line.p2();
        double len = std::sqrt(dir.x()*dir.x() + dir.y()*dir.y());
        if (len > 1e-6) {
            QPointF perp(-dir.y()/len, dir.x()/len);
            QPointF shift = perp * offset;
            QGraphicsTextItem *text = m_scene->addText(QString::number(e.weight, 'f', 1));
            text->setDefaultTextColor(Qt::darkBlue);
            text->setPos(mid + shift);
        }
    }

    for (const Graph::Vertex &v : m_graph->vertices()) {
        QGraphicsEllipseItem *circle = m_scene->addEllipse(v.pos.x() - 15, v.pos.y() - 15, 30, 30,
                                                            QPen(Qt::black), QBrush(Qt::cyan));
        QGraphicsTextItem *label = m_scene->addText(QString::number(v.id));
        label->setDefaultTextColor(Qt::black);
        label->setPos(v.pos.x() - 8, v.pos.y() - 8);
        m_vertexItems[v.id] = circle;
    }
}

void GraphWidget::mousePressEvent(QMouseEvent *event) {
    QPointF scenePos = mapToScene(event->pos());
    int clickedId = -1;
    for (const Graph::Vertex &v : m_graph->vertices()) {
        QPointF p = v.pos;
        double dx = scenePos.x() - p.x();
        double dy = scenePos.y() - p.y();
        if (std::sqrt(dx*dx + dy*dy) <= 20) {
            clickedId = v.id;
            break;
        }
    }
    if (event->button() == Qt::LeftButton && clickedId != -1) {
        m_draggingVertex = true;
        m_draggedVertexId = clickedId;
    }
    QGraphicsView::mousePressEvent(event);
}

void GraphWidget::mouseMoveEvent(QMouseEvent *event) {
    if (m_draggingVertex && m_draggedVertexId != -1) {
        QPointF newPos = mapToScene(event->pos());
        emit vertexMoved(m_draggedVertexId, newPos);
        updateView();
    }
    QGraphicsView::mouseMoveEvent(event);
}

void GraphWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (m_draggingVertex) {
        m_draggingVertex = false;
        m_draggedVertexId = -1;
    }
    QGraphicsView::mouseReleaseEvent(event);
}

QGraphicsEllipseItem* GraphWidget::findVertexItem(int id) const {
    return m_vertexItems.value(id, nullptr);
}
