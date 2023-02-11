#ifndef OBJECTWIDGET_H
#define OBJECTWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include "objectsprocessing.h"

class PropertyWidget;

class ObjectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ObjectWidget(const Utility::CustomObject &object, QWidget *parent = nullptr);

    Utility::CustomObject object() const;
private:
    QVector<PropertyWidget*> propertyWidgets;

    QWidget *createGroupBoxWidget(const Utility::CustomObject &object);
signals:

};

class PropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyWidget(const QString &propertyName, const QVariant &value, QWidget *parent = nullptr);

    virtual QVariant value() const = 0;
protected:
    QLineEdit *lineEdit{ nullptr };
};

class StringPropertyWidget : public PropertyWidget
{
    Q_OBJECT
public:
    explicit StringPropertyWidget(const QString &propertyName, const QString &str, QWidget *parent = nullptr)
        : PropertyWidget(propertyName, QVariant(str), parent)
    { }

    QVariant value() const override;

};

#endif // OBJECTWIDGET_H
