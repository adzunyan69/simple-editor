#include "objectwidget.h"

#include <QLayout>
#include <QLabel>
#include <QGroupBox>
ObjectWidget::ObjectWidget(const CustomObject &object,
                           const PropertyHash &propertyHash,
                           QWidget *parent)
    : QWidget(parent)
{
    this->setObjectName(object.objectName());

    QLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(createObjectWidget(object, propertyHash));
    setLayout(mainLayout);

}

QWidget *ObjectWidget::createObjectWidget(const CustomObject &object,
                                          const PropertyHash &propertyHash)
{
    QGroupBox *groupBox = new QGroupBox(object.objectName(), this);
    QLayout *groupLayout = new QVBoxLayout();

    auto properties = object.properties();

    for(auto it = properties.constKeyValueBegin(); it != properties.constKeyValueEnd(); ++it)
    {
        if(propertyHash.contains(it->first) == false)
        {
            qWarning() << QString("Invalid object property %1")
                          .arg(it->first);
            return groupBox;
        }

        auto propertyWidget = PropertyWidgetFactory::makeWidget(it->first,
                                                                propertyHash[it->first],
                this);
        propertyWidget->setValue(it->second);
        propertyWidgets.push_back(propertyWidget);
        groupLayout->addWidget(propertyWidget);
    }
    groupBox->setLayout(groupLayout);

    return groupBox;
}

CustomObject ObjectWidget::object() const
{
    QVariantHash propertiesHash;
    for(auto &property: propertyWidgets)
        propertiesHash[property->objectName()] = property->value();

    return CustomObject(this->objectName(), propertiesHash);
}

PropertyWidget* PropertyWidgetFactory::makeWidget(const QString &propertyName,
                                                  const Property &property,
                                                  QWidget *parent)
{
    switch(property->type())
    {
    case QMetaType::Type::Int:
        return new IntPropertyWidget(propertyName, property, parent);
    case QMetaType::Type::Float:
        return new FloatPropertyWidget(propertyName, property, parent);
    case QMetaType::Type::QIcon:
        return new IconPropertyWidget(propertyName, property, parent);
    case QMetaType::Type::QStringList:
        return new StringListPropertyWidget(propertyName, property, parent);
    default:
        qWarning() << QString("Unknown property type %1")
                      .arg(QString::number(property->type()));
        return nullptr;
    }
}

PropertyWidget::PropertyWidget(const QString &propertyName,
                               QWidget *parent)
    : QWidget(parent)
{
    this->setObjectName(propertyName);

    propertyLayout = new QHBoxLayout(this);

    auto labelWidget = new  QLabel(propertyName, this);
    labelWidget->setMinimumWidth(50);
    propertyLayout->addWidget(labelWidget);

    this->setLayout(propertyLayout);
}

IntPropertyWidget::IntPropertyWidget(const QString &propertyName,
                                     const Property &property,
                                     QWidget *parent)
    : PropertyWidget(propertyName, parent)
{
    if(propertyLayout)
    {
        spinBox = new QSpinBox(this);
        spinBox->setMinimum(property->from().toInt());
        spinBox->setMaximum(property->to().toInt());
        spinBox->setMaximumWidth(75);

        propertyLayout->addItem(new QSpacerItem(1,1, QSizePolicy::Expanding));
        propertyLayout->addWidget(spinBox);
    }
}

QVariant IntPropertyWidget::value() const
{
    if(spinBox)
        return spinBox->value();

    return QVariant();
}

void IntPropertyWidget::setValue(const QVariant &value)
{
    bool isValid = false;
    int v = value.toInt(&isValid);
    if(spinBox && isValid)
        spinBox->setValue(v);
}

FloatPropertyWidget::FloatPropertyWidget(const QString &propertyName,
                                         const Property &property,
                                         QWidget *parent)
    : PropertyWidget(propertyName, parent)
{
    if(propertyLayout)
    {
        spinBox = new QDoubleSpinBox(this);
        spinBox->setMinimum(property->from().toFloat());
        spinBox->setMaximum(property->to().toFloat());
        spinBox->setMaximumWidth(75);

        propertyLayout->addItem(new QSpacerItem(1,1, QSizePolicy::Expanding));
        propertyLayout->addWidget(spinBox);
    }
}

QVariant FloatPropertyWidget::value() const
{
    if(spinBox)
        return spinBox->value();

    return QVariant();
}

void FloatPropertyWidget::setValue(const QVariant &value)
{
    bool isValid = false;
    int v = value.toFloat(&isValid);
    if(spinBox && isValid)
        spinBox->setValue(v);
}

IconPropertyWidget::IconPropertyWidget(const QString &propertyName,
                                       const Property &property,
                                       QWidget *parent)
    : PropertyWidget(propertyName, parent)
{
    if(propertyLayout)
    {
        pixmapLabel = new QLabel("image", this);
        QPushButton *changeIconButton = new QPushButton("Select image", this);
        connect(changeIconButton, &QPushButton::clicked,
                this, &IconPropertyWidget::updateIcon);

        propertyLayout->addItem(new QSpacerItem(1,1, QSizePolicy::Expanding));
        propertyLayout->addWidget(pixmapLabel);
        propertyLayout->addWidget(changeIconButton);
    }
}

QVariant IconPropertyWidget::value() const
{
    if(pixmapLabel)
        return filename;

    return QVariant();
}

void IconPropertyWidget::setValue(const QVariant &value)
{
    if(pixmapLabel)
    {
        filename = value.toString();
        QPixmap pixmap(filename);
        if(pixmap.isNull())
            pixmapLabel->setText("Image doesn't exists");
        else
        {
            pixmap = pixmap.scaled(35, 35, Qt::IgnoreAspectRatio);
            pixmapLabel->setPixmap(pixmap);
        }
    }
}

void IconPropertyWidget::updateIcon()
{
    QString file = QFileDialog::getOpenFileName(this,
        tr("Open Image"), QDir::currentPath(), tr("Image Files (*.png *.jpg *.bmp *.)"));

    if(file.isEmpty() == false)
        setValue(file);
}

StringListPropertyWidget::StringListPropertyWidget(const QString &propertyName,
                                                   const Property &property,
                                                   QWidget *parent)
    : PropertyWidget(propertyName, parent)
{
    if(propertyLayout)
    {
        stringBox = new QComboBox(this);
        for(auto &value: property->accpetedValues())
            stringBox->addItem(value.toString());

        propertyLayout->addItem(new QSpacerItem(1,1, QSizePolicy::Expanding));
        propertyLayout->addWidget(stringBox);
    }
}

QVariant StringListPropertyWidget::value() const
{
    if(stringBox)
        return stringBox->currentText();

    return QVariant();
}

void StringListPropertyWidget::setValue(const QVariant &value)
{
    if(stringBox)
    {
        int index = stringBox->findText(value.toString());
        if(index ==  -1)
        {
            qWarning() << "The value isn't exists in the combo box";
            return;
        }
        stringBox->setCurrentIndex(index);
    }
}
