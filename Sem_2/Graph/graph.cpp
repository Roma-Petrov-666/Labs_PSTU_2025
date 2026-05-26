#include "graph.h"
#include <algorithm>

void Graph::addVertex(int v) {
    vertices.insert(v);
}

void Graph::removeVertex(int v) {
    vertices.remove(v);
    QList<QPair<int,int>> toErase;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (it.key().first == v || it.key().second == v) {
            toErase.append(it.key());
        }
    }
    for (const auto& e : toErase) {
        edges.remove(e);
    }
}

void Graph::addEdge(int from, int to, int weight) {
    if (hasVertex(from) && hasVertex(to)) {
        edges[{from, to}] = weight;
        edges[{to, from}] = weight;
    }
}

void Graph::removeEdge(int from, int to) {
    edges.remove({from, to});
    edges.remove({to, from});
}

void Graph::setEdgeWeight(int from, int to, int weight) {
    if (edges.contains({from, to})) {
        edges[{from, to}] = weight;
        edges[{to, from}] = weight;
    }
}

int Graph::getWeight(int from, int to) const {
    return edges.value({from, to}, -1);
}

QSet<int> Graph::getVertices() const {
    return vertices;
}

QVector<QVector<int>> Graph::getAdjacencyMatrix() const {
    QList<int> sortedVerts = vertices.values();
    std::sort(sortedVerts.begin(), sortedVerts.end());
    int n = sortedVerts.size();
    QVector<QVector<int>> mat(n, QVector<int>(n, -1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w = getWeight(sortedVerts[i], sortedVerts[j]);
            if (w != -1) mat[i][j] = w;
        }
    }
    return mat;
}

QList<int> Graph::getNeighbors(int v) const {
    QSet<int> neighSet;
    for (auto it = edges.begin(); it != edges.end(); ++it) {
        if (it.key().first == v) neighSet.insert(it.key().second);
        else if (it.key().second == v) neighSet.insert(it.key().first);
    }
    return neighSet.values();
}

bool Graph::hasVertex(int v) const {
    return vertices.contains(v);
}

bool Graph::hasEdge(int from, int to) const {
    return edges.contains({from, to});
}

void Graph::clear() {
    vertices.clear();
    edges.clear();
}