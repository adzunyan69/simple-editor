#ifndef JSON_OBJECT_READER_H
#define JSON_OBJECT_READER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include "object_reader.h"

// Object json-reader implementation
class JsonObjectsReader : public ObjectsReader
{
public:
    JsonObjectsReader(const QString &filename);
    QVector<CustomObject> readObjects() override;

private:
    const QString _filename;

    QVector<CustomObject> getObjectsFromArray(const QString &objectName,
                                              const QJsonArray &array);
};

#endif // JSON_OBJECT_READER_H
