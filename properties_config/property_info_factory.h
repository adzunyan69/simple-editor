#ifndef PROPERTY_INFO_FACTORY_H
#define PROPERTY_INFO_FACTORY_H

#include <QDebug>
#include <memory>
#include "property_info.h"

class PropertyInfoFactory
{
public:
    static std::unique_ptr<PropertyInfo> makeProperty(const QVariantHash &jsonProperty);
private:
    static std::unique_ptr<PropertyInfo> intProperty(const QVariantHash &jsonProperty);
    static std::unique_ptr<PropertyInfo> floatProperty(const QVariantHash &jsonProperty);
    static std::unique_ptr<PropertyInfo> stringListProperty(const QVariantHash &jsonProperty);
    static std::unique_ptr<PropertyInfo> iconProperty(const QVariantHash &jsonProperty);
};

#endif // PROPERTY_INFO_FACTORY_H
