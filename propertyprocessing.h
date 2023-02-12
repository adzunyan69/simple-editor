#ifndef PROPERTYPROCESSING_H
#define PROPERTYPROCESSING_H

#include <QVariant>
#include <memory>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <limits>


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

using PropertyHash = QHash<QString, std::shared_ptr<PropertyInfo>>;
using PropertyTable = QHash<QString, PropertyHash>;
using Property = std::shared_ptr<PropertyInfo>;

class PropertyInfoFactory
{
public:
    static std::unique_ptr<PropertyInfo> makeProperty(const QVariantHash &jsonProperty)
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
private:
    static std::unique_ptr<PropertyInfo> intProperty(const QVariantHash &jsonProperty)
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

    static std::unique_ptr<PropertyInfo> floatProperty(const QVariantHash &jsonProperty)
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

    static std::unique_ptr<PropertyInfo> stringListProperty(const QVariantHash &jsonProperty)
    {
        if(jsonProperty.contains("items") == false)
        {
            qWarning() << "Invalid field \"items\"";
            return nullptr;
        }
        return std::make_unique<PropertyInfo>(QMetaType::Type::QStringList, jsonProperty["items"].toList());
    }
    static std::unique_ptr<PropertyInfo> iconProperty(const QVariantHash &jsonProperty)
    {
        return std::make_unique<PropertyInfo>(QMetaType::QIcon);
    }

};

class PropertyProcessing
{
public:
    PropertyProcessing() = default;

    PropertyTable readPropertyConfig(const QString &filename) const
    {
        PropertyTable properties;

        QFile file(filename);
        if(!file.open(QIODevice::ReadOnly))
        {
            qWarning() << QString("Couldn't open property config file %1")
                          .arg(filename);
            return properties;
        }


        QJsonParseError parseError;
        const QJsonDocument doc(QJsonDocument::fromJson(file.readAll(), &parseError));

        if (parseError.error != QJsonParseError::NoError) {
               qWarning() << "Parse error at" << parseError.offset << ":" << parseError.errorString();
               return properties;
        }

        const QJsonObject jObject = doc.object();
        qInfo() << "Keys: " << jObject.keys();
        for(auto it = jObject.constBegin(); it != jObject.constEnd(); ++it)
        {
            properties[it.key()] = getPropertyHash(it.value().toObject());
        }

        return properties;

    }
private:
    PropertyHash getPropertyHash(const QJsonObject &jsonObject) const
    {
        PropertyHash propertyHash;
        for(auto it = jsonObject.constBegin(); it != jsonObject.constEnd(); ++it)
        {
            propertyHash[it.key()] = std::shared_ptr(PropertyInfoFactory::makeProperty(it.value().toObject().toVariantHash()));
        }

        return propertyHash;
    }

};

#endif // PROPERTYPROCESSING_H
