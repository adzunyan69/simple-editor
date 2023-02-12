#ifndef OBJECTSPROCESSING_H
#define OBJECTSPROCESSING_H

#include <memory>

#include "object_reader.h"
#include "object_writer.h"

// Objects reader-writer using instance using instance of the some reader/writer instance
class ObjectProcessing
{
public:
    ObjectProcessing() = default;

    QVector<CustomObject> read(std::shared_ptr<ObjectsReader> reader ) const
    {
        return reader->readObjects();
    }

    void write(const QVector<CustomObject> &objects, std::shared_ptr<ObjectsWriter> writer) const
    {
        writer->writeObjects(objects);
    }
};

#endif // OBJECTSPROCESSING_H
