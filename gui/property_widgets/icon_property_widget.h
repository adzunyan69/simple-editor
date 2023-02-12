#ifndef ICON_PROPERTY_WIDGET_H
#define ICON_PROPERTY_WIDGET_H

#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QDir>
#include "../../properties_config/property_info.h"
#include "../property_widget.h"

// Icon-property widget implementation with ability to change icon
class IconPropertyWidget : public PropertyWidget
{
    Q_OBJECT
public:
    explicit IconPropertyWidget(const QString &propertyName,
                                const Property &property,
                                QWidget *parent = nullptr);
    QVariant value() const override;
    void setValue(const QVariant &value) override;

private:
    QLabel *pixmapLabel{ nullptr };
    QString filename;

private slots:
    void updateIcon();
};

#endif // ICON_PROPERTY_WIDGET_H
