#ifndef CUSTOMOBJECT_H
#define CUSTOMOBJECT_H

#include <QString>
#include <QVariantHash>

// Simple meta-object implemintation
class CustomObject
{
public:
    CustomObject(const QString &objectName,
                 const QVariantHash &propertiesTable)
        : _objectName(objectName),
          _propertiesTable(propertiesTable)
    { }

    QString objectName() const
    {
        return _objectName;
    }

    QVariantHash propertiesTable() const
    {
        return _propertiesTable;
    }

private:
    QString _objectName;
    QVariantHash _propertiesTable;
};

#endif // CUSTOMOBJECT_H
