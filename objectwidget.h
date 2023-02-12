#ifndef OBJECTWIDGET_H
#define OBJECTWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QSpacerItem>
#include <QDoubleSpinBox>
#include <QIcon>
#include <QComboBox>
#include <QFileDialog>
#include <QPushButton>
#include <QDir>
#include "objectsprocessing.h"
#include "propertyprocessing.h"

class PropertyWidget;

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

class PropertyWidgetFactory
{
public:
    static PropertyWidget* makeWidget(const QString &propertyName,
                                      const Property &property,
                                      QWidget *parent = nullptr);
};

class PropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyWidget(const QString &propertyName, QWidget *parent = nullptr);

    virtual QVariant value() const = 0;
    virtual void setValue(const QVariant &value) = 0;

protected:
    QLayout *propertyLayout{ nullptr };
};

class IntPropertyWidget : public PropertyWidget
{
    Q_OBJECT
public:
    explicit IntPropertyWidget(const QString &propertyName, const Property &property, QWidget *parent = nullptr);


    QVariant value() const override;
    void setValue(const QVariant &value) override;
private:
    QSpinBox *spinBox{ nullptr };
};

class FloatPropertyWidget : public PropertyWidget
{
    Q_OBJECT
public:
    explicit FloatPropertyWidget(const QString &propertyName, const Property &property, QWidget *parent = nullptr);


    QVariant value() const override;
    void setValue(const QVariant &value) override;
private:
    QDoubleSpinBox *spinBox{ nullptr };
};

class IconPropertyWidget : public PropertyWidget
{
    Q_OBJECT
public:
    explicit IconPropertyWidget(const QString &propertyName, const Property &property, QWidget *parent = nullptr);


    QVariant value() const override;
    void setValue(const QVariant &value) override;
private:
    QLabel *pixmapLabel{ nullptr };
    QString filename;

private slots:
    void updateIcon();
};

class StringListPropertyWidget : public PropertyWidget
{
    Q_OBJECT
public:
    explicit StringListPropertyWidget(const QString &propertyName, const Property &property, QWidget *parent = nullptr);

    QVariant value() const override;
    void setValue(const QVariant &value) override;
private:
    QComboBox *stringBox{ nullptr };
};

#endif // OBJECTWIDGET_H
