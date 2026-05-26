#include "graph.h"
#include <cmath>
#include <algorithm>
#include <limits>

Graph::Graph() : m_nextId(0) {}

void Graph::addVertex(const QPointF &pos) {
    m_vertices.append(Vertex(m_nextId++, pos));
}

void Graph::removeVertex(int id) {
    m_edges.erase(std::remove_if(m_edges.begin(), m_edges.end(),
        [id](const DirectedEdge &e) { return e.from == id || e.to == id; }), m_edges.end());
    m_vertices.erase(std::remove_if(m_vertices.begin(), m_vertices.end(),
        [id](const Vertex &v) { return v.id == id; }), m_vertices.end());
}

void Graph::addDirectedEdge(int from, int to, double weight) {
    for (const auto &e : m_edges) {
        if (e.from == from && e.to == to) return;
    }
    m_edges.append(DirectedEdge(from, to, weight));
}

void Graph::removeDirectedEdge(int from, int to) {
    m_edges.erase(std::remove_if(m_edges.begin(), m_edges.end(),
        [from, to](const DirectedEdge &e) { return e.from == from && e.to == to; }), m_edges.end());
}

void Graph::setDirectedEdgeWeight(int from, int to, double weight) {
    for (auto &e : m_edges) {
        if (e.from == from && e.to == to) {
            e.weight = weight;
            return;
        }
    }
    addDirectedEdge(from, to, weight);
}

double Graph::edgeWeight(int from, int to) const {
    for (const auto &e : m_edges) {
        if (e.from == from && e.to == to) return e.weight;
    }
    return std::numeric_limits<double>::infinity();
}

void Graph::moveVertex(int id, const QPointF &newPos) {
    int idx = vertexIndex(id);
    if (idx != -1) {
        m_vertices[idx].pos = newPos;
    }
}

int Graph::vertexIdAt(int index) const {
    if (index >= 0 && index < m_vertices.size())
        return m_vertices[index].id;
    return -1;
}

int Graph::vertexIndex(int id) const {
    for (int i = 0; i < m_vertices.size(); ++i)
        if (m_vertices[i].id == id) return i;
    return -1;
}

QVector<QVector<double>> Graph::adjacencyMatrix() const {
    int n = m_vertices.size();
    QVector<QVector<double>> mat(n, QVector<double>(n, std::numeric_limits<double>::infinity()));
    for (int i = 0; i < n; ++i) mat[i][i] = 0.0;
    for (const auto &e : m_edges) {
        int i = vertexIndex(e.from);
        int j = vertexIndex(e.to);
        if (i != -1 && j != -1)
            mat[i][j] = e.weight;
    }
    return mat;
}
