#include "mainwindow.h"
#include "graphwidget.h"
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QInputDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupDefaultGraph();

    m_graphWidget = new GraphWidget(this);
    m_graphWidget->setGraph(&m_graph);
    setCentralWidget(m_graphWidget);

    createToolBar();

    connect(m_graphWidget, &GraphWidget::vertexMoved, this, &MainWindow::onVertexMoved);

    resize(900, 700);
    setWindowTitle("TSP Solver - Asymmetric (Directed edges) - Branch and Bound");
}

MainWindow::~MainWindow() {}

void MainWindow::setupDefaultGraph() {
    QVector<QPointF> positions = {
        {100,100}, {300,80}, {500,150}, {600,300}, {450,500}, {150,450}
    };
    for (const QPointF &p : positions) {
        m_graph.addVertex(p);
    }

    m_graph.addDirectedEdge(0, 1, 50);
    m_graph.addDirectedEdge(1, 0, 70);
    m_graph.addDirectedEdge(1, 2, 40);
    m_graph.addDirectedEdge(2, 1, 60);
    m_graph.addDirectedEdge(2, 3, 30);
    m_graph.addDirectedEdge(3, 2, 45);
    m_graph.addDirectedEdge(3, 4, 20);
    m_graph.addDirectedEdge(4, 3, 35);
    m_graph.addDirectedEdge(4, 5, 25);
    m_graph.addDirectedEdge(5, 4, 40);
    m_graph.addDirectedEdge(5, 0, 55);
    m_graph.addDirectedEdge(0, 5, 65);
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 6; ++j) {
            if (i != j && m_graph.edgeWeight(i, j) >= 1e9) {
                m_graph.addDirectedEdge(i, j, 100);
            }
        }
    }
}

void MainWindow::createToolBar() {
    QToolBar *toolBar = addToolBar("Управление");
    QAction *actAddVertex = toolBar->addAction("Добавить вершину");
    QAction *actRemoveVertex = toolBar->addAction("Удалить вершину");
    QAction *actAddEdge = toolBar->addAction("Добавить дугу");
    QAction *actRemoveEdge = toolBar->addAction("Удалить дугу");
    QAction *actSetWeight = toolBar->addAction("Изменить вес дуги");
    QAction *actSolve = toolBar->addAction("Решить TSP");

    connect(actAddVertex, &QAction::triggered, this, &MainWindow::addVertex);
    connect(actRemoveVertex, &QAction::triggered, this, &MainWindow::removeVertex);
    connect(actAddEdge, &QAction::triggered, this, &MainWindow::addEdgeDialog);
    connect(actRemoveEdge, &QAction::triggered, this, &MainWindow::removeEdgeDialog);
    connect(actSetWeight, &QAction::triggered, this, &MainWindow::setWeightDialog);
    connect(actSolve, &QAction::triggered, this, &MainWindow::solveTSP);
}

void MainWindow::addVertex() {
    QPointF center = m_graphWidget->mapToScene(m_graphWidget->viewport()->rect().center());
    m_graph.addVertex(center);
    m_graphWidget->setGraph(&m_graph);
}

void MainWindow::removeVertex() {
    if (m_graph.vertexCount() == 0) {
        QMessageBox::warning(this, "Ошибка", "Нет вершин для удаления");
        return;
    }
    QStringList items;
    QMap<QString, int> map;
    for (const auto &v : m_graph.vertices()) {
        QString str = QString("ID %1 (%2, %3)").arg(v.id).arg(v.pos.x()).arg(v.pos.y());
        items << str;
        map[str] = v.id;
    }
    bool ok;
    QString selected = QInputDialog::getItem(this, "Удалить вершину", "Выберите вершину:", items, 0, false, &ok);
    if (ok && !selected.isEmpty()) {
        int id = map[selected];
        m_graph.removeVertex(id);
        m_graphWidget->setGraph(&m_graph);
    }
}

void MainWindow::addEdgeDialog() {
    if (m_graph.vertexCount() < 2) {
        QMessageBox::warning(this, "Ошибка", "Нужно хотя бы 2 вершины");
        return;
    }
    QStringList items;
    QMap<QString, int> map;
    for (const auto &v : m_graph.vertices()) {
        QString str = QString("ID %1").arg(v.id);
        items << str;
        map[str] = v.id;
    }
    bool ok;
    QString fromStr = QInputDialog::getItem(this, "Добавить дугу", "От вершины:", items, 0, false, &ok);
    if (!ok) return;
    QString toStr = QInputDialog::getItem(this, "Добавить дугу", "К вершине:", items, 0, false, &ok);
    if (!ok) return;
    int fromId = map[fromStr];
    int toId = map[toStr];
    if (fromId == toId) {
        QMessageBox::warning(this, "Ошибка", "Нельзя создать дугу в ту же вершину");
        return;
    }
    double weight = QInputDialog::getDouble(this, "Вес дуги", "Введите вес:", 1.0, 0, 1e6, 2, &ok);
    if (ok) {
        m_graph.addDirectedEdge(fromId, toId, weight);
        m_graphWidget->setGraph(&m_graph);
    }
}

void MainWindow::removeEdgeDialog() {
    if (m_graph.edges().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет дуг для удаления");
        return;
    }
    QStringList items;
    QMap<QString, QPair<int,int>> map;
    for (const auto &e : m_graph.edges()) {
        QString str = QString("%1 → %2 (вес %3)").arg(e.from).arg(e.to).arg(e.weight);
        items << str;
        map[str] = qMakePair(e.from, e.to);
    }
    bool ok;
    QString selected = QInputDialog::getItem(this, "Удалить дугу", "Выберите дугу:", items, 0, false, &ok);
    if (ok && !selected.isEmpty()) {
        auto p = map[selected];
        m_graph.removeDirectedEdge(p.first, p.second);
        m_graphWidget->setGraph(&m_graph);
    }
}

void MainWindow::setWeightDialog() {
    if (m_graph.edges().isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Нет дуг для изменения веса");
        return;
    }
    QStringList items;
    QMap<QString, QPair<int,int>> map;
    for (const auto &e : m_graph.edges()) {
        QString str = QString("%1 → %2 (вес %3)").arg(e.from).arg(e.to).arg(e.weight);
        items << str;
        map[str] = qMakePair(e.from, e.to);
    }
    bool ok;
    QString selected = QInputDialog::getItem(this, "Изменить вес дуги", "Выберите дугу:", items, 0, false, &ok);
    if (!ok) return;
    auto p = map[selected];
    double newWeight = QInputDialog::getDouble(this, "Новый вес", "Введите вес:",
                                                m_graph.edgeWeight(p.first, p.second), 0, 1e6, 2, &ok);
    if (ok) {
        m_graph.setDirectedEdgeWeight(p.first, p.second, newWeight);
        m_graphWidget->setGraph(&m_graph);
    }
}

void MainWindow::solveTSP() {
    auto mat = m_graph.adjacencyMatrix();
    TSPSolver::Result res = TSPSolver::branchAndBound(mat);
    if (res.found) {

        qDebug() << "Raw solver path (indices):" << res.path;


        QVector<int> pathIds;
        for (int idx : res.path) {
            int id = m_graph.vertexIdAt(idx);
            if (id != -1) pathIds.append(id);
        }

        QString pathStr;
        for (int id : pathIds) pathStr += QString::number(id) + " ";
        QMessageBox::information(this, "Результат TSP",
                                 QString("Маршрут: %1\nСтоимость: %2")
                                 .arg(pathStr).arg(res.cost));
        m_graphWidget->highlightPath(pathIds);
    } else {
        QMessageBox::warning(this, "Ошибка", "Гамильтонов цикл не найден. Убедитесь, что граф сильно связный.");
    }
}

void MainWindow::onVertexMoved(int id, QPointF pos) {
    m_graph.moveVertex(id, pos);
    m_graphWidget->setGraph(&m_graph);
}
