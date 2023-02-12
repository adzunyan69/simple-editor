#include "stringlist_property_widget.h"

#include <QDebug>

StringListPropertyWidget::StringListPropertyWidget(const QString &propertyName,
                                                   const Property &property,
                                                   QWidget *parent)
    : PropertyWidget(propertyName, parent)
{
    if(propertyLayout)
    {
        stringBox = new QComboBox(this);
        for(auto &value: property->accpetedValues())
            stringBox->addItem(value.toString());

        propertyLayout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
        propertyLayout->addWidget(stringBox);
    }
}

QVariant StringListPropertyWidget::value() const
{
    if(stringBox)
        return stringBox->currentText();

    // return invalid QVariant instead throwing exception
    return QVariant();
}

void StringListPropertyWidget::setValue(const QVariant &value)
{
    if(stringBox)
    {
        int index = stringBox->findText(value.toString());
        if(index ==  -1)
        {
            qWarning() << "The value isn't exists in the combo box";
            return;
        }
        stringBox->setCurrentIndex(index);
    }
}
