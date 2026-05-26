#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"
#include "tspsolver.h"

QT_BEGIN_NAMESPACE
class QAction;
class QToolBar;
class GraphWidget;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void addVertex();
    void removeVertex();
    void addEdgeDialog();
    void removeEdgeDialog();
    void setWeightDialog();
    void solveTSP();
    void onVertexMoved(int id, QPointF pos);

private:
    void createToolBar();
    void setupDefaultGraph();

    Graph m_graph;
    GraphWidget *m_graphWidget;
};

#endif
