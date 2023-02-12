#ifndef OBJECT_READER_H
#define OBJECT_READER_H

#include "custom_object.h"

// Abstract objects parser
class ObjectsReader
{
public:
    ObjectsReader() = default;
    virtual ~ObjectsReader() = default;

    virtual QVector<CustomObject> readObjects() = 0;
};

#endif // OBJECT_READER_H
