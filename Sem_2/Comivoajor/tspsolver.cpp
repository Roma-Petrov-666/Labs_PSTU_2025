#include "tspsolver.h"
#include <queue>
#include <algorithm>
#include <limits>

using namespace std;

struct Node {
    int level;
    QVector<int> path;
    double cost;
    QVector<QVector<double>> reducedMatrix;
    int cityCount;
};

double reduceMatrix(QVector<QVector<double>> &mat, int n) {
    double totalReduction = 0.0;
    for (int i = 0; i < n; ++i) {
        double minVal = numeric_limits<double>::infinity();
        for (int j = 0; j < n; ++j) {
            if (mat[i][j] < minVal) minVal = mat[i][j];
        }
        if (minVal > 0 && minVal < numeric_limits<double>::infinity()) {
            totalReduction += minVal;
            for (int j = 0; j < n; ++j)
                if (mat[i][j] < numeric_limits<double>::infinity())
                    mat[i][j] -= minVal;
        }
    }
    for (int j = 0; j < n; ++j) {
        double minVal = numeric_limits<double>::infinity();
        for (int i = 0; i < n; ++i) {
            if (mat[i][j] < minVal) minVal = mat[i][j];
        }
        if (minVal > 0 && minVal < numeric_limits<double>::infinity()) {
            totalReduction += minVal;
            for (int i = 0; i < n; ++i)
                if (mat[i][j] < numeric_limits<double>::infinity())
                    mat[i][j] -= minVal;
        }
    }
    return totalReduction;
}

QVector<QVector<double>> copyMatrix(const QVector<QVector<double>> &src, int n) {
    QVector<QVector<double>> dst(n, QVector<double>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dst[i][j] = src[i][j];
    return dst;
}

TSPSolver::Result TSPSolver::branchAndBound(const QVector<QVector<double>> &dist) {
    int n = dist.size();
    Result best;
    best.cost = numeric_limits<double>::infinity();
    best.found = false;
    if (n == 0) return best;

    auto cmp = [](const Node &a, const Node &b) { return a.cost > b.cost; };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);

    Node root;
    root.level = 1;
    root.path = {0};
    root.cityCount = n;
    root.reducedMatrix = copyMatrix(dist, n);
    root.cost = reduceMatrix(root.reducedMatrix, n);
    pq.push(root);

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.level == n) {
            int last = current.path.last();
            int first = current.path.first();
            double finalCost = current.cost + current.reducedMatrix[last][first];
            if (finalCost < best.cost && current.reducedMatrix[last][first] < numeric_limits<double>::infinity()) {
                best.cost = finalCost;
                best.path = current.path;
                best.found = true;
            }
            continue;
        }

        int last = current.path.last();
        for (int next = 0; next < n; ++next) {
            if (next == last) continue;
            bool visited = false;
            for (int v : current.path) if (v == next) { visited = true; break; }
            if (visited) continue;
            if (current.reducedMatrix[last][next] >= numeric_limits<double>::infinity()/2) continue;

            Node child;
            child.level = current.level + 1;
            child.path = current.path;
            child.path.append(next);
            child.cityCount = n;
            child.reducedMatrix = copyMatrix(current.reducedMatrix, n);

            double edgeCost = child.reducedMatrix[last][next];
            for (int i = 0; i < n; ++i) {
                child.reducedMatrix[last][i] = numeric_limits<double>::infinity();
                child.reducedMatrix[i][next] = numeric_limits<double>::infinity();
            }
            for (int i = 0; i < child.path.size() - 1; ++i) {
                child.reducedMatrix[child.path[i+1]][child.path[i]] = numeric_limits<double>::infinity();
            }

            double additional = reduceMatrix(child.reducedMatrix, n);
            child.cost = current.cost + edgeCost + additional;

            if (child.cost < best.cost) {
                pq.push(child);
            }
        }
    }

    if (best.found) {
        best.path.append(best.path.first());
    }
    return best;
}
