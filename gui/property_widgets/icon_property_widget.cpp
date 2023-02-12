#include "icon_property_widget.h"
#include <QDebug>
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

        propertyLayout->addItem(new QSpacerItem(1, 1, QSizePolicy::Expanding));
        propertyLayout->addWidget(pixmapLabel);
        propertyLayout->addWidget(changeIconButton);
    }
}

QVariant IconPropertyWidget::value() const
{
    if(pixmapLabel)
        return filename;

    // return invalid QVariant instead throwing exception
    return QVariant();
}

void IconPropertyWidget::setValue(const QVariant &value)
{
    if(pixmapLabel)
    {
        filename = value.toString();
        QPixmap pixmap(filename);
        if(pixmap.isNull())
        {
            qWarning() << "Picture isn't exists";
            pixmapLabel->setText("Image doesn't \nexists");
        }
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
        tr("Open Image"), QDir::currentPath(), tr("Image Files (*.png *.jpg *.bmp *.ico)"));

    if(file.isEmpty() == false)
        setValue(file);
}
