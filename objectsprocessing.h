#ifndef OBJECTSPROCESSING_H
#define OBJECTSPROCESSING_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVector>
#include <QFile>

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
    QString _objectName;
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
            qWarning() << QString("Couldn't open ojects file %1")
                          .arg(_filename);
            return objects;
        }

        QJsonParseError parseError;
        const QJsonDocument doc(QJsonDocument::fromJson(file.readAll(), &parseError));

        if (parseError.error != QJsonParseError::NoError) {
               qWarning() << "Parse error at" << parseError.offset << ":" << parseError.errorString();
               return objects;
        }

        const QJsonObject jObject = doc.object();
        qInfo() << "Keys: " << jObject.keys();
        for(auto it = jObject.constBegin(); it != jObject.constEnd(); ++it)
        {
            auto objectsFromArray = getObjectsFromArray(it.key(), it->toArray());
            objects.append(objectsFromArray);
        }

        return objects;
    }

private:
    const QString _filename;

    QVector<CustomObject> getObjectsFromArray(const QString &objectName,
                       const QJsonArray &array)
    {
        QVector<CustomObject> objects;
        for(auto it = array.constBegin(); it != array.constEnd(); ++it)
        {
            objects.push_back(CustomObject(objectName, it->toObject().toVariantHash()));
        }

        return objects;
    }
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

#endif // OBJECTSPROCESSING_H
