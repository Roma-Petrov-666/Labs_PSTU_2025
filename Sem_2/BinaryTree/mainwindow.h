#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include "tree.h"
#include "treewidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    BinarySearchTree tree;
    TreeWidget *treeWidget;
    QTextEdit *outputText;

    void updateTreeDisplay();
    void displayList(const QList<QString> &list, const QString &title);
    bool getKeyValueFromUser(int &key, int &value);

private slots:
    void onInsert();
    void onRemove();
    void onSearch();
    void onBalance();
    void onFindMin();
    void onCreateBalanced();
    void onTraverse(int index);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif