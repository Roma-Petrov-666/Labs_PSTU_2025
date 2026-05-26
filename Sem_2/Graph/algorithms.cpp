#include "algorithms.h"
#include <queue>
#include <stack>
#include <QSet>

QList<int> Algorithms::bfs(const Graph& g, int start) {
    if (!g.hasVertex(start)) return {};
    QList<int> order;
    QSet<int> visited;
    std::queue<int> q;
    q.push(start);
    visited.insert(start);
    while (!q.empty()) {
        int v = q.front(); q.pop();
        order.append(v);
        for (int nb : g.getNeighbors(v)) {
            if (!visited.contains(nb)) {
                visited.insert(nb);
                q.push(nb);
            }
        }
    }
    return order;
}

QList<int> Algorithms::dfs(const Graph& g, int start) {
    if (!g.hasVertex(start)) return {};
    QList<int> order;
    QSet<int> visited;
    std::stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int v = st.top(); st.pop();
        if (visited.contains(v)) continue;
        visited.insert(v);
        order.append(v);
        for (int nb : g.getNeighbors(v)) {
            if (!visited.contains(nb))
                st.push(nb);
        }
    }
    return order;
}

QMap<int,int> Algorithms::dijkstra(const Graph& g, int start) {
    QMap<int,int> dist;
    QSet<int> unvisited;
    for (int v : g.getVertices()) {
        dist[v] = 1e9;
        unvisited.insert(v);
    }
    if (!g.hasVertex(start)) return dist;
    dist[start] = 0;
    while (!unvisited.isEmpty()) {
        int u = -1;
        int best = 1e9;
        for (int v : unvisited) {
            if (dist[v] < best) {
                best = dist[v];
                u = v;
            }
        }
        if (u == -1 || best == 1e9) break;
        unvisited.remove(u);
        for (int nb : g.getNeighbors(u)) {
            int w = g.getWeight(u, nb);
            if (w == -1) w = g.getWeight(nb, u);
            if (w != -1 && dist[u] + w < dist[nb]) {
                dist[nb] = dist[u] + w;
            }
        }
    }
    return dist;
}

QVector<QVector<int>> Algorithms::floydWarshall(const Graph& g) {
    QList<int> verts = g.getVertices().values();
    std::sort(verts.begin(), verts.end());
    int n = verts.size();
    QVector<QVector<int>> dist(n, QVector<int>(n, 1e9));
    for (int i = 0; i < n; ++i) {
        dist[i][i] = 0;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            int w = g.getWeight(verts[i], verts[j]);
            if (w != -1) dist[i][j] = w;
        }
    }
    for (int k = 0; k < n; ++k)
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    return dist;
}