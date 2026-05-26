#ifndef GRAPH_H
#define GRAPH_H

#include <QVector>
#include <QPointF>
#include <QMap>

class Graph
{
public:
    struct Vertex {
        int id;
        QPointF pos;
        Vertex() : id(-1), pos(0,0) {}
        Vertex(int i, QPointF p) : id(i), pos(p) {}
    };

    struct DirectedEdge {
        int from;
        int to;
        double weight;
        DirectedEdge() : from(-1), to(-1), weight(0) {}
        DirectedEdge(int f, int t, double w) : from(f), to(t), weight(w) {}
    };

    Graph();

    void addVertex(const QPointF &pos);
    void removeVertex(int id);
    void addDirectedEdge(int from, int to, double weight);
    void removeDirectedEdge(int from, int to);
    void setDirectedEdgeWeight(int from, int to, double weight);
    double edgeWeight(int from, int to) const;
    void moveVertex(int id, const QPointF &newPos);

    const QVector<Vertex>& vertices() const { return m_vertices; }
    const QVector<DirectedEdge>& edges() const { return m_edges; }
    int vertexCount() const { return m_vertices.size(); }
    int vertexIdAt(int index) const;
    int vertexIndex(int id) const;
    QVector<QVector<double>> adjacencyMatrix() const;

private:
    QVector<Vertex> m_vertices;
    QVector<DirectedEdge> m_edges;
    int m_nextId;
};

#endif
