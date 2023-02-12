#include "property_widget_factory.h"

#include <QDebug>

#include "property_widgets/int_property_widget.h"
#include "property_widgets/float_property_widget.h"
#include "property_widgets/icon_property_widget.h"
#include "property_widgets/stringlist_property_widget.h"

PropertyWidget* PropertyWidgetFactory::makeWidget(const QString &propertyName,
                                                  const Property &property,
                                                  QWidget *parent)
{
    switch(property->type())
    {
    case QMetaType::Type::Int:
        return new IntPropertyWidget(propertyName, property, parent);
    case QMetaType::Type::Float:
        return new FloatPropertyWidget(propertyName, property, parent);
    case QMetaType::Type::QIcon:
        return new IconPropertyWidget(propertyName, property, parent);
    case QMetaType::Type::QStringList:
        return new StringListPropertyWidget(propertyName, property, parent);
    default:
        qWarning() << QString("Unknown property type %1")
                      .arg(QString::number(property->type()));
        return nullptr;
    }
}
