#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include "graph.h"
#include <QList>
#include <QMap>
#include <QVector>

class Algorithms {
public:
    static QList<int> bfs(const Graph& g, int start);
    static QList<int> dfs(const Graph& g, int start);
    static QMap<int,int> dijkstra(const Graph& g, int start);
    static QVector<QVector<int>> floydWarshall(const Graph& g);
};

#endif