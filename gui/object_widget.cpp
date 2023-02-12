#include "object_widget.h"

#include <QDebug>

ObjectWidget::ObjectWidget(const CustomObject &object,
                           const PropertyHash &propertyHash,
                           QWidget *parent)
    : QWidget(parent)
{
    setObjectName(object.objectName());

    QLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(createObjectWidget(object, propertyHash));
    setLayout(mainLayout);
}

QWidget *ObjectWidget::createObjectWidget(const CustomObject &object,
                                          const PropertyHash &propertyHash)
{
    QGroupBox *groupBox = new QGroupBox(object.objectName(), this);
    QLayout *groupLayout = new QVBoxLayout();

    // Append properties using property table with restrictions
    auto properties = object.propertiesTable();
    for(auto it = properties.constKeyValueBegin(); it != properties.constKeyValueEnd(); ++it)
    {
        if(propertyHash.contains(it->first) == false)
        {
            qWarning() << QString("Invalid object property %1")
                          .arg(it->first);
            continue;
        }
        // Appen certain property and set current value
        auto propertyWidget = PropertyWidgetFactory::makeWidget(it->first,
                                                                propertyHash[it->first], this);
        propertyWidget->setValue(it->second);
        propertyWidgets.push_back(propertyWidget);
        groupLayout->addWidget(propertyWidget);
    }
    groupBox->setLayout(groupLayout);

    return groupBox;
}

CustomObject ObjectWidget::object() const
{
    QVariantMap propertiesMap;
    for(auto &property: propertyWidgets)
        propertiesMap[property->objectName()] = property->value();

    return CustomObject(this->objectName(), propertiesMap);
}
