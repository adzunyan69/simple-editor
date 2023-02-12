#include "property_info_factory.h"

std::unique_ptr<PropertyInfo> PropertyInfoFactory::makeProperty(const QVariantHash &jsonProperty)
{
    static QHash<QString, QMetaType::Type> stringToType
    {
        { "int", QMetaType::Type::Int },
        { "float", QMetaType::Type::Float },
        { "image", QMetaType::Type::QIcon },
        { "array", QMetaType::Type::QStringList }
    };

    auto typeString = jsonProperty["type"].toString();
    switch(stringToType[typeString])
    {
    case QMetaType::Type::Int:
        return intProperty(jsonProperty);
    case QMetaType::Type::Float:
        return floatProperty(jsonProperty);
    case QMetaType::Type::QIcon:
        return iconProperty(jsonProperty);
    case QMetaType::Type::QStringList:
        return stringListProperty(jsonProperty);
    default:
        qWarning() << QString("Unknown type %1")
                      .arg(typeString);
        return nullptr;
    }
}

std::unique_ptr<PropertyInfo> PropertyInfoFactory::intProperty(const QVariantHash &jsonProperty)
{
    int from = std::numeric_limits<int>::min();
    int to = std::numeric_limits<int>::max();
    bool isValid = false;
    if(jsonProperty.contains("from"))
    {
        from = jsonProperty["from"].toInt(&isValid);
        if(!isValid)
        {
            qWarning() << "Invalid field \"from\"";
            return nullptr;
        }
    }
    if(jsonProperty.contains("to"))
    {
        to = jsonProperty["to"].toInt(&isValid);
        if(!isValid)
        {
            qWarning() << "Invalid field \"to\"";
            return nullptr;
        }
    }

    if(from > to)
    {
        qWarning() << QString("Invalid range (from %1 to %2)")
                      .arg(QString::number(from),
                           QString::number(to));
        return nullptr;
    }
    return std::make_unique<PropertyInfo>(QMetaType::Type::Int, from, to);
}

std::unique_ptr<PropertyInfo> PropertyInfoFactory::floatProperty(const QVariantHash &jsonProperty)
{
    float from = std::numeric_limits<float>::min();
    float to = std::numeric_limits<float>::max();
    bool isValid = false;
    if(jsonProperty.contains("from"))
    {
        from = jsonProperty["from"].toFloat(&isValid);
        if(!isValid)
        {
            qWarning() << "Invalid field \"from\"";
            return nullptr;
        }
    }
    if(jsonProperty.contains("to"))
    {
        to = jsonProperty["to"].toFloat(&isValid);
        if(!isValid)
        {
            qWarning() << "Invalid field \"to\"";
            return nullptr;
        }
    }

    if(from > to)
    {
        qWarning() << QString("Invalid range (from %1 to %2)")
                      .arg(QString::number(from),
                           QString::number(to));
        return nullptr;
    }

    return std::make_unique<PropertyInfo>(QMetaType::Type::Float, from, to);
}

std::unique_ptr<PropertyInfo> PropertyInfoFactory::stringListProperty(const QVariantHash &jsonProperty)
{
    if(jsonProperty.contains("items") == false)
    {
        qWarning() << "Invalid field \"items\"";
        return nullptr;
    }
    return std::make_unique<PropertyInfo>(QMetaType::Type::QStringList, jsonProperty["items"].toList());
}

std::unique_ptr<PropertyInfo> PropertyInfoFactory::iconProperty(const QVariantHash &jsonProperty)
{
    return std::make_unique<PropertyInfo>(QMetaType::QIcon);
}
