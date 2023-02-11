#ifndef OBJECTSPROCESSING_H
#define OBJECTSPROCESSING_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QVector>
#include <QFile>

namespace Utility
{

class CustomObject
{
public:
    CustomObject(const QString &objectName, const QVariantHash &properties)
        : _objectName(objectName), _properties(properties)
    { }

    QString objectName() const
    {
        return _objectName;
    }

    QList<QString> propertiesNames () const
    {
        return _propertiesNames;
    }

    QVariant property(const QString &propertyName) const
    {
        return _properties[propertyName];
    }

    QVariantHash properties() const
    {
        return _properties;
    }

private:
    const QString _objectName;
    QList<QString> _propertiesNames;
    QVariantHash _properties;
};


class ObjectsReader
{
public:
    ObjectsReader() = default;
    virtual ~ObjectsReader() = default;

    virtual QVector<CustomObject> readObjects() = 0;
};

class ObjectsWriter
{
public:
    ObjectsWriter() = default;
    virtual ~ObjectsWriter() = default;

    virtual void writeObjects(const QVector<CustomObject> &objects) = 0;
};

class JsonObjectsReader : public ObjectsReader
{
public:
    JsonObjectsReader(const QString &filename)
        : _filename(filename), ObjectsReader()
    { }

    QVector<CustomObject> readObjects() override
    {
        QVector<CustomObject> objects;

        QFile file(_filename);

        if (!file.open(QIODevice::ReadOnly)) {
            qWarning("Couldn't open file.");
            return objects;
        }

        QByteArray saveData = file.readAll();

        QJsonParseError parseError;
        const QJsonDocument doc(QJsonDocument::fromJson(saveData, &parseError));

        if (parseError.error != QJsonParseError::NoError) {
               qWarning() << "Parse error at" << parseError.offset << ":" << parseError.errorString();
               return objects;
        }

        const QJsonObject jObject = doc.object();
        qInfo() << "Keys: " << jObject.keys();
        for(auto it = jObject.constBegin(); it != jObject.constEnd(); ++it)
        {
            objects.push_back(CustomObject(it.key(),
                              it.value().toObject().toVariantHash()));
        }

        return objects;
    }

private:
    const QString _filename;
};

class JsonObjectsWriter : public ObjectsWriter
{
public:
    JsonObjectsWriter(const QString &filename)
        : _filename(filename), ObjectsWriter()
    { }

    void writeObjects(const QVector<CustomObject> &objects) override
    {
        QFile file(_filename);

        if (!file.open(QIODevice::WriteOnly)) {
            qWarning("Couldn't open file.");
            return;
        }

        QJsonObject root;
        for(auto &object : objects)
            root.insert(object.objectName() + " test", QJsonObject::fromVariantHash(object.properties()));

        QJsonDocument doc(root);
        qDebug() << doc.toJson();
    }

private:
    const QString _filename;
};

class ObjectProcessing
{
public:
    ObjectProcessing() = default;

    QVector<CustomObject> read(std::unique_ptr<ObjectsReader> reader ) const
    {
        return reader->readObjects();
    }

    void write(const QVector<CustomObject> &objects, std::unique_ptr<ObjectsWriter> writer) const
    {
        writer->writeObjects(objects);
    }
};

}
//class ObjectEditorWidget
//{
//public:
//    void drawObject(QObject* obj)
//    {
//        obj->objectName(); // "Player"
//        obj->dynamicPropertyNames(); // "Material", "Speed"
//        auto widget = new QWidget();
//        wdiget->label("Player");
//        widget->addListBox("material1")...; // "array"
//        obj->property("Material")
//    }
//    ObjectDescription save()
//    {
//        return { }//obj->property("Material")->setValue("material2");
//    }
//private:

//};



// ObjectColletion -> vector<QObject*>
// obj->setPropert("Speed", ...)
// obj->setPropert("Material", ...)

// PropertiesCollection properties
/* "Player": { "Speed": { "type": "float", "from": 1.0 }, "Material": { "type": "array", "items": { ... } } } */
// properties["Player"]["Speed"]->getType(); getFrom() getTo() getItems()

// obs->proeptyList();
// .. obs->property(propetyName) -> valut to the gui
// .. properties["Player"][propertyName]->













#endif // OBJECTSPROCESSING_H
