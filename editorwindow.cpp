#include "editorwindow.h"
#include "./ui_editorwindow.h"
#include <QDebug>
#include "objectsprocessing.h"
#include "propertyprocessing.h"

EditorWindow::EditorWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::EditorWindow),
      scrollArea(new QScrollArea(this)),
      scrollLayout(new QVBoxLayout(scrollArea)),
      saveButton(new QPushButton("Save", this))
{
    ui->setupUi(this);

    scrollArea->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
    scrollArea->setWidgetResizable( true );
    // scrollArea->setGeometry( 10, 10, 200, 200 );

    QWidget *scrollContainerWidget = new QWidget();
    scrollContainerWidget->setLayout(scrollLayout);
    scrollArea->setWidget( scrollContainerWidget );

    ui->verticalLayout->addWidget(scrollArea);
    ui->verticalLayout->addWidget(saveButton);

    loadObjects();

    connect(saveButton, &QPushButton::clicked,
            this, &EditorWindow::saveObjects);
}

EditorWindow::~EditorWindow()
{
    delete ui;
}

void EditorWindow::loadObjects()
{
    auto objects = ObjectProcessing().read(std::make_unique<JsonObjectsReader>("objects.json"));
    auto propertyTable = PropertyProcessing().readPropertyConfig("properties.json");

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
    qInfo() << "Save button clicked";
    QVector<CustomObject> objects;
    for(auto &w: widgets)
        objects.push_back(w->object());

    ObjectProcessing().write(objects, std::make_unique<JsonObjectsWriter>("objects_new.json"));


}

