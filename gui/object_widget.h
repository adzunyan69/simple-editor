#ifndef OBJECT_WIDGET_H
#define OBJECT_WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGroupBox>
#include "property_widget_factory.h"
#include "../custom_objects/custom_object.h"

// Contaioner for the object isntance
class ObjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ObjectWidget(const CustomObject &object,
                          const PropertyHash &propertyHash,
                          QWidget *parent = nullptr);
    CustomObject object() const;

private:
    QVector<PropertyWidget*> propertyWidgets;
    QWidget *createObjectWidget(const CustomObject &object,
                                const PropertyHash &propertyHash);
signals:

};

#endif // OBJECT_WIDGET_H
