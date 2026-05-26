#ifndef TSP_SOLVER_H
#define TSP_SOLVER_H

#include <QVector>

class TSPSolver
{
public:
    struct Result {
        QVector<int> path;
        double cost;
        bool found;
    };

    static Result branchAndBound(const QVector<QVector<double>> &dist);
};

#endif
