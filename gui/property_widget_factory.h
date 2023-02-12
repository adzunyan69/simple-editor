#ifndef PROPERTY_WIDGET_FACTORY_H
#define PROPERTY_WIDGET_FACTORY_H

#include "property_widget.h"
#include "../properties_config/property_info.h"

// Factory for creating the certain property based on the property type
// Avaliable type:
// -- Int (from-to restriction)
// -- Float (from-to restriction)
// -- Icon (without restriction)
// -- StringList (array of strings)
class PropertyWidgetFactory
{
public:
    static PropertyWidget* makeWidget(const QString &propertyName,
                                      const Property &property,
                                      QWidget *parent = nullptr);
};

#endif // PROPERTY_WIDGET_FACTORY_H
