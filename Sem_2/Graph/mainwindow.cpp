#include "mainwindow.h"
#include "graphwidget.h"
#include "algorithms.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include <QTextEdit>
#include <QLabel>
#include <QInputDialog>
#include <QMessageBox>
#include <QTableWidget>
#include <QDialogButtonBox>
#include <algorithm>   // добавлено для std::sort

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();
    createDefaultGraph();
    graphWidget->updateVisualization();
    updateStartVertexCombo();
}

void MainWindow::setupUI() {
    graphWidget = new GraphWidget(&graph, this);
    startVertexCombo = new QComboBox(this);
    outputText = new QTextEdit(this);
    outputText->setReadOnly(true);

    QPushButton* btnBFS = new QPushButton("BFS", this);
    QPushButton* btnDFS = new QPushButton("DFS", this);
    QPushButton* btnDijkstra = new QPushButton("Дейкстра", this);
    QPushButton* btnFloyd = new QPushButton("Флойд", this);

    QPushButton* btnAddVertex = new QPushButton("Добавить узел", this);
    QPushButton* btnRemoveVertex = new QPushButton("Удалить узел", this);
    QPushButton* btnAddEdge = new QPushButton("Добавить ребро", this);
    QPushButton* btnRemoveEdge = new QPushButton("Удалить ребро", this);
    QPushButton* btnEditWeight = new QPushButton("Редактировать вес ребра", this);
    QPushButton* btnEditMatrix = new QPushButton("Редактировать матрицу смежности", this);

    connect(btnBFS, &QPushButton::clicked, this, &MainWindow::onRunBFS);
    connect(btnDFS, &QPushButton::clicked, this, &MainWindow::onRunDFS);
    connect(btnDijkstra, &QPushButton::clicked, this, &MainWindow::onRunDijkstra);
    connect(btnFloyd, &QPushButton::clicked, this, &MainWindow::onRunFloyd);
    connect(btnAddVertex, &QPushButton::clicked, this, &MainWindow::onAddVertex);
    connect(btnRemoveVertex, &QPushButton::clicked, this, &MainWindow::onRemoveVertex);
    connect(btnAddEdge, &QPushButton::clicked, this, &MainWindow::onAddEdge);
    connect(btnRemoveEdge, &QPushButton::clicked, this, &MainWindow::onRemoveEdge);
    connect(btnEditWeight, &QPushButton::clicked, this, &MainWindow::onEditWeight);
    connect(btnEditMatrix, &QPushButton::clicked, this, &MainWindow::onEditAdjacencyMatrix);

    QHBoxLayout* algoLayout = new QHBoxLayout;
    algoLayout->addWidget(new QLabel("Стартовый узел:"));
    algoLayout->addWidget(startVertexCombo);
    algoLayout->addWidget(btnBFS);
    algoLayout->addWidget(btnDFS);
    algoLayout->addWidget(btnDijkstra);
    algoLayout->addWidget(btnFloyd);

    QHBoxLayout* editLayout = new QHBoxLayout;
    editLayout->addWidget(btnAddVertex);
    editLayout->addWidget(btnRemoveVertex);
    editLayout->addWidget(btnAddEdge);
    editLayout->addWidget(btnRemoveEdge);
    editLayout->addWidget(btnEditWeight);
    editLayout->addWidget(btnEditMatrix);

    QVBoxLayout* rightLayout = new QVBoxLayout;
    rightLayout->addLayout(algoLayout);
    rightLayout->addWidget(outputText);
    rightLayout->addLayout(editLayout);

    QHBoxLayout* mainLayout = new QHBoxLayout;
    mainLayout->addWidget(graphWidget, 2);
    mainLayout->addLayout(rightLayout, 1);

    QWidget* central = new QWidget(this);
    central->setLayout(mainLayout);
    setCentralWidget(central);
    resize(1000, 600);
    setWindowTitle("Graph Algorithms Visualizer - Вариант 18 (Дейкстра с вершины 3)");
}

void MainWindow::createDefaultGraph() {
    // Вершины 1..6 согласно варианту 18
    for (int v = 1; v <= 6; ++v) graph.addVertex(v);

    // Рёбра и веса из варианта 18 (неориентированные)
    graph.addEdge(5, 2, 53);
    graph.addEdge(5, 3, 21);
    graph.addEdge(2, 3, 16);
    graph.addEdge(3, 4, 3);
    graph.addEdge(4, 1, 5);
    graph.addEdge(3, 1, 18);
    graph.addEdge(1, 2, 12);
    graph.addEdge(2, 6, 45);
    graph.addEdge(1, 6, 34);
}

void MainWindow::updateStartVertexCombo() {
    startVertexCombo->clear();
    QList<int> verts = graph.getVertices().values();
    std::sort(verts.begin(), verts.end());
    for (int v : verts) startVertexCombo->addItem(QString::number(v));

    // Для варианта 18 стартовая вершина по заданию - 3
    int idx = startVertexCombo->findText("3");
    if (idx >= 0) startVertexCombo->setCurrentIndex(idx);
    else if (startVertexCombo->count() > 0) startVertexCombo->setCurrentIndex(0);
}

void MainWindow::onGraphChanged() {
    graphWidget->updateVisualization();
    updateStartVertexCombo();
}

void MainWindow::onRunBFS() {
    if (startVertexCombo->count() == 0) return;
    int start = startVertexCombo->currentText().toInt();
    QList<int> order = Algorithms::bfs(graph, start);
    QString res = "BFS из " + QString::number(start) + ": ";
    for (int v : order) res += QString::number(v) + " ";
    outputText->append(res);
}

void MainWindow::onRunDFS() {
    if (startVertexCombo->count() == 0) return;
    int start = startVertexCombo->currentText().toInt();
    QList<int> order = Algorithms::dfs(graph, start);
    QString res = "DFS из " + QString::number(start) + ": ";
    for (int v : order) res += QString::number(v) + " ";
    outputText->append(res);
}

void MainWindow::onRunDijkstra() {
    if (startVertexCombo->count() == 0) return;
    int start = startVertexCombo->currentText().toInt();
    QMap<int,int> dist = Algorithms::dijkstra(graph, start);
    QString res = "Расстояния Дейкстры от " + QString::number(start) + ":\n";
    for (auto it = dist.begin(); it != dist.end(); ++it) {
        if (it.value() >= 1e8) res += QString::number(it.key()) + ": INF\n";
        else res += QString::number(it.key()) + ": " + QString::number(it.value()) + "\n";
    }
    outputText->append(res);
}

void MainWindow::onRunFloyd() {
    if (startVertexCombo->count() == 0) return;
    int start = startVertexCombo->currentText().toInt();
    auto mat = Algorithms::floydWarshall(graph);
    QList<int> verts = graph.getVertices().values();
    std::sort(verts.begin(), verts.end());
    int startIndex = verts.indexOf(start);
    if (startIndex == -1) {
        outputText->append("Стартовая вершина не найдена!");
        return;
    }
    QString res = "Расстояния Флойда от " + QString::number(start) + ":\n";
    for (int i = 0; i < verts.size(); ++i) {
        int dist = mat[startIndex][i];
        if (dist >= 1e8) res += QString::number(verts[i]) + ": INF\n";
        else res += QString::number(verts[i]) + ": " + QString::number(dist) + "\n";
    }
    outputText->append(res);
}

void MainWindow::onAddVertex() {
    bool ok;
    int v = QInputDialog::getInt(this, "Добавить узел", "Номер узла:", 0, -1000000, 1000000, 1, &ok);
    if (ok && !graph.hasVertex(v)) {
        graph.addVertex(v);
        onGraphChanged();
    } else if (ok) {
        QMessageBox::warning(this, "Ошибка", "Узел уже существует!");
    }
}

void MainWindow::onRemoveVertex() {
    if (graph.getVertices().isEmpty()) return;
    QList<int> verts = graph.getVertices().values();
    std::sort(verts.begin(), verts.end());
    QStringList items;
    for (int v : verts) items << QString::number(v);
    bool ok;
    QString selected = QInputDialog::getItem(this, "Удалить узел", "Выберите узел:", items, 0, false, &ok);
    if (ok && !selected.isEmpty()) {
        int v = selected.toInt();
        graph.removeVertex(v);
        onGraphChanged();
    }
}

void MainWindow::onAddEdge() {
    QList<int> verts = graph.getVertices().values();
    if (verts.size() < 2) return;
    QStringList items;
    for (int v : verts) items << QString::number(v);
    bool ok;
    QString fromStr = QInputDialog::getItem(this, "Добавить ребро", "От узла:", items, 0, false, &ok);
    if (!ok) return;
    QString toStr = QInputDialog::getItem(this, "Добавить ребро", "К узлу:", items, 0, false, &ok);
    if (!ok) return;
    int weight = QInputDialog::getInt(this, "Добавить ребро", "Вес:", 1, 1, 10000, 1, &ok);
    if (ok) {
        int from = fromStr.toInt();
        int to = toStr.toInt();
        if (graph.hasVertex(from) && graph.hasVertex(to)) {
            graph.addEdge(from, to, weight);
            onGraphChanged();
        }
    }
}

void MainWindow::onRemoveEdge() {
    QList<int> verts = graph.getVertices().values();
    if (verts.isEmpty()) return;
    QStringList edgesList;
    QList<QPair<int,int>> edgePairs;
    for (int from : verts) {
        for (int to : graph.getNeighbors(from)) {
            if (from < to) {
                edgesList << QString("%1 -> %2").arg(from).arg(to);
                edgePairs.append({from, to});
            }
        }
    }
    if (edgesList.isEmpty()) return;
    bool ok;
    QString chosen = QInputDialog::getItem(this, "Удалить ребро", "Выберите ребро:", edgesList, 0, false, &ok);
    if (ok) {
        int idx = edgesList.indexOf(chosen);
        if (idx >= 0) {
            auto e = edgePairs[idx];
            graph.removeEdge(e.first, e.second);
            onGraphChanged();
        }
    }
}

void MainWindow::onEditWeight() {
    QList<int> verts = graph.getVertices().values();
    if (verts.isEmpty()) return;
    QStringList edgesList;
    QList<QPair<int,int>> edgePairs;
    for (int from : verts) {
        for (int to : graph.getNeighbors(from)) {
            if (from < to) {
                int w = graph.getWeight(from, to);
                if (w == -1) w = graph.getWeight(to, from);
                edgesList << QString("%1 -> %2 (вес=%3)").arg(from).arg(to).arg(w);
                edgePairs.append({from, to});
            }
        }
    }
    if (edgesList.isEmpty()) return;
    bool ok;
    QString chosen = QInputDialog::getItem(this, "Редактирование веса", "Выберите ребро:", edgesList, 0, false, &ok);
    if (ok) {
        int idx = edgesList.indexOf(chosen);
        if (idx >= 0) {
            int newWeight = QInputDialog::getInt(this, "Редактирование веса", "Новый вес:", 1, 1, 10000, 1, &ok);
            if (ok) {
                auto e = edgePairs[idx];
                graph.setEdgeWeight(e.first, e.second, newWeight);
                onGraphChanged();
            }
        }
    }
}

void MainWindow::onEditAdjacencyMatrix() {
    QList<int> verts = graph.getVertices().values();
    std::sort(verts.begin(), verts.end());
    int n = verts.size();
    if (n == 0) return;
    QDialog dialog(this);
    dialog.setWindowTitle("Редактировать матрицу смежности");
    QVBoxLayout layout(&dialog);
    QTableWidget table(n, n, &dialog);
    QStringList headers;
    for (int v : verts) headers << QString::number(v);
    table.setHorizontalHeaderLabels(headers);
    table.setVerticalHeaderLabels(headers);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int w = graph.getWeight(verts[i], verts[j]);
            if (w == -1) table.setItem(i, j, new QTableWidgetItem(""));
            else table.setItem(i, j, new QTableWidgetItem(QString::number(w)));
        }
    }
    QDialogButtonBox buttons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout.addWidget(&table);
    layout.addWidget(&buttons);
    QObject::connect(&buttons, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    QObject::connect(&buttons, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
    if (dialog.exec() == QDialog::Accepted) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                QString text = table.item(i, j)->text();
                if (!text.isEmpty()) {
                    bool ok;
                    int w = text.toInt(&ok);
                    if (ok && w > 0) graph.addEdge(verts[i], verts[j], w);
                    else graph.removeEdge(verts[i], verts[j]);
                } else {
                    graph.removeEdge(verts[i], verts[j]);
                }
            }
        }
        onGraphChanged();
    }
}