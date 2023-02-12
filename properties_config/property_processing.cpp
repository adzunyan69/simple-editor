#include "property_processing.h"

PropertyTable PropertyProcessing::readPropertyConfig(const QString &filename) const
{
    PropertyTable properties;

    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
    {
        qWarning() << QString("Couldn't open property config file %1")
                      .arg(filename);
        return properties;
    }


    QJsonParseError parseError;
    const QJsonDocument doc(QJsonDocument::fromJson(file.readAll(), &parseError));

    if (parseError.error != QJsonParseError::NoError) {
           qWarning() << "Parse error at" << parseError.offset << ":" << parseError.errorString();
           return properties;
    }

    const QJsonObject jObject = doc.object();
    qInfo() << "Keys: " << jObject.keys();
    for(auto it = jObject.constBegin(); it != jObject.constEnd(); ++it)
    {
        properties[it.key()] = getPropertyHash(it.value().toObject());
    }

    return properties;

}

PropertyHash PropertyProcessing::getPropertyHash(const QJsonObject &jsonObject) const
{
    PropertyHash propertyHash;
    for(auto it = jsonObject.constBegin(); it != jsonObject.constEnd(); ++it)
    {
        auto property = std::shared_ptr(PropertyInfoFactory::makeProperty(it.value().toObject().toVariantHash()));
        if(property == nullptr)
        {
            qWarning() << "Received invalid property";
            continue;
        }
        propertyHash[it.key()] = property;
    }

    return propertyHash;
}
