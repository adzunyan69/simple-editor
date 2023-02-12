#ifndef PROPERTY_WIDGET_H
#define PROPERTY_WIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>

// Abstract container for the certain property
class PropertyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PropertyWidget(const QString &propertyName,
                            QWidget *parent = nullptr);

    virtual QVariant value() const = 0;
    virtual void setValue(const QVariant &value) = 0;

protected:
    QLayout *propertyLayout{ nullptr };
};

#endif // PROPERTY_WIDGET_H
