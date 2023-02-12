#ifndef STRINGLIST_PROPERTY_WIDGET_H
#define STRINGLIST_PROPERTY_WIDGET_H

#include <QComboBox>
#include "../../properties_config/property_info.h"
#include "../property_widget.h"

// StringList-property widget implementation
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

#endif // STRINGLIST_PROPERTY_WIDGET_H
