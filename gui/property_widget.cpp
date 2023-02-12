#include "property_widget.h"

PropertyWidget::PropertyWidget(const QString &propertyName,
                               QWidget *parent)
    : QWidget(parent)
{
    this->setObjectName(propertyName);

    propertyLayout = new QHBoxLayout(this);

    auto labelWidget = new  QLabel(propertyName, this);
    labelWidget->setMinimumWidth(50);
    propertyLayout->addWidget(labelWidget);

    this->setLayout(propertyLayout);
}
