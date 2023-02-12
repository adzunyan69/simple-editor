#ifndef PROPERTY_INFO_H
#define PROPERTY_INFO_H

#include <QVariant>
#include <memory>

class PropertyInfo;

using PropertyHash = QHash<QString, std::shared_ptr<PropertyInfo>>;
using PropertyTable = QHash<QString, PropertyHash>;
using Property = std::shared_ptr<PropertyInfo>;

class PropertyInfo
{
public:

    // Constructor for the list or the array types
    PropertyInfo(QMetaType::Type type, const QVariantList &acceptedValues)
        : _type(type), _acceptedValues(acceptedValues)
    {
    }

    // Constructor for the some single-value properry with from-to restriction
    PropertyInfo(QMetaType::Type type, const QVariant &from, const QVariant &to)
        : _type(type), _from(from), _to(to)
    {
    }

    // Constructor for the some single-value property withot restriction
    PropertyInfo(QMetaType::Type type)
        : _type(type)
    { }
    QMetaType::Type type() const
    {
        return _type;
    }

    QVariantList accpetedValues() const
    {
        return _acceptedValues;
    }

    QVariant from() const
    {
        return _from;
    }

    QVariant to() const
    {
        return _to;
    }

private:
    QMetaType::Type _type;
    QVariantList _acceptedValues; // for the Array type
    QVariant _from;
    QVariant _to;
};


#endif // PROPERTY_INFO_H
