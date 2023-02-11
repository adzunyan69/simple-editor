#include "editorwindow.h"
#include "./ui_editorwindow.h"
#include <QDebug>
#include "objectsprocessing.h"
EditorWindow::EditorWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::EditorWindow)
{
    ui->setupUi(this);

    using namespace Utility;
    auto objects = ObjectProcessing().read(std::make_unique<JsonObjectsReader>("objects.json"));
    ObjectProcessing().write(objects, std::make_unique<JsonObjectsWriter>("objects_new.json"));
}

EditorWindow::~EditorWindow()
{
    delete ui;
}

