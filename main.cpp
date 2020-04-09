#include "mainwindow.h"

#include <QApplication>
#include <QTextCodec>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    QApplication a(argc, argv);

    QTranslator t;
    t.load(":/dict2_qt_ru_RU.qm");
    a.installTranslator(&t);

    MainWindow w;
    w.show();
    return a.exec();
}
