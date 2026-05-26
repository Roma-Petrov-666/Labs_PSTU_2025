#include "mainwindow.h"
#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QDialog>
#include <QDialogButtonBox>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    QWidget *central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout *mainLayout = new QVBoxLayout(central);

    treeWidget = new TreeWidget(this);
    treeWidget->setMinimumHeight(400);
    mainLayout->addWidget(treeWidget);

    QHBoxLayout *controlLayout = new QHBoxLayout();

    QPushButton *btnInsert = new QPushButton("Вставить");
    QPushButton *btnRemove = new QPushButton("Удалить");
    QPushButton *btnSearch = new QPushButton("Поиск");
    QPushButton *btnBalance = new QPushButton("Балансировка");
    QPushButton *btnFindMin = new QPushButton("Найти мин. значение");   // новая кнопка
    QPushButton *btnCreateBalanced = new QPushButton("Создать сбалансированное"); // новая кнопка

    QComboBox *traverseCombo = new QComboBox();
    traverseCombo->addItems({"Прямой", "Симметричный", "Обратный"});
    QPushButton *btnTraverse = new QPushButton("Обход");

    controlLayout->addWidget(btnInsert);
    controlLayout->addWidget(btnRemove);
    controlLayout->addWidget(btnSearch);
    controlLayout->addWidget(btnBalance);
    controlLayout->addWidget(btnFindMin);
    controlLayout->addWidget(btnCreateBalanced);
    controlLayout->addWidget(traverseCombo);
    controlLayout->addWidget(btnTraverse);

    mainLayout->addLayout(controlLayout);

    outputText = new QTextEdit();
    outputText->setReadOnly(true);
    outputText->setMaximumHeight(150);
    mainLayout->addWidget(outputText);

    connect(btnInsert, &QPushButton::clicked, this, &MainWindow::onInsert);
    connect(btnRemove, &QPushButton::clicked, this, &MainWindow::onRemove);
    connect(btnSearch, &QPushButton::clicked, this, &MainWindow::onSearch);
    connect(btnBalance, &QPushButton::clicked, this, &MainWindow::onBalance);
    connect(btnFindMin, &QPushButton::clicked, this, &MainWindow::onFindMin);
    connect(btnCreateBalanced, &QPushButton::clicked, this, &MainWindow::onCreateBalanced);
    connect(btnTraverse, &QPushButton::clicked, this, [this, traverseCombo]() {
        onTraverse(traverseCombo->currentIndex());
    });

    onCreateBalanced();
}

MainWindow::~MainWindow() {}

void MainWindow::updateTreeDisplay() {
    treeWidget->setTree(&tree);
    treeWidget->drawTree();
}

void MainWindow::displayList(const QList<QString> &list, const QString &title) {
    QString str = title + ": ";
    for (const QString &item : list) {
        str += item + "; ";
    }
    outputText->append(str);
}

void MainWindow::onTraverse(int index) {
    QList<QString> result;
    switch(index) {
        case 0: result = tree.preOrder(); displayList(result, "Прямой обход"); break;
        case 1: result = tree.inOrder(); displayList(result, "Симметричный обход"); break;
        case 2: result = tree.postOrder(); displayList(result, "Обратный обход"); break;
        default: break;
    }
}

void MainWindow::onInsert() {
    int key, value;
    if (getKeyValueFromUser(key, value)) {
        tree.insert(key, value);
        updateTreeDisplay();
        outputText->append(QString("Вставлено: ключ %1, значение %2").arg(key).arg(value));
    }
}

void MainWindow::onRemove() {
    bool ok;
    int key = QInputDialog::getInt(this, "Удаление", "Введите ключ для удаления:", 0, -10000, 10000, 1, &ok);
    if (ok) {
        int dummy;
        if (tree.search(key, dummy)) {
            tree.remove(key);
            updateTreeDisplay();
            outputText->append("Удалён ключ: " + QString::number(key));
        }
        else {
            QMessageBox::information(this, "Удаление", "Ключ не найден!");
        }
    }
}

void MainWindow::onSearch() {
    bool ok;
    int key = QInputDialog::getInt(this, "Поиск", "Введите ключ:", 0, -10000, 10000, 1, &ok);
    if (ok) {
        int value;
        if (tree.search(key, value)) {
            outputText->append(QString("Поиск: ключ %1 найден, значение = %2").arg(key).arg(value));
        }
        else {
            outputText->append("Поиск: ключ " + QString::number(key) + " не найден");
        }
    }
}

void MainWindow::onBalance() {
    tree.balance();
    updateTreeDisplay();
    outputText->append("Дерево сбалансировано.");
}

void MainWindow::onFindMin() {
    int minVal = tree.findMinValue();
    if (tree.getRoot() == nullptr) {
        outputText->append("Дерево пусто, минимального элемента нет.");
    } else {
        outputText->append("Минимальное значение (value) в дереве: " + QString::number(minVal));
    }
}

void MainWindow::onCreateBalanced() {
    QList<int> keys = {10, 20, 30, 40, 50, 60, 70};
    QList<int> values = {100, 200, 300, 400, 500, 600, 700};
    tree.createBalanced(keys, values);
    updateTreeDisplay();
    outputText->append("Создано идеально сбалансированное дерево (ключи: 10..70, значения: 100..700).");
}

bool MainWindow::getKeyValueFromUser(int &key, int &value) {
    QDialog dialog(this);
    dialog.setWindowTitle("Вставка элемента");
    QVBoxLayout layout(&dialog);

    QLabel labelKey("Ключ (целое число):");
    QLineEdit editKey;
    editKey.setValidator(new QIntValidator(-10000, 10000, &dialog));

    QLabel labelValue("Значение (целое число):");
    QLineEdit editValue;
    editValue.setValidator(new QIntValidator(-10000, 10000, &dialog));

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout.addWidget(&labelKey);
    layout.addWidget(&editKey);
    layout.addWidget(&labelValue);
    layout.addWidget(&editValue);
    layout.addWidget(&buttonBox);

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    if (dialog.exec() == QDialog::Accepted) {
        key = editKey.text().toInt();
        value = editValue.text().toInt();
        return true;
    }
    return false;
}