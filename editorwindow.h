#ifndef EDITORWINDOW_H
#define EDITORWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include "objectwidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EditorWindow; }
QT_END_NAMESPACE

class EditorWindow : public QMainWindow
{
    Q_OBJECT

public:
    EditorWindow(QWidget *parent = nullptr);
    ~EditorWindow();

private:
    Ui::EditorWindow *ui;

    QVector<ObjectWidget*> widgets;
    QPushButton *saveButton{ nullptr };

private slots:
    void saveObjects();
};

#endif // EDITORWINDOW_H
