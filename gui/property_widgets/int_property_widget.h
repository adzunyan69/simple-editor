#ifndef INT_PROPERTY_WIDGET_H
#define INT_PROPERTY_WIDGET_H

#include <QSpinBox>
#include "../../properties_config/property_info.h"
#include "../property_widget.h"

// Int-property widget implementation
class IntPropertyWidget : public PropertyWidget
{
    Q_OBJECT
public:
    explicit IntPropertyWidget(const QString &propertyName,
                               const Property &property,
                               QWidget *parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant &value) override;

private:
    QSpinBox *spinBox{ nullptr };
};

#endif // INT_PROPERTY_WIDGET_H
