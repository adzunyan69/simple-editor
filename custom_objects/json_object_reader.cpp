#include "json_object_reader.h"

JsonObjectsReader::JsonObjectsReader(const QString &filename)
    : ObjectsReader(),
      _filename(filename)

{ }

QVector<CustomObject> JsonObjectsReader::readObjects()
{
    QVector<CustomObject> objects;

    // Openning json file
    QFile file(_filename);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << QString("Couldn't open ojects file %1")
                      .arg(_filename);
        return objects;
    }

    // Trying to parse
    QJsonParseError parseError;
    const QJsonDocument doc(QJsonDocument::fromJson(file.readAll(), &parseError));
    if (parseError.error != QJsonParseError::NoError)
    {
           qWarning() << "Parse error at" << parseError.offset << ":" << parseError.errorString();
           return objects;
    }

    // Converting json key-value table to the CustomObject
    const QJsonObject jsonObjects = doc.object();
    for(auto it = jsonObjects.constBegin(); it != jsonObjects.constEnd(); ++it)
    {
        auto objectsFromArray = getObjectsFromArray(it.key(), it->toArray());
        objects.append(objectsFromArray);
    }

    return objects;
}

QVector<CustomObject> JsonObjectsReader::getObjectsFromArray(const QString &objectName,
                                                             const QJsonArray &array)
{
    QVector<CustomObject> objects;
    for(auto it = array.constBegin(); it != array.constEnd(); ++it)
    {
        auto o = it->toObject();
        auto h = o.toVariantHash();
        objects.push_back(CustomObject(objectName, it->toObject().toVariantHash()));
    }

    return objects;
}
