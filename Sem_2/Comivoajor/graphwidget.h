#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMap>
#include "graph.h"

class GraphWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GraphWidget(QWidget *parent = nullptr);
    void setGraph(Graph *g);
    void highlightPath(const QVector<int> &pathIds);

signals:
    void vertexMoved(int id, QPointF pos);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void updateView();
    void drawArrow(const QPointF &from, const QPointF &to, const QColor &color, double offset,
                   QGraphicsLineItem **outLine, QGraphicsPolygonItem **outArrow);
    QGraphicsEllipseItem* findVertexItem(int id) const;

    Graph *m_graph;
    QGraphicsScene *m_scene;
    QMap<int, QGraphicsEllipseItem*> m_vertexItems;
    struct EdgeGraphics {
        QGraphicsLineItem *line;
        QGraphicsPolygonItem *arrow;
    };
    QMap<int, EdgeGraphics> m_edgeGraphics;
    bool m_draggingVertex;
    int m_draggedVertexId;
};

#endif
