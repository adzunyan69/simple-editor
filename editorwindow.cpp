#include "editorwindow.h"
#include "./ui_editorwindow.h"
#include <QDebug>

#include "custom_objects/object_processing.h"
#include "properties_config/property_processing.h"
#include "custom_objects/json_object_reader.h"
#include "custom_objects/json_object_writer.h"

EditorWindow::EditorWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::EditorWindow),
      scrollArea(new QScrollArea(this)),
      scrollLayout(new QVBoxLayout(scrollArea)),
      saveButton(new QPushButton("Save", this))
{
    ui->setupUi(this);

    initGUI();
    loadObjects();
}

EditorWindow::~EditorWindow()
{
    delete ui;
}

void EditorWindow::initGUI()
{
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    scrollArea->setWidgetResizable(true);

    QWidget *scrollContainerWidget = new QWidget();
    scrollContainerWidget->setLayout(scrollLayout);
    scrollArea->setWidget(scrollContainerWidget);

    ui->verticalLayout->addWidget(scrollArea);
    ui->verticalLayout->addWidget(saveButton);

    connect(saveButton, &QPushButton::clicked,
            this, &EditorWindow::saveObjects);
}

void EditorWindow::loadObjects()
{
    // Reading objects and properties config
    auto objects = ObjectProcessing().read(std::make_unique<JsonObjectsReader>("objects.json"));
    auto propertyTable = PropertyProcessing().readPropertyConfig("properties.json");

    // Appending objects to the gui using properties table
    for(auto &object: objects)
    {
        if(propertyTable.contains(object.objectName()) == false)
        {
            qWarning() << QString("Invalid property for the object %1")
                          .arg(object.objectName());
            continue;
        }

        auto objectWidget = new ObjectWidget(object, propertyTable[object.objectName()], this);
        widgets.push_back(objectWidget);
        scrollLayout->addWidget(objectWidget);
    }
}

void EditorWindow::saveObjects()
{
    QVector<CustomObject> objects;
    for(auto &w: widgets)
        objects.push_back(w->object());

    ObjectProcessing().write(objects, std::make_unique<JsonObjectsWriter>("objects_new.json"));
}

