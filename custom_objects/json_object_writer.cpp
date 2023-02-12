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

    // Creating arrays of the certain object types
    QJsonObject root;
    QHash<QString, QJsonArray> objArrays;
    for(auto &object : objects)
    {
        auto obj = QJsonObject::fromVariantMap(object.propertiesTable());
        if(objArrays.contains(object.objectName()) == false)
        {
            objArrays.insert(object.objectName(), QJsonArray());
        }

        objArrays[object.objectName()].append(obj);
    }

    // Appending all arrays to the root
    for(auto it = objArrays.constKeyValueBegin(); it != objArrays.constKeyValueEnd(); ++it)
    {
        root.insert(it->first, it->second);
    }

    QJsonDocument doc(root);
    QTextStream stream(&file);
    stream << QString(doc.toJson(QJsonDocument::Indented));
}
