#ifndef JSON_OBJECT_WRITER_H
#define JSON_OBJECT_WRITER_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

#include "object_writer.h"

// Object json-writer implementation
class JsonObjectsWriter : public ObjectsWriter
{
public:
    JsonObjectsWriter(const QString &filename);
    void writeObjects(const QVector<CustomObject> &objects) override;

private:
    const QString _filename;
};


#endif // JSON_OBJECT_WRITER_H
