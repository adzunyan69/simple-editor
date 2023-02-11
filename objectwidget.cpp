#include "objectwidget.h"

#include <QLayout>
#include <QLabel>
#include <QGroupBox>


ObjectWidget::ObjectWidget(const Utility::CustomObject &object, QWidget *parent)
    : QWidget(parent)
{
    this->setObjectName(object.objectName());

    QLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(createGroupBoxWidget(object));
    setLayout(mainLayout);

}

QWidget *ObjectWidget::createGroupBoxWidget(const Utility::CustomObject &object)
{
    QGroupBox *groupBox = new QGroupBox(object.objectName(), this);
    QLayout *groupLayout = new QVBoxLayout();

    auto properties = object.properties();
    for(auto it = properties.constKeyValueBegin(); it != properties.constKeyValueEnd(); ++it)
    {
        auto propertyWidget = new StringPropertyWidget(it->first, it->second.toString(), this);
        propertyWidgets.push_back(propertyWidget);
        groupLayout->addWidget(propertyWidget);
    }
    groupBox->setLayout(groupLayout);

    return groupBox;
}


Utility::CustomObject ObjectWidget::object() const
{
    QVariantHash propertiesHash;
    for(auto &property: propertyWidgets)
        propertiesHash[property->objectName()] = property->value();

    return Utility::CustomObject(this->objectName(), propertiesHash);
}

PropertyWidget::PropertyWidget(const QString &propertyName, const QVariant &value, QWidget *parent)
    : QWidget(parent)
{
    this->setObjectName(propertyName);

    QLayout *propertyLayout = new QHBoxLayout();

    auto labelWidget = new  QLabel(propertyName, this);
    labelWidget->setMinimumWidth(50);
    propertyLayout->addWidget(labelWidget);

    lineEdit = new QLineEdit(value.toString(), this);
    propertyLayout->addWidget(lineEdit);

    this->setLayout(propertyLayout);
}

QVariant StringPropertyWidget::value() const
{
    return lineEdit->text();
}
