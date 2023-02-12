#include "float_property_widget.h"

FloatPropertyWidget::FloatPropertyWidget(const QString &propertyName,
                                         const Property &property,
                                         QWidget *parent)
    : PropertyWidget(propertyName, parent)
{
    if(propertyLayout)
    {
        spinBox = new QDoubleSpinBox(this);
        spinBox->setMinimum(property->from().toFloat());
        spinBox->setMaximum(property->to().toFloat());
        spinBox->setMaximumWidth(75);

        propertyLayout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
        propertyLayout->addWidget(spinBox);
    }
}

QVariant FloatPropertyWidget::value() const
{
    if(spinBox)
        return spinBox->value();

    // return invalid QVariant instead throwing exception
    return QVariant();
}

void FloatPropertyWidget::setValue(const QVariant &value)
{
    bool isValid = false;
    int v = value.toFloat(&isValid);
    if(spinBox && isValid)
        spinBox->setValue(v);
}
