#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graph.h"

class GraphWidget;
class QComboBox;
class QTextEdit;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void onGraphChanged();
    void onRunBFS();
    void onRunDFS();
    void onRunDijkstra();
    void onRunFloyd();
    void onAddVertex();
    void onRemoveVertex();
    void onAddEdge();
    void onRemoveEdge();
    void onEditWeight();
    void onEditAdjacencyMatrix();

private:
    Graph graph;
    GraphWidget* graphWidget;
    QComboBox* startVertexCombo;
    QTextEdit* outputText;

    void setupUI();
    void updateStartVertexCombo();
    void createDefaultGraph();
};

#endif