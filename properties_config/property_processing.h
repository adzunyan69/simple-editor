#ifndef PROPERTY_PROCESSING_H
#define PROPERTY_PROCESSING_H

#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "property_info_factory.h"

class PropertyProcessing
{
public:
    PropertyProcessing() = default;

    PropertyTable readPropertyConfig(const QString &filename) const;
private:
    PropertyHash getPropertyHash(const QJsonObject &jsonObject) const;
};

#endif // PROPERTY_PROCESSING_H
