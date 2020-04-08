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
    ui->translationArea->addItems(words);
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
    QString word;
    QString translation;


    while (!in.atEnd()) {
        line = in.readLine();

        if (!line.isEmpty() && !line[0].isSpace()) {
            if (!word.isEmpty()) {
                //qDebug() << word << translation;
                words.append(word);
            }
            word = line.simplified();
            translation = word;
        } else {
            translation = translation + QString("\n") + line;
        }
    }

    if (!word.isEmpty()) {
       // qDebug() << word << translation;
        words.append(word);
    }

    inFile.close();
}
