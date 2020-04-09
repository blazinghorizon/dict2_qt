#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTextStream>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    load_dictionary();
    ui->wordList->addItems(words);
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
                words.append(word);
                translations.insert(word, translation);
            }
            word = line.simplified();
            translation = word;
        } else {
            translation = translation + QString("\n") + line;
        }
    }

    if (!word.isEmpty()) {
        words.append(word);
        translations.insert(word, translation);
    }

    inFile.close();
}

void MainWindow::on_wordList_currentTextChanged(const QString &currentText)
{
    ui->translationArea->setPlainText(translations[currentText]);
}

void MainWindow::on_searchLine_textChanged(const QString &arg1)
{
    QRegExp rx(arg1);
    ui->wordList->clear();
    ui->wordList->addItems(words.filter(rx));
}
