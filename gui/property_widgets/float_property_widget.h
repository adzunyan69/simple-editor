#ifndef FLOAT_PROPERTY_WIDGET_H
#define FLOAT_PROPERTY_WIDGET_H

#include <QSpinBox>
#include "../../properties_config/property_info.h"
#include "../property_widget.h"

// Float-property widget implementation
class FloatPropertyWidget : public PropertyWidget
{
    Q_OBJECT
public:
    explicit FloatPropertyWidget(const QString &propertyName,
                                 const Property &property,
                                 QWidget *parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant &value) override;

private:
    QDoubleSpinBox *spinBox{ nullptr };
};

#endif // FLOAT_PROPERTY_WIDGET_H
