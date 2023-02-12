#ifndef OBJECT_WRITER_H
#define OBJECT_WRITER_H

#include "custom_object.h"

// Abstract objects writer
class ObjectsWriter
{
public:
    ObjectsWriter() = default;
    virtual ~ObjectsWriter() = default;

    virtual void writeObjects(const QVector<CustomObject> &objects) = 0;
};

#endif // OBJECT_WRITER_H
