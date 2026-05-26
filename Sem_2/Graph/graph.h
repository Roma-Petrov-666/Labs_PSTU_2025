#ifndef GRAPH_H
#define GRAPH_H

#include <QSet>
#include <QMap>
#include <QPair>
#include <QVector>

class Graph {
public:
    void clear();
    void addVertex(int v);
    void removeVertex(int v);
    void addEdge(int from, int to, int weight);
    void removeEdge(int from, int to);
    void setEdgeWeight(int from, int to, int weight);
    int getWeight(int from, int to) const;
    QSet<int> getVertices() const;
    QVector<QVector<int>> getAdjacencyMatrix() const;
    QList<int> getNeighbors(int v) const;
    bool hasVertex(int v) const;
    bool hasEdge(int from, int to) const;

private:
    QSet<int> vertices;
    QMap<QPair<int,int>, int> edges;
};

#endif // GRAPH_H