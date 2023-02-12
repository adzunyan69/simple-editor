#include "json_object_writer.h"

JsonObjectsWriter::JsonObjectsWriter(const QString &filename)
    : ObjectsWriter(),
      _filename(filename)
{ }

void JsonObjectsWriter::writeObjects(const QVector<CustomObject> &objects)
{
    // Openning json file
    QFile file(_filename);
    if (!file.open(QIODevice::WriteOnly))
    {
        qWarning("Couldn't open file.");
        return;
    }

    // Writting objects to the json file
    QJsonObject root;
    for(auto &object : objects)
        root.insert(object.objectName() + " test", QJsonObject::fromVariantHash(object.propertiesTable()));

    QJsonDocument doc(root);
    qDebug() << doc.toJson();
}
