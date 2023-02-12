#ifndef CUSTOMOBJECT_H
#define CUSTOMOBJECT_H

#include <QString>
#include <QVariantHash>

// Simple meta-object implemintation
class CustomObject
{
public:
    CustomObject(const QString &objectName,
                 const QVariantMap &propertiesTable)
        : _objectName(objectName),
          _propertiesTable(propertiesTable)
    { }

    QString objectName() const
    {
        return _objectName;
    }

    QVariantMap propertiesTable() const
    {
        return _propertiesTable;
    }

private:
    QString _objectName;
    QVariantMap _propertiesTable;
};

#endif // CUSTOMOBJECT_H
