#include "int_property_widget.h"

IntPropertyWidget::IntPropertyWidget(const QString &propertyName,
                                     const Property &property,
                                     QWidget *parent)
    : PropertyWidget(propertyName, parent)
{
    if(propertyLayout)
    {
        spinBox = new QSpinBox(this);
        spinBox->setMinimum(property->from().toInt());
        spinBox->setMaximum(property->to().toInt());
        spinBox->setMaximumWidth(75);

        propertyLayout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
        propertyLayout->addWidget(spinBox);
    }
}

QVariant IntPropertyWidget::value() const
{
    if(spinBox)
        return spinBox->value();

    // return invalid QVariant instead throwing exception
    return QVariant();
}

void IntPropertyWidget::setValue(const QVariant &value)
{
    bool isValid = false;
    int v = value.toInt(&isValid);
    if(spinBox && isValid)
        spinBox->setValue(v);
}
