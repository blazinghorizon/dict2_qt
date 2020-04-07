#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QDebug>
#include <QTextStream>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    load_dictionary();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_dictionary()
{
    QFile inFile(":/mueller.dict");

    if (!inFile.open(QIODevice::ReadOnly)) {
        return;
    }

    QTextStream in(&inFile);
    in.setCodec("UTF-8");

    QString line;

    while (!in.atEnd()) {
        line = in.readLine();
        qDebug() << line;
    }
    qDebug("yeet");

    inFile.close();
}
