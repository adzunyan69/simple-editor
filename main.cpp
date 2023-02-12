#include "editorwindow.h"

#include <QApplication>
#include <QDir>
#include <QDateTime>
#include <QTextStream>
#include <iostream>

// Simple cropped file logger from other projects
void logToFileMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);
QString getLogMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(logToFileMessageHandler);
    EditorWindow w;
    w.show();
    return a.exec();
}

void logToFileMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    auto txt = getLogMsg(type, context, msg);
    QString logDir = QDir::currentPath() + "/log/";

    if(!QDir().exists(logDir))
        QDir().mkpath(logDir);


    QFile file(logDir + "log.txt");
    if(file.open(QIODevice::WriteOnly | QIODevice::Append) == false)
    {
        QTextStream stream(stdout, QIODevice::WriteOnly);
        std::cout << "[The log file was not opened] ";
        std::cout << txt.toStdString() << std::endl;
        return;
    }

    QTextStream stream(&file);
    stream << txt << Qt::endl;
    file.close();
}

QString getLogMsg(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static long long uid = 0;
    uid++;

    QString txt;
    QString function = context.function;

    switch (type) {
        case QtInfoMsg:
            txt = QString("Info [%1@%2]>> %3").arg(function).arg(context.line).arg(msg);
        break;
        case QtDebugMsg:
            txt = QString("Debug [%1@%2]>> %3").arg(function).arg(context.line).arg(msg);
            break;
        case QtWarningMsg:
            txt = QString("Warning [%1@%2]>> %3").arg(function).arg(context.line).arg(msg);
        break;
        case QtCriticalMsg:
            txt = QString("Critical [%1@%2]>> %3").arg(function).arg(context.line).arg(msg);
        break;
        case QtFatalMsg:
            txt = QString("Fatal [%1@%2]>> %3").arg(function).arg(context.line).arg(msg);
            abort();
        break;
    }

    QDateTime dateTime = QDateTime::currentDateTime();
    txt = QString("%1@%2 %3 ")
          .arg(uid)
          .arg(dateTime.toString("yyyy-MM-dd hh:mm:ss.zzz"))
          .arg(txt);

    return txt;
}
