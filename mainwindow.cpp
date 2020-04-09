#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QTextStream>
#include <QTextCodec>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    load_dictionary(":/mueller.dict");
    statusBar("Standart dictionary");
    ui->wordList->addItems(words);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::statusBar(QString message)
{
    QString a = QCoreApplication::applicationDirPath();
    a.append("/mueller.dict");
    if ((message == ":/mueller.dict") || (message == a))
        message = tr("Standart dictionary");
    ui->statusbar->showMessage(message);
}

void MainWindow::load_dictionary(QString fileName)
{
    QFile inFile(fileName);

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

void MainWindow::slotFileDialog()
{
    words.clear();
    translations.clear();
    QString fileName = QFileDialog::getOpenFileName(
                this, tr("Open File"),"",tr("Text (*.dict)"));
    statusBar(fileName);
    load_dictionary(fileName);

}
