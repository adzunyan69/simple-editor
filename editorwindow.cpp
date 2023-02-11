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

    for(auto &object: objects)
    {
        auto objectWidget = new ObjectWidget(object, this);
        widgets.push_back(objectWidget);
        ui->verticalLayout->addWidget(objectWidget);
    }

    saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::clicked,
            this, &EditorWindow::saveObjects);
    ui->verticalLayout->addWidget(saveButton);
}

EditorWindow::~EditorWindow()
{
    delete ui;
}

void EditorWindow::saveObjects()
{
    using namespace Utility;
    qInfo() << "Save button clicked";
    QVector<Utility::CustomObject> objects;
    for(auto &w: widgets)
        objects.push_back(w->object());

    ObjectProcessing().write(objects, std::make_unique<JsonObjectsWriter>("objects_new.json"));


}

